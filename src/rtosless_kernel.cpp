#include "rtosless.h"
#include "rtosless_hal.h"

namespace rl {

    static volatile uint32_t kernel_millis_;
    static volatile uint32_t kernel_micros_;
    static volatile uint32_t kernel_ticks_;

    uint32_t kernel_millis() {
        #if defined(__AVR__)
        uint32_t value;
        uint8_t sreg = SREG;
        cli();
        value = kernel_millis_;
        SREG = sreg;
        return value;
        #else
        return kernel_millis_;
        #endif
    }

    uint32_t kernel_micros() {
        #if defined(__AVR__)
        uint32_t value;
        uint8_t sreg = SREG;
        cli();
        value = kernel_micros_;
        SREG = sreg;
        return value;
        #else
        return kernel_micros_;
        #endif
    }

    uint32_t kernel_ticks() {
        #if defined(__AVR__)
        uint32_t value;
        uint8_t sreg = SREG;
        cli();
        value = kernel_ticks_;
        SREG = sreg;
        return value;
        #else
        return kernel_ticks_;
        #endif
    }

    void kernel() {
        kernel_millis_ = millis();
        kernel_micros_ = micros();

        timer_process_queue();
        event_process_pending();

        kernel_ticks_++;
    }

}
