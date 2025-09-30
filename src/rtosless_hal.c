#include "rtosless_hal.h"

#if defined(__AVR__) || defined(ARDUINO_ARCH_AVR)
#include <avr/interrupt.h>
#elif defined(__arm__) || defined(__ARM_ARCH)
#include "cmsis_gcc.h"
#endif

bool rl_enter_critical(void) {
        #if defined(__AVR__) || defined(ARDUINO_ARCH_AVR)
        uint8_t sreg = SREG;
        cli();
        return (sreg & (uint8_t)_BV(SREG_I)) != 0; // Return true if interrupts were enabled

        #elif defined(__riscv) || defined(ARDUINO_ARCH_ESP32C3)
        uint32_t mstatus;
        __asm volatile ("csrr %0, mstatus" : "=r"(mstatus));
        __asm volatile ("csrci mstatus, 8");
        return (mstatus & 0x8u) != 0; // Return true if interrupts were enabled

        #elif defined(__arm__) || defined(__ARM_ARCH)
        uint32_t primask;
        __asm volatile ("MRS %0, PRIMASK" : "=r"(primask));
        __asm volatile ("cpsid i");
        return (primask & 0x1u) == 0; // PRIMASK=0 means interrupts enabled

        #else
        // No critical section support for this platform
        return false;
        #endif
    }

    void rl_exit_critical(bool prev) {
        #if defined(__AVR__) || defined(ARDUINO_ARCH_AVR)
        if (prev) sei(); // Re-enable interrupts if they were enabled before

        #elif defined(__riscv) || defined(ARDUINO_ARCH_ESP32C3)
        if (prev) __asm volatile ("csrsi mstatus, 8"); // Re-enable interrupts

        #elif defined(__arm__) || defined(__ARM_ARCH)
        if (prev) __asm volatile ("cpsie i"); // Re-enable interrupts

        #else
        // No critical section support for this platform
        (void)prev; // Suppress unused parameter warning
        #endif
    }
