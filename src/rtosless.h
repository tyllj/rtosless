
#ifndef RTOSLESS_H
#define RTOSLESS_H

#include "rtosless_hal.h"
#include "rtosless_timer.h"
#include "rtosless_events.h"
#include "rtosless_async.h"
#include "rtosless_gpio.h"
#include "rtosless_pins.h"
#include "rtosless_signal.h"
#include "rtosless_loop_timer.h"
#include "rtosless_states.h"


namespace rl {

    uint32_t kernel_millis();
    uint32_t kernel_micros();
    uint32_t kernel_ticks();

    void kernel();
}

#endif // RTOSLESS_H
