#ifndef RTOSLESS_DRV_74HC595_H
#define RTOSLESS_DRV_74HC595_H

#ifndef LSBFIRST
#define LSBFIRST 0
#endif

#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#include <stdint.h>
#include <stdbool.h>
#include "../rtosless_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef uint8_t rl_bit_order_t;

    typedef struct {
        rl_pin_t data_pin;
        rl_pin_t clock_pin;
        rl_pin_t latch_pin;
        rl_bit_order_t bit_order;
    } rl_ic74hc595_t;

    // Constructor functions
    rl_ic74hc595_t rl_ic74hc595_create(rl_pin_t data, rl_pin_t clock, rl_pin_t latch, rl_bit_order_t order);

    // Core operations
    void rl_ic74hc595_setup_pins(const rl_ic74hc595_t* ic);
    void rl_ic74hc595_begin_transmission(const rl_ic74hc595_t* ic);
    void rl_ic74hc595_end_transmission(const rl_ic74hc595_t* ic);
    void rl_ic74hc595_shift_out(const rl_ic74hc595_t* ic, uint8_t val);

#ifdef __cplusplus
}
#endif

#endif // RTOSLESS_DRV_74HC595_H
