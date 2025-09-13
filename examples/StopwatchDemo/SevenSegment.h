#ifndef SG_SEVENSEGMENT_H
#define SG_SEVENSEGMENT_H

#include <stdint.h>
#include <rtosless_gpio.h>
#include <rtosless_timer.h>
#include <drv/rtosless_ic74HC595.h>
#include <avr/pgmspace.h>

namespace SG {

    class SevenSegment {
    public:
        SevenSegment(rl::pin_t data, rl::pin_t shiftClock, rl::pin_t storageClock);
        void init();
        void setChar(uint8_t index, char character);
        void clearChar(uint8_t index) { setChar(index, 0); }
        void setDot(uint8_t index, uint8_t enabled);
        void setDot(uint8_t index) { setDot(index, 1); }
        void clearDot(uint8_t index) { setDot(index, 0); }
        void refresh();

    private:
        rl::drv::ic74HC595 _shift;
        rl::pin_t _storageClock;
        volatile uint8_t _chars[4];
        volatile uint8_t _points;
        volatile uint8_t _n;
        uint8_t _plex[4];
    };

} // namespace SG

#endif // SG_SEVENSEGMENT_H
