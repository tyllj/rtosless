#ifndef RTOSLESS_DEBOUNCE_H
#define RTOSLESS_DEBOUNCE_H

#include <stdint.h>
#include "rtosless_kernel.h"

#ifndef RL_DEBOUNCE_DEFAULT_MS
#define RL_DEBOUNCE_DEFAULT_MS 25
#endif

namespace rl {

class debounced_input_t {
public:
    explicit debounced_input_t(uint32_t debounce_ms = RL_DEBOUNCE_DEFAULT_MS)
        : debounce_ms_(debounce_ms) {}

    bool update(bool raw) {
        if (raw != last_raw_) {
            last_raw_ = raw;
            last_change_ = kernel_millis();
        }
        if ((kernel_millis() - last_change_) >= debounce_ms_ && raw != stable_state_) {
            stable_state_ = raw;
            return true;
        }
        return false;
    }

    bool state(bool raw) {
        if (raw != last_raw_) {
            last_raw_ = raw;
            last_change_ = kernel_millis();
        }
        if ((kernel_millis() - last_change_) >= debounce_ms_) {
            stable_state_ = raw;
        }
        return stable_state_;
    }

    bool rising(bool raw) {
        bool current = state(raw);
        bool edge = (!last_state_ && current);
        last_state_ = current;
        return edge;
    }

    bool falling(bool raw) {
        bool current = state(raw);
        bool edge = (last_state_ && !current);
        last_state_ = current;
        return edge;
    }

private:
    uint32_t debounce_ms_;
    bool last_raw_ = false;
    bool stable_state_ = false;
    bool last_state_ = false;
    uint32_t last_change_ = 0;
};

} // namespace rl

// 🔘 RL_DEBOUNCED(expr): returns true when debounced signal changes
#define RL_DEBOUNCED(expr) \
([]() -> bool { \
    static rl::debounced_input_t debounce; \
    return debounce.update(expr); \
})()

// 🔘 RL_DEBOUNCED_STATE(expr): returns current debounced value
#define RL_DEBOUNCED_STATE(expr) \
([]() -> bool { \
    static rl::debounced_input_t debounce; \
    return debounce.state(expr); \
})()

// 🔼 RL_DEBOUNCED_RISING(expr): returns true on rising edge
#define RL_DEBOUNCED_RISING(expr) \
([]() -> bool { \
    static rl::debounced_input_t debounce; \
    return debounce.rising(expr); \
})()

// 🔽 RL_DEBOUNCED_FALLING(expr): returns true on falling edge
#define RL_DEBOUNCED_FALLING(expr) \
([]() -> bool { \
    static rl::debounced_input_t debounce; \
    return debounce.falling(expr); \
})()

#endif // RTOSLESS_DEBOUNCE_H