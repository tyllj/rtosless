#include "rtosless_timer.h"
#include "rtosless_events.h"
#include "rtosless_hal.h"
#include <Arduino.h>

typedef struct {
    void (*handler)(void);
    uint32_t exec_time;
    uint32_t interval;
    uint8_t flags;
    void* instance_ptr;
    void (*member_stub)(void*);
} rtosless_timer_t;

static rtosless_timer_t timers[TIMER_MAX_COUNT];

static inline uint32_t rtosless_now(uint8_t res) {
    return (res == TIMER_RESOLUTION_MILLIS) ? rl::kernel_millis() : rl::kernel_micros();
}

static inline uint8_t timer_is_oneshot(uint8_t index) {
    return (index < TIMER_MAX_COUNT && timers[index].interval == 0);
}

extern "C" {

    uint8_t timer_create(void (*handler)(void), uint32_t interval, uint32_t phase,
                         uint8_t resolution, uint8_t priority, uint8_t one_shot)
    {
        if (priority >= SCHED_EVENT_PRIO_COUNT) return 0xFF;
        uint32_t ps = rl_enter_critical();
        for (uint8_t i = 0; i < TIMER_MAX_COUNT; ++i) {
            if (!timers[i].handler && !timers[i].member_stub) {
                timers[i].handler = handler;
                timers[i].interval = one_shot ? 0 : interval;
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
        timers[index].member_stub = stub;
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
                           uint32_t phase, uint8_t resolution, uint8_t priority, uint8_t one_shot)
    {
        if (index >= TIMER_MAX_COUNT || priority >= SCHED_EVENT_PRIO_COUNT) return;
        uint32_t ps = rl_enter_critical();
        rtosless_timer_t* t = &timers[index];
        if (!t->handler && !t->member_stub) { rl_exit_critical(ps); return; }
        if (handler) t->handler = handler;
        t->interval = one_shot ? 0 : interval;
        t->exec_time = rtosless_now(resolution) + phase;
        timer_set_trigger_state(&t->flags, TIMER_STATE_RUNNING);
        timer_set_resolution(&t->flags, resolution);
        timer_set_priority(&t->flags, priority);
        timer_set_member_callback(&t->flags, t->member_stub ? 1 : 0);
        rl_exit_critical(ps);
    }

    uint8_t timer_create_millis(void (*handler)(void), uint32_t interval, uint32_t phase) {
        return timer_create(handler, interval, phase, TIMER_RESOLUTION_MILLIS, SCHED_PRIO_LOW, 0);
    }

    uint8_t timer_create_micros(void (*handler)(void), uint32_t interval, uint32_t phase) {
        return timer_create(handler, interval, phase, TIMER_RESOLUTION_MICROS, SCHED_PRIO_HIGH, 0);
    }

    uint8_t timer_do_in_millis(void (*handler)(void), uint32_t delay) {
        return timer_create(handler, delay, 0, TIMER_RESOLUTION_MILLIS, SCHED_PRIO_LOW, 1);
    }

    void timer_set_interval(uint8_t index, uint32_t interval) {
        if (index >= TIMER_MAX_COUNT) return;
        uint32_t ps = rl_enter_critical();
        timers[index].interval = interval;
        rl_exit_critical(ps);
    }

    void timer_set_priority(uint8_t index, uint8_t priority) {
        if (index >= TIMER_MAX_COUNT || priority >= SCHED_EVENT_PRIO_COUNT) return;
        uint32_t ps = rl_enter_critical();
        timer_set_priority(&timers[index].flags, priority);
        rl_exit_critical(ps);
    }

    void timer_process_queue(void) {
        uint32_t now_ms = rtosless_now(TIMER_RESOLUTION_MILLIS);
        uint32_t now_us = rtosless_now(TIMER_RESOLUTION_MICROS);

        for (uint8_t i = 0; i < TIMER_MAX_COUNT; ++i) {
            void (*handler)(void) = NULL;
            void (*member_stub)(void*) = NULL;
            void* instance_ptr = NULL;
            uint8_t priority = 0;
            event_args_t args = {0};
            uint8_t should_invoke = 0;

            uint32_t ps = rl_enter_critical();
            rtosless_timer_t* t = &timers[i];

            if ((t->handler || t->member_stub) && timer_get_trigger_state(t->flags) == TIMER_STATE_RUNNING) {
                uint32_t now = (timer_get_resolution(t->flags) == TIMER_RESOLUTION_MILLIS) ? now_ms : now_us;
                if (now >= t->exec_time) {
                    should_invoke = 1;
                    priority = timer_get_priority(t->flags);
                    args.ptrs[0] = (uintptr_t)(t->handler ? (void*)t->handler : (void*)t->member_stub);

                    if (timer_is_oneshot(i)) {
                        timer_delete(i);
                    } else {
                        t->exec_time += t->interval;
                    }

                    handler = t->handler;
                    member_stub = t->member_stub;
                    instance_ptr = t->instance_ptr;
                }
            }

            rl_exit_critical(ps);

            if (should_invoke) {
                if (timer_is_member_callback(t->flags) && member_stub && instance_ptr) {
                    if (event_post(call_callback, args, priority) != 0) {
                        member_stub(instance_ptr);
                    }
                } else if (handler) {
                    if (event_post(call_callback, args, priority) != 0) {
                        handler();
                    }
                }
            }
        }
    }
}
