
#ifndef RTOSLESS_H
#define RTOSLESS_H

#include "rtosless_hal.h"
#include "rtosless_timer.h"
#include "rtosless_events.h"
#include "rtosless_async.h"

extern "C" {
    inline void rtosless() {
        timer_process_queue();
        event_process_pending();
    }
}

#endif // RTOSLESS_H
