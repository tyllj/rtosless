#ifndef RTOSLESS_LOOP_TIMER_H
#define RTOSLESS_LOOP_TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include "rtosless_kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 🔁 Fixed-interval timer (repeating)
    typedef struct {
        uint32_t period;
        uint32_t previous;
        bool use_micros;
    } rl_loop_interval_t;

    static inline void rl_loop_interval_init_millis(rl_loop_interval_t* timer, uint32_t ms, uint32_t phase) {
        timer->period = ms;
        timer->previous = phase;
        timer->use_micros = false;
    }

    static inline void rl_loop_interval_init_millis_now(rl_loop_interval_t* timer, uint32_t ms) {
        rl_loop_interval_init_millis(timer, ms, rl_millis());
    }

    static inline void rl_loop_interval_init_micros(rl_loop_interval_t* timer, uint32_t us, uint32_t phase) {
        timer->period = us;
        timer->previous = phase;
        timer->use_micros = true;
    }

    static inline void rl_loop_interval_init_micros_now(rl_loop_interval_t* timer, uint32_t us) {
        rl_loop_interval_init_micros(timer, us, rl_micros());
    }

    static inline bool rl_loop_interval_elapsed(rl_loop_interval_t* timer) {
        if (timer->period == 0 && timer->previous == 0) return false;  // inactive
        uint32_t now = timer->use_micros ? rl_micros() : rl_millis();
        if (now - timer->previous >= timer->period) {
            timer->previous = now;
            return true;
        }
        return false;
    }

    // 🕒 One-shot timer (single delay)
    typedef struct {
        uint32_t start;
        uint32_t duration;
        bool triggered;
        bool use_micros;
    } rl_loop_timer_t;

    static inline void rl_loop_timer_start_millis(rl_loop_timer_t* timer, uint32_t ms) {
        timer->start = rl_millis();
        timer->duration = ms;
        timer->triggered = true;
        timer->use_micros = false;
    }

    static inline void rl_loop_timer_start_micros(rl_loop_timer_t* timer, uint32_t us) {
        timer->start = rl_micros();
        timer->duration = us;
        timer->triggered = true;
        timer->use_micros = true;
    }

    static inline bool rl_loop_timer_elapsed(rl_loop_timer_t* timer) {
        if (timer->triggered) {
            uint32_t now = timer->use_micros ? rl_micros() : rl_millis();
            if (now - timer->start >= timer->duration) {
                timer->triggered = false;
                return true;
            }
        }
        return false;
    }

#ifdef __cplusplus
}
#endif

// 🧩 Unique name helpers (internal only)
#define __RL_CONCAT(a, b) __RL_CONCAT_INNER(a, b)
#define __RL_CONCAT_INNER(a, b) a##b
#define __RL_UNIQUE(name) __RL_CONCAT(name, __LINE__)

// 🔁 RL_EVERY_MILLIS(ms): executes block every ms
#define RL_EVERY_MILLIS(ms) \
static rl_loop_interval_t __RL_UNIQUE(__every_) = {0}; \
if (__RL_UNIQUE(__every_).period == 0) rl_loop_interval_init_millis_now(&__RL_UNIQUE(__every_), ms); \
    if (rl_loop_interval_elapsed(&__RL_UNIQUE(__every_)))

// 🔁 RL_EVERY_MICROS(us): executes block every us
#define RL_EVERY_MICROS(us) \
static rl_loop_interval_t __RL_UNIQUE(__every_) = {0}; \
if (__RL_UNIQUE(__every_).period == 0) rl_loop_interval_init_micros_now(&__RL_UNIQUE(__every_), us); \
    if (rl_loop_interval_elapsed(&__RL_UNIQUE(__every_)))

#endif // RTOSLESS_LOOP_TIMER_H
