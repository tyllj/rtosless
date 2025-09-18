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
    struct name##_state_t { \
        bool initialized = false; \
        int state = 0; \
        bool completed = false; \
        rl::task_completion_source_t<return_type> self = {}; \
        void (*resume)() = name##_resume; \
        /* User variables can be added here if needed */ \
    }; \
    static name##_state_t name##_state; \
    rl::task_completion_source_t<return_type>* name##_entry(__VA_ARGS__) { \
        if (!name##_state.initialized) { \
            name##_state.initialized = true; \
            /* User variables initialization if needed */ \
        } \
        name##_resume(); \
        return &name##_state.self; \
    } \
    void name##_resume() { \
        switch (name##_state.state) { case 0:

        // ⏳ Await macro (returns result from task_completion_source_t<T> or pointer)
        #define RL_ASYNC_AWAIT(awaitable_or_ptr) \
        ({ \
            auto* __ptr = __builtin_types_compatible_p(typeof(awaitable_or_ptr), rl::task_completion_source_t<void>*) \
            ? awaitable_or_ptr \
            : &(awaitable_or_ptr); \
            if (__ptr && !__ptr->is_ready()) { \
                name##_state.resume = __func__; \
                name##_state.state = __LINE__; return {}; case __LINE__:; \
            } \
            __ptr->result; \
        })

        // ⏱️ Delay macro (non-blocking)
        #define RL_ASYNC_DELAY(ms) \
        do { \
            static uint32_t __delay_start = 0; \
            if (__delay_start == 0) { \
                __delay_start = rl::kernel_millis(); \
                name##_state.resume = __func__; \
                name##_state.state = __LINE__; return; case __LINE__:; \
            } \
            if (rl::kernel_millis() - __delay_start < (ms)) { \
                name##_state.resume = __func__; \
                name##_state.state = __LINE__; return; case __LINE__:; \
            } \
            __delay_start = 0; \
        } while (0)

        #define RL_ASYNC_DELAY_MICROS(us) \
        do { \
            static uint32_t __delay_start = 0; \
            if (__delay_start == 0) { \
                __delay_start = rl::kernel_micros(); \
                name##_state.resume = __func__; \
                name##_state.state = __LINE__; return; case __LINE__:; \
            } \
            if (rl::kernel_micros() - __delay_start < (us)) { \
                name##_state.resume = __func__; \
                name##_state.state = __LINE__; return; case __LINE__:; \
            } \
            __delay_start = 0; \
        } while (0)

        // ✅ Return macro (handles void and non-void)
        #define RL_ASYNC_RETURN(val) \
        do { \
            name##_state.completed = true; \
            if constexpr (!__builtin_types_compatible_p(typeof(val), void)) { \
                name##_state.self.fulfill(val); \
            } else { \
                name##_state.self.fulfill(); \
            } \
            return; \
        } while (0)

        // ✅ End macro (for void-returning coroutines)
        #define RL_ASYNC_END \
    } name##_state.completed = true; name##_state.self.fulfill(); }

    // 🔁 Yield until condition is true
    #define RL_ASYNC_YIELD_UNTIL(expr) \
    do { \
        if (!(expr)) { \
            name##_state.resume = __func__; \
            name##_state.state = __LINE__; return; case __LINE__:; \
        } \
    } while (0)

    // 🚀 Run macro (returns task_completion_source_t<T>*)
    #define RL_ASYNC_RUN(name, ...) name##_entry(__VA_ARGS__)

    // 🔍 Completion check macro
    #define RL_ASYNC_IS_COMPLETED(awaitable_or_ptr) \
    ((typeof(awaitable_or_ptr)*)(&(awaitable_or_ptr)))->is_ready()

    #endif // RL_RTOSLESS_ASYNC_H
