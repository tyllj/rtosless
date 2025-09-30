#ifndef RTOSLESS_SIGNALS_H
#define RTOSLESS_SIGNALS_H

#include "rtosless_hal.h"

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// 🔘 rl_signal_t: unified signal type with auto/manual reset modes
// State encoding: lower nibble = triggered (0x01), upper nibble = auto_reset (0x10)
typedef struct {
    volatile uint8_t state;
} rl_signal_t;

#define RL_SIGNAL_TRIGGERED_BIT 0x01
#define RL_SIGNAL_AUTO_RESET_BIT 0x10

// Constructors for different modes
static inline rl_signal_t rl_signal_auto_reset() {
    rl_signal_t s = {RL_SIGNAL_AUTO_RESET_BIT};
    return s;
}

static inline rl_signal_t rl_signal_manual_reset() {
    rl_signal_t s = {0};
    return s;
}

// Core operations
static inline void rl_signal_trigger(rl_signal_t* s) {
    bool ps = rl_enter_critical();
    s->state |= RL_SIGNAL_TRIGGERED_BIT;
    rl_exit_critical(ps);
}

static inline void rl_signal_reset(rl_signal_t* s) {
    bool ps = rl_enter_critical();
    s->state &= ~RL_SIGNAL_TRIGGERED_BIT;
    rl_exit_critical(ps);
}

static inline bool rl_signal_is_triggered(rl_signal_t* s) {
    bool result = false;
    bool ps = rl_enter_critical();
    if (s->state & RL_SIGNAL_TRIGGERED_BIT) {
        result = true;
        // Auto-reset behavior: clear trigger after checking
        if (s->state & RL_SIGNAL_AUTO_RESET_BIT) {
            s->state &= ~RL_SIGNAL_TRIGGERED_BIT;
        }
    }
    rl_exit_critical(ps);
    return result;
}

#ifdef __cplusplus
}
#endif
#endif // RTOSLESS_SIGNALS_H
