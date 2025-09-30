#include "rtosless_timer.h"
#include "rtosless_events.h"  
#include "rtosless_hal.h"
#include "rtosless_kernel.h"
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint32_t exec_time;
    uint32_t interval;
    uint8_t flags;
    void (*handler)(void*);
    void* instance_ptr;
} rl_timer_internal_t;

static rl_timer_internal_t timers[RL_TIMER_MAX_COUNT];

static inline uint32_t rl_now(uint8_t res) {
    return (res == RL_TIMER_RESOLUTION_MILLIS) ? rl_millis() : rl_micros();
}

static inline uint8_t rl_timer_is_oneshot(uint8_t index) {
    return (index < RL_TIMER_MAX_COUNT && timers[index].interval == 0);
}

uint8_t rl_timer_create(void (*handler)(void*), void* instance, uint32_t interval, uint32_t phase,
                        uint8_t resolution, uint8_t priority)
{
    if (priority >= RL_SCHED_EVENT_PRIO_COUNT) return 0xFF;
    bool ps = rl_enter_critical();
    for (uint8_t i = 0; i < RL_TIMER_MAX_COUNT; ++i) {
        if (!timers[i].handler) {
            timers[i].handler = handler;
            timers[i].instance_ptr = instance;
            timers[i].interval = interval;
            timers[i].exec_time = rl_now(resolution) + phase;
            rl_timer_set_trigger_state(&timers[i].flags, RL_TIMER_STATE_RUNNING);
            rl_timer_set_resolution(&timers[i].flags, resolution);
            rl_timer_set_priority(&timers[i].flags, priority);
            rl_exit_critical(ps);
            return i;
        }
    }
    rl_exit_critical(ps);
    return 0xFF;
}

void rl_timer_bind_member(uint8_t index, void* instance, void (*stub)(void*)) {
    if (index >= RL_TIMER_MAX_COUNT) return;
    uint32_t ps = rl_enter_critical();
    timers[index].instance_ptr = instance;
    timers[index].handler = (void (*)(void*))((uintptr_t)stub);
    rl_timer_set_member_callback(&timers[index].flags, 1);
    rl_exit_critical(ps);
}

void rl_timer_pause(uint8_t index) {
    if (index >= RL_TIMER_MAX_COUNT) return;
    uint32_t ps = rl_enter_critical();
    rl_timer_set_trigger_state(&timers[index].flags, RL_TIMER_STATE_PAUSED);
    rl_exit_critical(ps);
}

void rl_timer_continue(uint8_t index) {
    if (index >= RL_TIMER_MAX_COUNT) return;
    uint32_t ps = rl_enter_critical();
    rl_timer_internal_t* t = &timers[index];
    if (rl_timer_get_trigger_state(t->flags) == RL_TIMER_STATE_PAUSED && t->interval > 0) {
        uint32_t now = rl_now(rl_timer_get_resolution(t->flags));
        if (now >= t->exec_time) {
            uint32_t missed = (now - t->exec_time) / t->interval;
            t->exec_time += (missed + 1) * t->interval;
        }
        rl_timer_set_trigger_state(&t->flags, RL_TIMER_STATE_RUNNING);
    }
    rl_exit_critical(ps);
}

void rl_timer_delete(uint8_t index) {
    if (index >= RL_TIMER_MAX_COUNT) return;
    uint32_t ps = rl_enter_critical();
    /* C99 compound literal for zero initialization */
    timers[index] = (rl_timer_internal_t){0};
    rl_exit_critical(ps);
}

