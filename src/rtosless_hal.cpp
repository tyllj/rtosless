#include "rtosless_hal.h"

#if defined(__AVR__) || defined(ARDUINO_ARCH_AVR)
#include <avr/interrupt.h>
#elif defined(__arm__) || defined(__ARM_ARCH)
#include "cmsis_gcc.h"
#endif

extern "C" {

    uint32_t rtosless_enter_critical(void) {
        #if defined(__AVR__) || defined(ARDUINO_ARCH_AVR)
        uint8_t sreg = SREG;
        cli();
        return (sreg & (uint8_t)_BV(SREG_I)) ? 0u : 1u;

        #elif defined(__riscv) || defined(ARDUINO_ARCH_ESP32C3)
        uint32_t mstatus;
        __asm volatile ("csrr %0, mstatus" : "=r"(mstatus));
        __asm volatile ("csrci mstatus, 8");
        return (mstatus & 0x8u) ? 0u : 1u;

        #elif defined(__arm__) || defined(__ARM_ARCH)
        uint32_t primask;
        __asm volatile ("MRS %0, PRIMASK" : "=r"(primask));
        __asm volatile ("cpsid i");
        return primask & 0x1u;

        #else
        noInterrupts();
        return 0u;
        #endif
    }

    void rtosless_exit_critical(uint32_t prev) {
        #if defined(__AVR__) || defined(ARDUINO_ARCH_AVR)
        if ((prev & 0x1u) == 0u) sei();

        #elif defined(__riscv) || defined(ARDUINO_ARCH_ESP32C3)
        if ((prev & 0x1u) == 0u) __asm volatile ("csrsi mstatus, 8");

        #elif defined(__arm__) || defined(__ARM_ARCH)
        if ((prev & 0x1u) == 0u) __asm volatile ("cpsie i");

        #else
        if ((prev & 0x1u) == 0u) interrupts();
        #endif
    }

}
