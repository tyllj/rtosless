// rtosless_gpio.h
#ifndef RTOSLESS_GPIO_H
#define RTOSLESS_GPIO_H

#include <stdint.h>

#if defined(__AVR__)
#include <avr/io.h>
#elif defined(STM32F3)
#include "stm32f3xx.h"
#elif defined(ESP32C3)
#include "driver/gpio.h"
#elif defined(RA4M1)
#include "r_gpio_rx_if.h"
#endif

#ifndef HIGH
#define HIGH 1
#endif

#ifndef LOW
#define LOW 0
#endif

namespace rl {

    // 🧭 Port names for all supported platforms
    enum class port_t : uint8_t {
        A = 0, B, C, D, E, F, G, H, J, K, L
    };

    // 🎯 Pin abstraction: encodes port and pin in one byte
    struct pin_t {
        uint8_t encoded;

        constexpr pin_t(port_t port, uint8_t pin) : encoded((static_cast<uint8_t>(port) << 4) | (pin & 0x0F)) {}

        constexpr port_t port() const { return static_cast<port_t>(encoded >> 4); }
        constexpr uint8_t pin() const { return encoded & 0x0F; }
    };

    // 🧰 Pin mode options
    enum class gpio_mode : uint8_t {
        input = 0,
        input_pullup,
        input_pulldown,
        output
    };

    #if defined(__AVR__)

    inline volatile uint8_t* port_ddr(port_t port) {
        switch (port) {
            case port_t::A: return &DDRA;
            case port_t::B: return &DDRB;
            case port_t::C: return &DDRC;
            case port_t::D: return &DDRD;
            case port_t::E: return &DDRE;
            case port_t::F: return &DDRF;
            case port_t::G: return &DDRG;
            case port_t::H: return &DDRH;
            case port_t::J: return &DDRJ;
            case port_t::K: return &DDRK;
            case port_t::L: return &DDRL;
            default: return nullptr;
        }
        return nullptr;
    }

    inline volatile uint8_t* port_out(port_t port) {
        switch (port) {
            case port_t::A: return &PORTA;
            case port_t::B: return &PORTB;
            case port_t::C: return &PORTC;
            case port_t::D: return &PORTD;
            case port_t::E: return &PORTE;
            case port_t::F: return &PORTF;
            case port_t::G: return &PORTG;
            case port_t::H: return &PORTH;
            case port_t::J: return &PORTJ;
            case port_t::K: return &PORTK;
            case port_t::L: return &PORTL;
            default: return nullptr;
        }
        return nullptr;
    }

    inline volatile uint8_t* port_in(port_t port) {
        switch (port) {
            case port_t::A: return &PINA;
            case port_t::B: return &PINB;
            case port_t::C: return &PINC;
            case port_t::D: return &PIND;
            case port_t::E: return &PINE;
            case port_t::F: return &PINF;
            case port_t::G: return &PING;
            case port_t::H: return &PINH;
            case port_t::J: return &PINJ;
            case port_t::K: return &PINK;
            case port_t::L: return &PINL;
            default: return nullptr;
        }
        return nullptr;
    }

    inline void gpio_pin_mode(pin_t p, gpio_mode mode) {
        volatile uint8_t* ddr = port_ddr(p.port());
        volatile uint8_t* out = port_out(p.port());

        if (mode == gpio_mode::output) {
            *ddr |= (1 << p.pin());
        } else {
            *ddr &= ~(1 << p.pin());
            if (mode == gpio_mode::input_pullup) {
                *out |= (1 << p.pin());
            } else {
                *out &= ~(1 << p.pin());
            }
        }
    }

    inline void gpio_write(pin_t p, bool high) {
        volatile uint8_t* out = port_out(p.port());
        if (high) *out |= (1 << p.pin());
        else      *out &= ~(1 << p.pin());
    }

    inline bool gpio_read(pin_t p) {
        volatile uint8_t* in = port_in(p.port());
        return (*in >> p.pin()) & 0x1;
    }