void rl_timer_reconfigure(uint8_t index, void (*handler)(void*), void* instance, uint32_t interval,
                          uint32_t phase, uint8_t resolution, uint8_t priority)
{
    if (index >= RL_TIMER_MAX_COUNT || priority >= RL_SCHED_EVENT_PRIO_COUNT) return;
    uint32_t ps = rl_enter_critical();
    rl_timer_internal_t* t = &timers[index];
    if (!t->handler) { rl_exit_critical(ps); return; }
    if (handler) t->handler = handler;
    if (instance) t->instance_ptr = instance;
    t->interval = interval;
    t->exec_time = rl_now(resolution) + phase;
    rl_timer_set_trigger_state(&t->flags, RL_TIMER_STATE_RUNNING);
    rl_timer_set_resolution(&t->flags, resolution);
    rl_timer_set_priority(&t->flags, priority);
    rl_exit_critical(ps);
}

uint8_t rl_timer_do_each_millis(uint32_t interval, void (*handler)(void*), void* instance) {
    return rl_timer_create(handler, instance, interval, 0, RL_TIMER_RESOLUTION_MILLIS, RL_SCHED_PRIO_LOW);
}

uint8_t rl_timer_do_each_micros(uint32_t interval, void (*handler)(void*), void* instance) {
    return rl_timer_create(handler, instance, interval, 0, RL_TIMER_RESOLUTION_MICROS, RL_SCHED_PRIO_HIGH);
}

uint8_t rl_timer_do_in_millis(uint32_t delay, void (*handler)(void*), void* instance) {
    return rl_timer_create(handler, instance, 0, delay, RL_TIMER_RESOLUTION_MILLIS, RL_SCHED_PRIO_HIGH);
}

/* Event handling functions for timer callbacks */
static void timer_member_event_make_args(void (*member_stub)(void*), void* instance_ptr, rl_event_args_t* args) {
    args->ptrs[0] = (uintptr_t)instance_ptr;
    args->ptrs[1] = (uintptr_t)member_stub;
}


/* Implementation for member callback handling */
void rl_call_member_callback(rl_event_args_t args) {
    void* instance_ptr = (void*)args.ptrs[0];
    void (*member_stub)(void*) = (void (*)(void*))args.ptrs[1];    
    if (instance_ptr && member_stub)
        member_stub(instance_ptr);
}

/* Implementation for member callback handling */
void rl_call_static_callback(rl_event_args_t args) {
    void* instance_ptr = (void*)args.ptrs[0];
    void (*member_stub)(void*) = (void (*)(void*))args.ptrs[1];    
    if (member_stub)
        member_stub(instance_ptr);
}

void rl_timer_process_queue(void) {
    for (uint8_t i = 0; i < RL_TIMER_MAX_COUNT; ++i) {
        void (*handler)(void*) = NULL;
        void* instance_ptr = NULL;
        uint8_t priority = 0;
        rl_event_args_t args = {0};
        uint8_t should_invoke = 0;

        bool ps = rl_enter_critical();
        rl_timer_internal_t* t = &timers[i];

        if ((t->handler) && rl_timer_get_trigger_state(t->flags) == RL_TIMER_STATE_RUNNING) {
            uint32_t now = (rl_timer_get_resolution(t->flags) == RL_TIMER_RESOLUTION_MILLIS) ? rl_millis() : rl_micros();
            if (now >= t->exec_time) {
                should_invoke = 1;
                priority = rl_timer_get_priority(t->flags);
                handler = t->handler;
                instance_ptr = t->instance_ptr;
                

                timer_member_event_make_args(handler, instance_ptr, &args);
                

                if (rl_timer_is_oneshot(i)) {
                    rl_timer_delete(i);
                } else {
                    t->exec_time += t->interval;
                }
            }
        }

        rl_exit_critical(ps);

        if (should_invoke) {
            if (rl_timer_is_member_callback(t->flags) && handler && instance_ptr) {
                if (rl_event_post(rl_call_member_callback, args, priority) != 0 && priority == RL_SCHED_PRIO_HIGH) {
                    handler(instance_ptr);
                }
            } else if (handler) {
                if (rl_event_post(rl_call_static_callback, args, priority) != 0 && priority == RL_SCHED_PRIO_HIGH) {
                    handler(instance_ptr);
                }
            }
        }
    }
}