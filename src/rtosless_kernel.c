#include "rtosless_hal.h"
#include "rtosless_timer.h"
#include "rtosless_events.h"

static volatile uint32_t rl_millis_;
static volatile uint32_t rl_micros_;
static volatile uint32_t rl_cycles_;

uint32_t rl_millis(void) {
    #if defined(__AVR__) || defined(ARDUINO_ARCH_AVR)
    bool ps = rl_enter_critical();
    uint32_t value = rl_millis_;
    rl_exit_critical(ps);
    return value;
    #else
    // 32-bit read is atomic on 32-bit processors
    return rl_millis_;
    #endif
}

uint32_t rl_micros(void) {
    #if defined(__AVR__) || defined(ARDUINO_ARCH_AVR)
    bool ps = rl_enter_critical();
    uint32_t value = rl_micros_;
    rl_exit_critical(ps);
    return value;
    #else
    // 32-bit read is atomic on 32-bit processors
    return rl_micros_;
    #endif
}

uint32_t rl_cycles(void) {
    #if defined(__AVR__) || defined(ARDUINO_ARCH_AVR)
    bool ps = rl_enter_critical();
    uint32_t value = rl_cycles_;
    rl_exit_critical(ps);
    return value;
    #else
    // 32-bit read is atomic on 32-bit processors
    return rl_cycles_;
    #endif
}

void rl_kernel(uint32_t millis, uint32_t micros) {
    #if defined(__AVR__) || defined(ARDUINO_ARCH_AVR)
    bool ps = rl_enter_critical();
    #endif
    
    rl_millis_ = millis;
    rl_micros_ = micros;
    rl_cycles_++;
    
    #if defined(__AVR__) || defined(ARDUINO_ARCH_AVR)
    rl_exit_critical(ps);
    #endif

    rl_timer_process_queue();
    rl_event_process_pending();
}