#ifndef RL_RTOSLESS_ASYNC_H
#define RL_RTOSLESS_ASYNC_H

#include "rtosless_events.h"
#include "rtosless_timer.h"
#include <stdint.h>

namespace rl {

    // 📬 ISR-safe task completion source
    template<typename T>
    struct task_completion_source_t {
        volatile bool completed = false;
        T result;

        inline void fulfill(T val) {
            result = val;
            completed = true;
        }

        inline void fulfill() {
            completed = true;
        }

        inline bool is_ready() const {
            return completed;
        }

        inline void reset() {
            completed = false;
        }
    };

    // 📬 Specialization for void
    template<>
    struct task_completion_source_t<void> {
        volatile bool completed = false;

        inline void fulfill() {
            completed = true;
        }

        inline bool is_ready() const {
            return completed;
        }

        inline void reset() {
            completed = false;
        }
    };

} // namespace rl

// 🧵 Define a coroutine with internal task_completion_source_t<T>
#define RL_ASYNC_FN(name, return_type, ...) \
rl::task_completion_source_t<return_type>* name##_entry(__VA_ARGS__) { \
    static bool __initialized = false; \
    static int __state = 0; \
    static bool __completed = false; \
    static void (*__resume)() = name##_resume; \
    static rl::task_completion_source_t<return_type> __self = {}; \
    if (!__initialized) { \
        __initialized = true; \
        static __VA_ARGS__; \
    } \
    name##_resume(); \
    return &__self; \
} \
void name##_resume() { \
    switch (__state) { case 0:

        // ⏳ Await macro (returns result from task_completion_source_t<T> or pointer)
        #define RL_ASYNC_AWAIT(awaitable_or_ptr) \
        ({ \
            auto* __ptr = __builtin_types_compatible_p(typeof(awaitable_or_ptr), rl::task_completion_source_t<void>*) \
            ? awaitable_or_ptr \
            : &(awaitable_or_ptr); \
            if (__ptr && !__ptr->is_ready()) { \
                __resume = __func__; \
                __state = __LINE__; return {}; case __LINE__:; \
            } \
            __ptr->result; \
        })

        // ⏱️ Delay macro (non-blocking)
        #define RL_ASYNC_DELAY(ms) \
        do { \
            static uint32_t __delay_start = 0; \
            if (__delay_start == 0) { \
                __delay_start = rl::kernel_millis(); \
                __resume = __func__; \
                __state = __LINE__; return; case __LINE__:; \
            } \
            if (rl::kernel_millis() - __delay_start < (ms)) { \
                __resume = __func__; \
                __state = __LINE__; return; case __LINE__:; \
            } \
            __delay_start = 0; \
        } while (0)

        #define RL_ASYNC_DELAY_MICROS(us) \
        do { \
            static uint32_t __delay_start = 0; \
            if (__delay_start == 0) { \
                __delay_start = rl::kernel_micros(); \
                __resume = __func__; \
                __state = __LINE__; return; case __LINE__:; \
            } \
            if (rl::kernel_micros() - __delay_start < (us)) { \
                __resume = __func__; \
                __state = __LINE__; return; case __LINE__:; \
            } \
            __delay_start = 0; \
        } while (0)

        // ✅ Return macro (handles void and non-void)
        #define RL_ASYNC_RETURN(val) \
        do { \
            __completed = true; \
            if constexpr (!__builtin_types_compatible_p(typeof(val), void)) { \
                __self.fulfill(val); \
            } else { \
                __self.fulfill(); \
            } \
            return; \
        } while (0)

        // ✅ End macro (for void-returning coroutines)
        #define RL_ASYNC_END \
    } __completed = true; __self.fulfill(); }

    // 🔁 Yield until condition is true
    #define RL_ASYNC_YIELD_UNTIL(expr) \
    do { \
        if (!(expr)) { \
            __resume = __func__; \
            __state = __LINE__; return; case __LINE__:; \
        } \
    } while (0)

    // 🚀 Run macro (returns task_completion_source_t<T>*)
    #define RL_ASYNC_RUN(name, ...) name##_entry(__VA_ARGS__)

    // 🔍 Completion check macro
    #define RL_ASYNC_IS_COMPLETED(awaitable_or_ptr) \
    ((typeof(awaitable_or_ptr)*)(&(awaitable_or_ptr)))->is_ready()

    #endif // RL_RTOSLESS_ASYNC_H
