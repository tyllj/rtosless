#include <avr/pgmspace.h>
#include <rtosless.h>
#include <rtosless_timer.h>

#include "SevenSegment.h"

/*
 *   0
 *  5 1
 *   6
 *  4 2
 *   3 7
 */
static const PROGMEM uint8_t SG_SevenSegment_font[128] = {
//    76543210
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b10000010, // !
    0b00100010, // "
    0b00000000, // #
    0b00000000, // $
    0b00000000, // %
    0b00000000, // &
    0b00100000, // '
    0b00000000, // (
    0b00000000, // )
    0b00000000, // *
    0b00000000, // +
    0b10000000, // ,
    0b01000000, // -
    0b10000000, // .
    0b00000000, // /
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
    0b10000100, // :
    0b10000100, // ;
    0b00000000, // <
    0b01001000, // =
    0b00000000, // >
    0b00110011, // ?
    0b00000000, // @
    0b01110111, // A
    0b01111100, // B
    0b00111001, // C
    0b01011110, // D
    0b01111001, // E
    0b01110001, // F
    0b00111101, // G
    0b01110110, // H
    0b00110000, // I
    0b00111100, // J
    0b01011011, // K
    0b00111000, // L
    0b00010101, // M
    0b00110111, // N
    0b00111111, // O
    0b01110011, // P
    0b01100111, // Q
    0b01010000, // R
    0b01101101, // S
    0b01111000, // T
    0b00111110, // U
    0b00101110, // V
    0b00101010, // W
    0b01110110, // X
    0b01101110, // Y
    0b01001011, // Z
    0b00000000, // [
    0b00000000, //
    0b00000000, // ]
    0b00000000, // ^
    0b01000000, // _
    0b00000000, // `
    0b01110111, // a
    0b01111100, // b
    0b00111001, // c
    0b01011110, // d
    0b01111001, // e
    0b01110001, // f
    0b00111101, // g
    0b01110110, // h
    0b00110000, // i
    0b00111100, // j
    0b01011011, // k
    0b00111000, // l
    0b00010101, // m
    0b00110111, // n
    0b00111111, // o
    0b01110011, // p
    0b01100111, // q
    0b01010000, // r
    0b01101101, // s
    0b01111000, // t
    0b00111110, // u
    0b00101110, // v
    0b00101010, // w
    0b01110110, // x
    0b01101110, // y
    0b01001011, // z
    0b00000000, // {
    0b00000000, // |
    0b00000000, // }
    0b00000000, // ~
};

static const uint8_t font_lookup(char c) {
    return pgm_read_byte(&SG_SevenSegment_font[static_cast<uint8_t>(c)]);
}

SG::SevenSegment::SevenSegment(rl_pin_t data, rl_pin_t shiftClock, rl_pin_t storageClock)
: _shift(rl_ic74hc595_create(data, shiftClock, storageClock, LSBFIRST)),
    _chars{0},
    _points{0},
    _n(0),
    _plex{ (uint8_t)~0x02, (uint8_t)~0x04, (uint8_t)~0x08, (uint8_t)~0x01 }
{}

void SG::SevenSegment::init() {
    rl_ic74hc595_setup_pins(&_shift);
    rl_timer_do_each_micros(5000, [](void* self) { ((SevenSegment*)self)->refresh(); }, this);
}

void SG::SevenSegment::setChar(uint8_t index, char character) {
    if (index < 4) {
        _chars[index] = font_lookup(character);
    }
}

void SG::SevenSegment::setDot(uint8_t index, uint8_t enabled) {
    if (index < 4) {
        if (enabled)
            _points |= (1 << index);
        else
            _points &= ~(1 << index);
    }
}

void SG::SevenSegment::refresh() {
    uint8_t charBits = _chars[_n];
    uint8_t plexBits = _plex[_n];

    if ((_points >> _n) & 1)
        charBits |= 0b10000000;

    rl_ic74hc595_begin_transmission(&_shift);
    rl_ic74hc595_shift_out(&_shift, charBits);
    rl_ic74hc595_shift_out(&_shift, plexBits);
    rl_ic74hc595_end_transmission(&_shift);

    _n = (_n + 1) % 4;
}
