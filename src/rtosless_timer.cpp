#include "rtosless_timer.h"
#include "rtosless_events.h"
#include "rtosless_hal.h"
#include "rtosless_kernel.h"

namespace rl {

    typedef struct {
        uint32_t exec_time;
        uint32_t interval;
        uint8_t flags;
        void (*handler)(void);
        void* instance_ptr;
    } rtosless_timer_t;

    static rtosless_timer_t timers[TIMER_MAX_COUNT];

    static inline uint32_t rtosless_now(uint8_t res) {
        return (res == TIMER_RESOLUTION_MILLIS) ? rl::kernel_millis() : rl::kernel_micros();
    }

    static inline uint8_t timer_is_oneshot(uint8_t index) {
        return (index < TIMER_MAX_COUNT && timers[index].interval == 0);
    }

    uint8_t timer_create(void (*handler)(void), uint32_t interval, uint32_t phase,
                         uint8_t resolution, uint8_t priority)
    {
        if (priority >= SCHED_EVENT_PRIO_COUNT) return 0xFF;
        uint32_t ps = rl_enter_critical();
        for (uint8_t i = 0; i < TIMER_MAX_COUNT; ++i) {
            if (!timers[i].handler) {
                timers[i].handler = handler;
                timers[i].interval = interval;
                timers[i].exec_time = rtosless_now(resolution) + phase;
                timer_set_trigger_state(&timers[i].flags, TIMER_STATE_RUNNING);
                timer_set_resolution(&timers[i].flags, resolution);
                timer_set_priority(&timers[i].flags, priority);
                rl_exit_critical(ps);
                return i;
            }
        }
        rl_exit_critical(ps);
        return 0xFF;
    }

    void timer_bind_member(uint8_t index, void* instance, void (*stub)(void*)) {
        if (index >= TIMER_MAX_COUNT) return;
        uint32_t ps = rl_enter_critical();
        timers[index].instance_ptr = instance;
        timers[index].handler = reinterpret_cast<void (*)(void)>(reinterpret_cast<uintptr_t>(stub));
        timer_set_member_callback(&timers[index].flags, 1);
        rl_exit_critical(ps);
    }

    void timer_pause(uint8_t index) {
        if (index >= TIMER_MAX_COUNT) return;
        uint32_t ps = rl_enter_critical();
        timer_set_trigger_state(&timers[index].flags, TIMER_STATE_PAUSED);
        rl_exit_critical(ps);
    }

    void timer_continue(uint8_t index) {
        if (index >= TIMER_MAX_COUNT) return;
        uint32_t ps = rl_enter_critical();
        rtosless_timer_t* t = &timers[index];
        if (timer_get_trigger_state(t->flags) == TIMER_STATE_PAUSED && t->interval > 0) {
            uint32_t now = rtosless_now(timer_get_resolution(t->flags));
            if (now >= t->exec_time) {
                uint32_t missed = (now - t->exec_time) / t->interval;
                t->exec_time += (missed + 1) * t->interval;
            }
            timer_set_trigger_state(&t->flags, TIMER_STATE_RUNNING);
        }
        rl_exit_critical(ps);
    }

    void timer_delete(uint8_t index) {
        if (index >= TIMER_MAX_COUNT) return;
        uint32_t ps = rl_enter_critical();
        timers[index] = (rtosless_timer_t){0};
        rl_exit_critical(ps);
    }

    void timer_reconfigure(uint8_t index, void (*handler)(void), uint32_t interval,
                           uint32_t phase, uint8_t resolution, uint8_t priority)
    {
        if (index >= TIMER_MAX_COUNT || priority >= SCHED_EVENT_PRIO_COUNT) return;
        uint32_t ps = rl_enter_critical();
        rtosless_timer_t* t = &timers[index];
        if (!t->handler) { rl_exit_critical(ps); return; }
        if (handler) t->handler = handler;
        t->interval = interval;
        t->exec_time = rtosless_now(resolution) + phase;
        timer_set_trigger_state(&t->flags, TIMER_STATE_RUNNING);
        timer_set_resolution(&t->flags, resolution);
        timer_set_priority(&t->flags, priority);
        rl_exit_critical(ps);
    }

    uint8_t timer_do_each_millis(void (*handler)(void), uint32_t interval) {
        return timer_create(handler, interval, 0, TIMER_RESOLUTION_MILLIS, SCHED_PRIO_LOW);
    }

    uint8_t timer_do_each_micros(void (*handler)(void), uint32_t interval) {
        return timer_create(handler, interval, 0, TIMER_RESOLUTION_MICROS, SCHED_PRIO_HIGH);
    }

    uint8_t timer_do_in_millis(void (*handler)(void), uint32_t delay) {
        return timer_create(handler, 0, delay, TIMER_RESOLUTION_MILLIS, SCHED_PRIO_HIGH);
    }

    static event_args_t timer_member_event_make_args(void (*member_stub)(void*), void* instance_ptr) {
        event_args_t args = {};
        args.ptrs[0] = reinterpret_cast<uintptr_t>(instance_ptr);
        args.ptrs[1] = reinterpret_cast<uintptr_t>(member_stub);
        return args;
    }

    static event_args_t timer_static_event_make_args(void (*handler)()) {
        event_args_t args = {};
        args.ptrs[0] = reinterpret_cast<uintptr_t>(handler);
        return args;
    }

    static void call_member_callback(const event_args_t args) {
        void* instance_ptr = reinterpret_cast<void*>(args.ptrs[0]);
        void (*member_stub)(void*) = reinterpret_cast<void (*)(void*)>(args.ptrs[1]);    
        if (instance_ptr && member_stub)
            member_stub(instance_ptr);
    }

    void timer_process_queue(void) {
        uint32_t now_ms = rtosless_now(TIMER_RESOLUTION_MILLIS);
        uint32_t now_us = rtosless_now(TIMER_RESOLUTION_MICROS);

        for (uint8_t i = 0; i < TIMER_MAX_COUNT; ++i) {
            void (*handler)(void) = nullptr;
            void (*member_stub)(void*) = nullptr;
            void* instance_ptr = nullptr;
            uint8_t priority = 0;
            event_args_t args = {0};
            uint8_t should_invoke = 0;

            uint32_t ps = rl_enter_critical();
            rtosless_timer_t* t = &timers[i];

            if ((t->handler) && timer_get_trigger_state(t->flags) == TIMER_STATE_RUNNING) {
                uint32_t now = (timer_get_resolution(t->flags) == TIMER_RESOLUTION_MILLIS) ? now_ms : now_us;
                if (now >= t->exec_time) {
                    should_invoke = 1;
                    priority = timer_get_priority(t->flags);
                    handler = t->handler;
                    member_stub = reinterpret_cast<void (*)(void*)>(t->handler);
                    instance_ptr = t->instance_ptr;
                    
                    args = timer_is_member_callback(t->flags)
                        ? timer_member_event_make_args(member_stub, instance_ptr)
                        : timer_static_event_make_args(handler);

                    if (timer_is_oneshot(i)) {
                        timer_delete(i);
                    } else {
                        t->exec_time += t->interval;
                    }
                }
            }

            rl_exit_critical(ps);

            if (should_invoke) {
                if (timer_is_member_callback(t->flags) && member_stub && instance_ptr) {
                    if (event_post(call_member_callback, args, priority) != 0 && priority == SCHED_PRIO_HIGH) {
                        member_stub(instance_ptr);
                    }
                } else if (handler) {
                    if (event_post(call_callback, args, priority) != 0 && priority == SCHED_PRIO_HIGH) {
                        handler();
                    }
                }
            }
        }
    }
}