    inline void gpio_toggle(pin_t p) {
        volatile uint8_t* out = port_out(p.port());
        *out ^= (1 << p.pin());
    }

    #elif defined(STM32F3)

    constexpr GPIO_TypeDef* port_base(port_t port) {
        return reinterpret_cast<GPIO_TypeDef*>(AHB2PERIPH_BASE + 0x0400 * static_cast<uint8_t>(port));
    }

    inline void gpio_pin_mode(pin_t p, gpio_mode mode) {
        GPIO_TypeDef* gpio = port_base(p.port());
        uint32_t shift = p.pin() * 2;

        gpio->MODER &= ~(0x3 << shift);
        if (mode == gpio_mode::output) gpio->MODER |= (0x1 << shift);

        gpio->PUPDR &= ~(0x3 << shift);
        if (mode == gpio_mode::input_pullup) gpio->PUPDR |= (0x1 << shift);
        else if (mode == gpio_mode::input_pulldown) gpio->PUPDR |= (0x2 << shift);
    }

    inline void gpio_write(pin_t p, bool high) {
        GPIO_TypeDef* gpio = port_base(p.port());
        gpio->BSRR = high ? (1 << p.pin()) : (1 << (p.pin() + 16));
    }

    inline bool gpio_read(pin_t p) {
        GPIO_TypeDef* gpio = port_base(p.port());
        return (gpio->IDR >> p.pin()) & 0x1;
    }

    inline void gpio_toggle(pin_t p) {
        GPIO_TypeDef* gpio = port_base(p.port());
        gpio->ODR ^= (1 << p.pin());
    }

    #elif defined(ESP32C3)

    inline void gpio_pin_mode(pin_t p, gpio_mode mode) {
        gpio_config_t cfg = {};
        cfg.pin_bit_mask = 1ULL << p.encoded;
        cfg.mode = (mode == gpio_mode::output) ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT;
        cfg.pull_up_en = (mode == gpio_mode::input_pullup) ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE;
        cfg.pull_down_en = (mode == gpio_mode::input_pulldown) ? GPIO_PULLDOWN_ENABLE : GPIO_PULLDOWN_DISABLE;
        gpio_config(&cfg);
    }

    inline void gpio_write(pin_t p, bool high) {
        gpio_set_level(static_cast<gpio_num_t>(p.encoded), high ? 1 : 0);
    }

    inline bool gpio_read(pin_t p) {
        return gpio_get_level(static_cast<gpio_num_t>(p.encoded)) != 0;
    }

    inline void gpio_toggle(pin_t p) {
        gpio_write(p, !gpio_read(p));
    }

    #elif defined(RA4M1)

    inline void gpio_pin_mode(pin_t p, gpio_mode mode) {
        gpio_cfg_t cfg = {
            .pin = p.encoded,
            .direction = (mode == gpio_mode::output) ? GPIO_DIRECTION_OUTPUT : GPIO_DIRECTION_INPUT,
            .output_logic = GPIO_OUTPUT_LOW,
            .port = static_cast<uint8_t>(p.port()),
            .pull = (mode == gpio_mode::input_pullup) ? GPIO_PULL_UP :
            (mode == gpio_mode::input_pulldown) ? GPIO_PULL_DOWN : GPIO_NO_PULL
        };
        R_GPIO_PinCfg(&cfg);
    }

    inline void gpio_write(pin_t p, bool high) {
        R_GPIO_PinWrite(p.encoded, high ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW);
    }

    inline bool gpio_read(pin_t p) {
        gpio_level_t level;
        R_GPIO_PinRead(p.encoded, &level);
        return level == GPIO_LEVEL_HIGH;
    }

    inline void gpio_toggle(pin_t p) {
        gpio_write(p, !gpio_read(p));
    }

    #else
    #error "Unsupported platform for rtosless_gpio.h"
    #endif

} // namespace rl

#endif // RTOSLESS_GPIO_H
