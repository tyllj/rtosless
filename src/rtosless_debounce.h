#ifndef RTOSLESS_DEBOUNCE_H
#define RTOSLESS_DEBOUNCE_H

#include <stdint.h>
#include <stdbool.h>
#include "rtosless_kernel.h"

#ifndef RL_DEBOUNCE_DEFAULT_MS
#define RL_DEBOUNCE_DEFAULT_MS 25
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rl_debounced_input {
    uint32_t debounce_ms;
    bool last_raw;
    bool stable_state;
    bool last_state;
    uint32_t last_change;
} rl_debounced_input_t;

// 🔧 Constructor-like initializer
static inline rl_debounced_input_t rl_debounced_input_init(uint32_t debounce_ms) {
    rl_debounced_input_t d = {
        .debounce_ms = debounce_ms,
        .last_raw = false,
        .stable_state = false,
        .last_state = false,
        .last_change = 0
    };
    return d;
}

// 🔘 Update: returns true if debounced signal changes
static inline bool rl_debounced_input_update(rl_debounced_input_t *d, bool raw) {
    if (raw != d->last_raw) {
        d->last_raw = raw;
        d->last_change = rl_millis();
    }
    if ((rl_millis() - d->last_change) >= d->debounce_ms && raw != d->stable_state) {
        d->stable_state = raw;
        return true;
    }
    return false;
}

// 🔘 State: returns current debounced value
static inline bool rl_debounced_input_state(rl_debounced_input_t *d, bool raw) {
    if (raw != d->last_raw) {
        d->last_raw = raw;
        d->last_change = rl_millis();
    }
    if ((rl_millis() - d->last_change) >= d->debounce_ms) {
        d->stable_state = raw;
    }
    return d->stable_state;
}

// 🔼 Rising edge detection
static inline bool rl_debounced_input_rising(rl_debounced_input_t *d, bool raw) {
    bool current = rl_debounced_input_state(d, raw);
    bool edge = (!d->last_state && current);
    d->last_state = current;
    return edge;
}

// 🔽 Falling edge detection
static inline bool rl_debounced_input_falling(rl_debounced_input_t *d, bool raw) {
    bool current = rl_debounced_input_state(d, raw);
    bool edge = (d->last_state && !current);
    d->last_state = current;
    return edge;
}

#ifdef __cplusplus
}
#endif

// ============================================================
// Macros using GCC statement-expressions to emulate lambdas
// ============================================================

// 🔘 RL_DEBOUNCED(expr): returns true when debounced signal changes
#define RL_DEBOUNCED(expr) \
({ \
    static rl_debounced_input_t debounce = { .debounce_ms = RL_DEBOUNCE_DEFAULT_MS }; \
    rl_debounced_input_update(&debounce, (expr)); \
})

// 🔘 RL_DEBOUNCED_STATE(expr): returns current debounced value
#define RL_DEBOUNCED_STATE(expr) \
({ \
    static rl_debounced_input_t debounce = { .debounce_ms = RL_DEBOUNCE_DEFAULT_MS }; \
    rl_debounced_input_state(&debounce, (expr)); \
})

// 🔼 RL_DEBOUNCED_RISING(expr): returns true on rising edge
#define RL_DEBOUNCED_RISING(expr) \
({ \
    static rl_debounced_input_t debounce = { .debounce_ms = RL_DEBOUNCE_DEFAULT_MS }; \
    rl_debounced_input_rising(&debounce, (expr)); \
})

// 🔽 RL_DEBOUNCED_FALLING(expr): returns true on falling edge
#define RL_DEBOUNCED_FALLING(expr) \
({ \
    static rl_debounced_input_t debounce = { .debounce_ms = RL_DEBOUNCE_DEFAULT_MS }; \
    rl_debounced_input_falling(&debounce, (expr)); \
})

#endif // RTOSLESS_DEBOUNCE_H
