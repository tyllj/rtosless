#ifndef RTOSLESS_EVENTS_H
#define RTOSLESS_EVENTS_H

#include <stdint.h>

#define RL_SCHED_EVENT_PRIO_COUNT 2
#define RL_SCHED_EVENT_QUEUE_LEN  16

/* Event argument union - compatible with both C and C++ */
typedef union {
    uintptr_t ptrs[2];
    uint8_t   bytes[16];
    int32_t   i32[4];
    uint32_t  u32[4];
    int64_t   i64[2];
    uint64_t  u64[2];
} rl_event_args_t;

#ifdef __cplusplus
extern "C" {
#endif

int32_t rl_event_post(void (*handler)(rl_event_args_t), rl_event_args_t args, uint8_t priority);
int32_t rl_event_post_no_args(void (*handler)(void), uint8_t priority);
void rl_event_process_pending(void);
void rl_call_callback(rl_event_args_t args);

#ifdef __cplusplus
}

/* C++ template functions - all use rl_ prefix */
#ifdef __cplusplus

// Trampoline for member functions
template<typename T>
void rl_event_trampoline_method(rl_event_args_t args) {
    T* instance = reinterpret_cast<T*>(args.ptrs[0]);
    void (T::*method)() = reinterpret_cast<void (T::*)()>(args.ptrs[1]);
    if (instance && method)
        (instance->*method)();
}

// Post a member function
template<typename T>
int32_t rl_event_post_member(T* instance, void (T::*method)(), uint8_t priority) {
    rl_event_args_t args = {};
    args.ptrs[0] = reinterpret_cast<uintptr_t>(instance);
    args.ptrs[1] = reinterpret_cast<uintptr_t>(method);
    return rl_event_post(&rl_event_trampoline_method<T>, args, priority);
}

// Trampoline for lambdas or functors
template<typename Callable>
void rl_event_trampoline_callable(rl_event_args_t args) {
    Callable* fn = reinterpret_cast<Callable*>(args.ptrs[0]);
    (*fn)();
}

// Post a lambda or functor (must persist externally)
template<typename Callable>
int32_t rl_event_post_callable(Callable* fn, uint8_t priority) {
    rl_event_args_t args = {};
    args.ptrs[0] = reinterpret_cast<uintptr_t>(fn);
    return rl_event_post(&rl_event_trampoline_callable<Callable>, args, priority);
}
#endif

#endif // RTOSLESS_EVENTS_H


#endif // RTOSLESS_EVENTS_H
