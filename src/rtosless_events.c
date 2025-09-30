#include "rtosless_events.h"
#include "rtosless_hal.h"
#include <stddef.h>
#include <stdint.h>

static volatile uint8_t ev_head[RL_SCHED_EVENT_PRIO_COUNT];
static volatile uint8_t ev_tail[RL_SCHED_EVENT_PRIO_COUNT];

typedef struct {
    void (*handler)(rl_event_args_t);
    rl_event_args_t args;
} rl_event_entry_t;

static rl_event_entry_t ev_q[RL_SCHED_EVENT_PRIO_COUNT][RL_SCHED_EVENT_QUEUE_LEN];

static inline int32_t event_enqueue_unsafe(uint8_t prio, void (*handler)(rl_event_args_t), rl_event_args_t args) {
    uint8_t next = (ev_tail[prio] + (uint8_t)1u) % RL_SCHED_EVENT_QUEUE_LEN;
    if (next == ev_head[prio]) return -1;
    ev_q[prio][ev_tail[prio]].handler = handler;
    ev_q[prio][ev_tail[prio]].args = args;
    ev_tail[prio] = next;
    return 0;
}

static inline int32_t event_dequeue_unsafe(uint8_t prio, void (**out)(rl_event_args_t), rl_event_args_t* args_out) {
    if (ev_head[prio] == ev_tail[prio]) return -1;
    *out = ev_q[prio][ev_head[prio]].handler;
    *args_out = ev_q[prio][ev_head[prio]].args;
    ev_head[prio] = (ev_head[prio] + (uint8_t)1u) % RL_SCHED_EVENT_QUEUE_LEN;
    return 0;
}

int32_t rl_event_post(void (*handler)(rl_event_args_t), rl_event_args_t args, uint8_t priority) {
    if (handler == NULL || priority >= RL_SCHED_EVENT_PRIO_COUNT) return -1;
    bool ps = rl_enter_critical();
    int32_t rc = event_enqueue_unsafe(priority, handler, args);
    rl_exit_critical(ps);
    return rc;
}

int32_t rl_event_post_no_args(void (*handler)(void), uint8_t priority) {
    rl_event_args_t args = {0};
    args.ptrs[0] = (uintptr_t)handler;
    return rl_event_post(rl_call_callback, args, priority);
}

void rl_event_process_pending(void) {
    void (*h)(rl_event_args_t) = NULL;
    rl_event_args_t args;
    for (;;) {
        bool ps = rl_enter_critical();
        uint8_t found = 0;
        for (uint8_t prio = 0; prio < RL_SCHED_EVENT_PRIO_COUNT; ++prio) {
            if (event_dequeue_unsafe(prio, &h, &args) == 0) {
                found = 1;
                break;
            }
        }
        rl_exit_critical(ps);
        if (found == 0 || h == NULL) break;
        h(args);
    }
}

void rl_call_callback(rl_event_args_t args) {
    void (*callback)(void) = (void (*)(void))args.ptrs[0];
    if (callback != NULL) {
        callback();
    }
}