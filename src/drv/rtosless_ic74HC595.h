#ifndef RTOSLESS_DRV_74HC595_H
#define RTOSLESS_DRV_74HC595_H

#include <stdint.h>
#include "rtosless_gpio.h"

namespace rl::drv {

    enum class bit_order_t : uint8_t {
        LSBFIRST = 0,
        MSBFIRST = 1
    };

    class ic74HC595 {
    public:
        rl::pin_t data_pin;
        rl::pin_t clock_pin;
        rl::pin_t latch_pin;
        bit_order_t bit_order;

        ic74HC595(rl::pin_t data, rl::pin_t clock, rl::pin_t latch, bit_order_t order = bit_order_t::MSBFIRST)
        : data_pin(data), clock_pin(clock), latch_pin(latch), bit_order(order) {}

        void begin_transmission() const {
            rl::gpio_write(latch_pin, false);
        }

        void end_transmission() const {
            rl::gpio_write(latch_pin, true);
        }

        void shift_out(uint8_t val) const {
            for (uint8_t i = 0; i < 8; ++i) {
                bool bit = (bit_order == bit_order_t::LSBFIRST)
                ? (val >> i) & 0x01
                : (val >> (7 - i)) & 0x01;

                rl::gpio_write(data_pin, bit);
                rl::gpio_write(clock_pin, true);
                rl::gpio_write(clock_pin, false);
            }
        }

        void setup_pins() const {
            rl::gpio_pin_mode(data_pin, rl::gpio_mode::output);
            rl::gpio_pin_mode(clock_pin, rl::gpio_mode::output);
            rl::gpio_pin_mode(latch_pin, rl::gpio_mode::output);
        }
    };

} // namespace rl::drv

#endif // RTOSLESS_DRV_74HC595_H
