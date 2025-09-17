#ifndef RTOSLESS_LOOP_TIMER_H
#define RTOSLESS_LOOP_TIMER_H

#include <stdint.h>
#include "rtosless_kernel.h"

namespace rl {

    // 🔁 Fixed-interval timer (repeating)
    class loop_interval_t {
    public:
        uint32_t period;
        uint32_t previous;
        bool use_micros;
    public:
        void init_millis(uint32_t ms, uint32_t phase = rl::kernel_millis()) {
            period = ms;
            previous = phase;
            use_micros = false;
        }

        void init_micros(uint32_t us, uint32_t phase = rl::kernel_micros()) {
            period = us;
            previous = phase;
            use_micros = true;
        }

        bool elapsed() {
            if (period == 0 && previous == 0) return false;  // inactive
            uint32_t now = use_micros ? rl::kernel_micros() : rl::kernel_millis();
            if (now - previous >= period) {
                previous = now;
                return true;
            }
            return false;
        }
    };

    // 🕒 One-shot timer (single delay)
    class loop_timer_t {
    public:
        uint32_t start;
        uint32_t duration;
        bool triggered;
        bool use_micros;
    public:
        void start_millis(uint32_t ms) {
            start = rl::kernel_millis();
            duration = ms;
            triggered = true;
            use_micros = false;
        }

        void start_micros(uint32_t us) {
            start = rl::kernel_micros();
            duration = us;
            triggered = true;
            use_micros = true;
        }

        bool elapsed() {
            if (triggered) {
                uint32_t now = use_micros ? rl::kernel_micros() : rl::kernel_millis();
                if (now - start >= duration) {
                    triggered = false;
                    return true;
                }
            }
            return false;
        }
    };

} // namespace rl

// 🧩 Unique name helpers (internal only)
#define __RL_CONCAT(a, b) __RL_CONCAT_INNER(a, b)
#define __RL_CONCAT_INNER(a, b) a##b
#define __RL_UNIQUE(name) __RL_CONCAT(name, __LINE__)

// 🔁 RL_EVERY_MILLIS(ms): executes block every ms
#define RL_EVERY_MILLIS(ms) \
static rl::loop_interval_t __RL_UNIQUE(__every_) = {}; \
if (__RL_UNIQUE(__every_).period == 0) __RL_UNIQUE(__every_).init_millis(ms); \
    if (__RL_UNIQUE(__every_).elapsed())

// 🔁 RL_EVERY_MICROS(us): executes block every us
#define RL_EVERY_MICROS(us) \
static rl::loop_interval_t __RL_UNIQUE(__every_) = {}; \
if (__RL_UNIQUE(__every_).period == 0) __RL_UNIQUE(__every_).init_micros(us); \
    if (__RL_UNIQUE(__every_).elapsed())

#endif // RTOSLESS_LOOP_TIMER_H
