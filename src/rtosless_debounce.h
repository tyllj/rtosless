#ifndef RTOSLESS_DEBOUNCE_H
#define RTOSLESS_DEBOUNCE_H

#include <stdint.h>
#include <Arduino.h>

// 🧩 Unique name helpers (internal only)
#define __RTOSLESS_CONCAT(a, b) a##b
#define __RTOSLESS_UNIQUE(name) __RTOSLESS_CONCAT(name, __LINE__)

// 🔘 RL_DEBOUNCED(expr, ms): returns true when debounced signal changes
#define RL_DEBOUNCED(expr, ms) \
([]() -> bool { \
    static bool __RTOSLESS_UNIQUE(last_raw) = (expr); \
    static bool __RTOSLESS_UNIQUE(stable_state) = (expr); \
    static uint32_t __RTOSLESS_UNIQUE(last_change) = rl::kernel_millis(); \
    bool raw = (expr); \
    if (raw != __RTOSLESS_UNIQUE(last_raw)) { \
        __RTOSLESS_UNIQUE(last_raw) = raw; \
        __RTOSLESS_UNIQUE(last_change) = rl::kernel_millis(); \
    } \
    if ((rl::kernel_millis() - __RTOSLESS_UNIQUE(last_change)) >= (ms) && raw != __RTOSLESS_UNIQUE(stable_state)) { \
        __RTOSLESS_UNIQUE(stable_state) = raw; \
        return true; \
    } \
    return false; \
})()

// 🔘 RL_DEBOUNCED_STATE(expr, ms): returns current debounced value
#define RL_DEBOUNCED_STATE(expr, ms) \
([]() -> bool { \
    static bool __RTOSLESS_UNIQUE(last_raw) = (expr); \
    static bool __RTOSLESS_UNIQUE(stable_state) = (expr); \
    static uint32_t __RTOSLESS_UNIQUE(last_change) = rl::kernel_millis(); \
    bool raw = (expr); \
    if (raw != __RTOSLESS_UNIQUE(last_raw)) { \
        __RTOSLESS_UNIQUE(last_raw) = raw; \
        __RTOSLESS_UNIQUE(last_change) = rl::kernel_millis(); \
    } \
    if ((rl::kernel_millis() - __RTOSLESS_UNIQUE(last_change)) >= (ms)) { \
        __RTOSLESS_UNIQUE(stable_state) = raw; \
    } \
    return __RTOSLESS_UNIQUE(stable_state); \
})()

// 🔼 RL_DEBOUNCED_RISING(expr, ms): returns true on rising edge
#define RL_DEBOUNCED_RISING(expr, ms) \
([]() -> bool { \
    static bool __RTOSLESS_UNIQUE(last_state) = (expr); \
    bool current = RL_DEBOUNCED_STATE(expr, ms); \
    bool rising = (!__RTOSLESS_UNIQUE(last_state) && current); \
    __RTOSLESS_UNIQUE(last_state) = current; \
    return rising; \
})()

// 🔽 RL_DEBOUNCED_FALLING(expr, ms): returns true on falling edge
#define RL_DEBOUNCED_FALLING(expr, ms) \
([]() -> bool { \
    static bool __RTOSLESS_UNIQUE(last_state) = (expr); \
    bool current = RL_DEBOUNCED_STATE(expr, ms); \
    bool falling = (__RTOSLESS_UNIQUE(last_state) && !current); \
    __RTOSLESS_UNIQUE(last_state) = current; \
    return falling; \
})()

#endif // RTOSLESS_DEBOUNCE_H
