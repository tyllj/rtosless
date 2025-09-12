#ifndef RTOSLESS_LOOP_TIMER_H
#define RTOSLESS_LOOP_TIMER_H

#include <stdint.h>
#include <Arduino.h>

namespace rl {

    // 🔁 Fixed-interval timer (repeating)
    struct loop_interval_t {
        uint64_t period;
        uint64_t previous;
        bool use_micros;

        void init_millis(uint64_t ms, uint64_t phase = millis()) {
            period = ms;
            previous = phase;
            use_micros = false;
        }

        void init_micros(uint64_t us, uint64_t phase = micros()) {
            period = us;
            previous = phase;
            use_micros = true;
        }

        bool elapsed() {
            if (period == 0 && previous == 0) return false;  // inactive
            uint64_t now = use_micros ? micros() : millis();
            if (now - previous >= period) {
                previous = now;
                return true;
            }
            return false;
        }
    };

    // 🕒 One-shot timer (single delay)
    struct loop_timer_t {
        uint64_t start;
        uint64_t duration;
        bool triggered;
        bool use_micros;

        void start_millis(uint64_t ms) {
            start = millis();
            duration = ms;
            triggered = true;
            use_micros = false;
        }

        void start_micros(uint64_t us) {
            start = micros();
            duration = us;
            triggered = true;
            use_micros = true;
        }

        bool elapsed() {
            if (triggered) {
                uint64_t now = use_micros ? micros() : millis();
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
#define __RL_CONCAT(a, b) a##b
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
