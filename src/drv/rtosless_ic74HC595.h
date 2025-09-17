#ifndef RTOSLESS_DRV_74HC595_H
#define RTOSLESS_DRV_74HC595_H

#ifndef LSBFIRST
#define LSBFIRST 0
#endif

#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#include <stdint.h>
#include "rtosless_gpio.h"

namespace rl::drv {

    typedef uint8_t bit_order_t;


    class ic74HC595 {
    public:
        rl::pin_t data_pin;
        rl::pin_t clock_pin;
        rl::pin_t latch_pin;
        bit_order_t bit_order;

        ic74HC595(rl::pin_t data, rl::pin_t clock, rl::pin_t latch, bit_order_t order = MSBFIRST)
        : data_pin(data), clock_pin(clock), latch_pin(latch), bit_order(order) {}

        void begin_transmission() const {
            rl::gpio_write(latch_pin, LOW);
        }

        void end_transmission() const {
            rl::gpio_write(latch_pin, HIGH);
        }

        void shift_out(uint8_t val) const {
            for (uint8_t i = 0; i < 8; i++)  {
                if (bit_order == LSBFIRST) {
                    rl::gpio_write(data_pin, val & 1);
                    val >>= 1;
                } else {	
                    rl::gpio_write(data_pin, (val & 128) != 0);
                    val <<= 1;
                }

                rl::gpio_write(clock_pin, HIGH);    
                rl::gpio_write(clock_pin, LOW);		
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
