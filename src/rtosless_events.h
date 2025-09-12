#ifndef RTOSLESS_EVENTS_H
#define RTOSLESS_EVENTS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
    #endif

    #define SCHED_EVENT_PRIO_COUNT 2
    #define SCHED_EVENT_QUEUE_LEN  16

    typedef union {
        uintptr_t ptrs[2];
        uint8_t   bytes[16];
        int32_t   i32[4];
        uint32_t  u32[4];
        int64_t   i64[2];
        uint64_t  u64[2];
    } event_args_t;

    int32_t event_post(void (*handler)(event_args_t), event_args_t args, uint8_t priority);
    int32_t event_post_no_args(void (*handler)(void), uint8_t priority);

    void event_process_pending(void);
    void call_callback(event_args_t args);

    #ifdef __cplusplus
}
#endif

// -------------------- C++ Extensions --------------------
#ifdef __cplusplus

namespace {
    // Trampoline for member functions
    template<typename T>
    void event_trampoline_method(event_args_t args) {
        T* instance = reinterpret_cast<T*>(args.ptrs[0]);
        void (T::*method)() = reinterpret_cast<void (T::*)()>(args.ptrs[1]);
        (instance->*method)();
    }

    // Post a member function
    template<typename T>
    int32_t event_post_member(T* instance, void (T::*method)(), uint8_t priority) {
        event_args_t args = {};
        args.ptrs[0] = reinterpret_cast<uintptr_t>(instance);
        args.ptrs[1] = reinterpret_cast<uintptr_t>(method);
        return event_post(&event_trampoline_method<T>, args, priority);
    }

    // Trampoline for lambdas or functors
    template<typename Callable>
    void event_trampoline_callable(event_args_t args) {
        Callable* fn = reinterpret_cast<Callable*>(args.ptrs[0]);
        (*fn)();
    }

    // Post a lambda or functor (must persist externally)
    template<typename Callable>
    int32_t event_post_callable(Callable* fn, uint8_t priority) {
        event_args_t args = {};
        args.ptrs[0] = reinterpret_cast<uintptr_t>(fn);
        return event_post(&event_trampoline_callable<Callable>, args, priority);
    }
}

#endif // __cplusplus

#endif // RTOSLESS_EVENTS_H
