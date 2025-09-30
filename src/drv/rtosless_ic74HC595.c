#include "rtosless_ic74HC595.h"

// Constructor functions
rl_ic74hc595_t rl_ic74hc595_create(rl_pin_t data, rl_pin_t clock, rl_pin_t latch, rl_bit_order_t order) {
    rl_ic74hc595_t ic = {
        .data_pin = data,
        .clock_pin = clock,
        .latch_pin = latch,
        .bit_order = order
    };
    return ic;
}

// Core operations
void rl_ic74hc595_setup_pins(const rl_ic74hc595_t* ic) {
    rl_gpio_pin_mode(ic->data_pin, OUTPUT);
    rl_gpio_pin_mode(ic->clock_pin, OUTPUT);
    rl_gpio_pin_mode(ic->latch_pin, OUTPUT);
}

void rl_ic74hc595_begin_transmission(const rl_ic74hc595_t* ic) {
    rl_gpio_write(ic->latch_pin, LOW);
}

void rl_ic74hc595_end_transmission(const rl_ic74hc595_t* ic) {
    rl_gpio_write(ic->latch_pin, HIGH);
}

void rl_ic74hc595_shift_out(const rl_ic74hc595_t* ic, uint8_t val) {
    for (uint8_t i = 0; i < 8; i++) {
        if (ic->bit_order == LSBFIRST) {
            rl_gpio_write(ic->data_pin, val & 1);
            val >>= 1;
        } else {
            rl_gpio_write(ic->data_pin, (val & 128) != 0);
            val <<= 1;
        }

        rl_gpio_write(ic->clock_pin, HIGH);    
        rl_gpio_write(ic->clock_pin, LOW);
    }
}