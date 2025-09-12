#ifndef RTOSLESS_SIGNALS_H
#define RTOSLESS_SIGNALS_H

#include "rtosless_async.h"

namespace rl {

// 🔘 auto_reset_signal_t: triggers once, resets after await
class auto_reset_signal_t {
private:
    volatile bool triggered = false;
public:
    inline void trigger() {
        triggered = true;
    }

    task_completion_source_t<void>* await() {
        static task_completion_source_t<void> signal = {};
        if (triggered) {
            triggered = false;
            signal.fulfill();
        }
        return &signal;
    }

    inline bool is_triggered() const {
        return triggered;
    }
};

// 🔘 manual_reset_signal_t: stays triggered until cleared
class manual_reset_signal_t {
private:
    volatile bool triggered = false;
public:
    inline void trigger() {
        triggered = true;
    }

    inline void reset() {
        triggered = false;
    }

    task_completion_source_t<void>* await() {
        static task_completion_source_t<void> signal = {};
        if (triggered && !signal.is_ready()) {
            signal.fulfill();
        }
        return &signal;
    }

    inline bool is_triggered() const {
        return triggered;
    }
};

} // namespace rl
#endif // RTOSLESS_SIGNALS_H
