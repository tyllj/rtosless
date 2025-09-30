// rtosless_gpio.h
#ifndef RTOSLESS_GPIO_H
#define RTOSLESS_GPIO_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

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

#ifndef INPUT
#define INPUT 0x0
#endif

#ifndef OUTPUT
#define OUTPUT 0x1
#endif

#ifndef INPUT_PULLUP
#define INPUT_PULLUP 0x2
#endif

#ifndef INPUT_PULLDOWN
#define INPUT_PULLDOWN 0x3
#endif

/* Port names for all supported platforms */
typedef enum {
    PORT_A = 0, PORT_B, PORT_C, PORT_D, PORT_E, 
    PORT_F, PORT_G, PORT_H, PORT_J, PORT_K, PORT_L
} rl_port_t;

/* Pin abstraction: encodes port and pin in one byte */
typedef uint8_t rl_pin_t;

/* Helper functions for pin manipulation */
static inline rl_pin_t rl_pin_make(rl_port_t port, uint8_t pin) {
    return ((uint8_t)port << 4) | (pin & 0x0F);
}

static inline rl_port_t rl_pin_get_port(rl_pin_t p) {
    return (rl_port_t)(p >> 4);
}

static inline uint8_t rl_pin_get_pin(rl_pin_t p) {
    return p & 0x0F;
}

/* Pin mode options - Arduino library compatible */
typedef uint8_t rl_gpio_mode_t;

#ifdef __cplusplus
extern "C" {
#endif

    #if defined(__AVR__)

static inline volatile uint8_t* rl_port_ddr(rl_port_t port) {
        switch (port) {
            case PORT_A: return &DDRA;
            case PORT_B: return &DDRB;
            case PORT_C: return &DDRC;
            case PORT_D: return &DDRD;
            case PORT_E: return &DDRE;
            case PORT_F: return &DDRF;
            case PORT_G: return &DDRG;
            case PORT_H: return &DDRH;
            case PORT_J: return &DDRJ;
            case PORT_K: return &DDRK;
            case PORT_L: return &DDRL;
            default: return NULL;
        }
        return NULL;
    }

    static inline volatile uint8_t* rl_port_out(rl_port_t port) {
        switch (port) {
            case PORT_A: return &PORTA;
            case PORT_B: return &PORTB;
            case PORT_C: return &PORTC;
            case PORT_D: return &PORTD;
            case PORT_E: return &PORTE;
            case PORT_F: return &PORTF;
            case PORT_G: return &PORTG;
            case PORT_H: return &PORTH;
            case PORT_J: return &PORTJ;
            case PORT_K: return &PORTK;
            case PORT_L: return &PORTL;
            default: return NULL;
        }
        return NULL;
    }

    static inline volatile uint8_t* rl_port_in(rl_port_t port) {
        switch (port) {
            case PORT_A: return &PINA;
            case PORT_B: return &PINB;
            case PORT_C: return &PINC;
            case PORT_D: return &PIND;
            case PORT_E: return &PINE;
            case PORT_F: return &PINF;
            case PORT_G: return &PING;
            case PORT_H: return &PINH;
            case PORT_J: return &PINJ;
            case PORT_K: return &PINK;
            case PORT_L: return &PINL;
            default: return NULL;
        }
        return NULL;
    }

    static inline void rl_gpio_pin_mode(rl_pin_t p, rl_gpio_mode_t mode) {
        volatile uint8_t* ddr = rl_port_ddr(rl_pin_get_port(p));
        volatile uint8_t* out = rl_port_out(rl_pin_get_port(p));

        if (mode == OUTPUT) {
            *ddr |= (1 << rl_pin_get_pin(p));
        } else {
            *ddr &= ~(1 << rl_pin_get_pin(p));
            if (mode == INPUT_PULLUP) {
                *out |= (1 << rl_pin_get_pin(p));
            } else {
                *out &= ~(1 << rl_pin_get_pin(p));
            }
        }
    }

    static inline void rl_gpio_write(rl_pin_t p, bool high) {
        volatile uint8_t* out = rl_port_out(rl_pin_get_port(p));
        if (high) *out |= (1 << rl_pin_get_pin(p));
        else      *out &= ~(1 << rl_pin_get_pin(p));
    }

    static inline bool rl_gpio_read(rl_pin_t p) {
        volatile uint8_t* in = rl_port_in(rl_pin_get_port(p));
        return (*in >> rl_pin_get_pin(p)) & 0x1;
    }

    static inline void rl_gpio_toggle(rl_pin_t p) {
        volatile uint8_t* out = rl_port_out(rl_pin_get_port(p));
        *out ^= (1 << rl_pin_get_pin(p));
    }

    #elif defined(STM32F3)

    static inline GPIO_TypeDef* rl_port_base(rl_port_t port) {
        return (GPIO_TypeDef*)(AHB2PERIPH_BASE + 0x0400 * (uint8_t)port);
    }

    static inline void rl_gpio_pin_mode(rl_pin_t p, rl_gpio_mode_t mode) {
        GPIO_TypeDef* gpio = rl_port_base(rl_pin_get_port(p));
        uint32_t shift = rl_pin_get_pin(p) * 2;

        gpio->MODER &= ~(0x3 << shift);
        if (mode == OUTPUT) gpio->MODER |= (0x1 << shift);

        gpio->PUPDR &= ~(0x3 << shift);
        if (mode == INPUT_PULLUP) gpio->PUPDR |= (0x1 << shift);
        else if (mode == INPUT_PULLDOWN) gpio->PUPDR |= (0x2 << shift);
    }

    static inline void rl_gpio_write(rl_pin_t p, bool high) {
        GPIO_TypeDef* gpio = rl_port_base(rl_pin_get_port(p));
        gpio->BSRR = high ? (1 << rl_pin_get_pin(p)) : (1 << (rl_pin_get_pin(p) + 16));
    }

    static inline bool rl_gpio_read(rl_pin_t p) {
        GPIO_TypeDef* gpio = rl_port_base(rl_pin_get_port(p));
        return (gpio->IDR >> rl_pin_get_pin(p)) & 0x1;
    }

    static inline void rl_gpio_toggle(rl_pin_t p) {
        GPIO_TypeDef* gpio = rl_port_base(rl_pin_get_port(p));
        gpio->ODR ^= (1 << rl_pin_get_pin(p));
    }

    #elif defined(ESP32C3)

    static inline void rl_gpio_pin_mode(rl_pin_t p, rl_gpio_mode_t mode) {
        gpio_config_t cfg = {0};
        cfg.pin_bit_mask = 1ULL << p.encoded;
        cfg.mode = (mode == OUTPUT) ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT;
        cfg.pull_up_en = (mode == INPUT_PULLUP) ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE;
        cfg.pull_down_en = (mode == INPUT_PULLDOWN) ? GPIO_PULLDOWN_ENABLE : GPIO_PULLDOWN_DISABLE;
        gpio_config(&cfg);
    }

    static inline void rl_gpio_write(rl_pin_t p, bool high) {
        gpio_set_level((gpio_num_t)p.encoded, high ? 1 : 0);
    }

    static inline bool rl_gpio_read(rl_pin_t p) {
        return gpio_get_level((gpio_num_t)p.encoded) != 0;
    }

    static inline void rl_gpio_toggle(rl_pin_t p) {
        rl_gpio_write(p, !rl_gpio_read(p));
    }

    #elif defined(RA4M1)

    static inline void rl_gpio_pin_mode(rl_pin_t p, rl_gpio_mode_t mode) {
        gpio_cfg_t cfg = {
            .pin = p.encoded,
            .direction = (mode == OUTPUT) ? GPIO_DIRECTION_OUTPUT : GPIO_DIRECTION_INPUT,
            .output_logic = GPIO_OUTPUT_LOW,
            .port = (uint8_t)rl_pin_get_port(p),
            .pull = (mode == INPUT_PULLUP) ? GPIO_PULL_UP :
                   (mode == INPUT_PULLDOWN) ? GPIO_PULL_DOWN : GPIO_NO_PULL
        };
        R_GPIO_PinCfg(&cfg);
    }

    static inline void rl_gpio_write(rl_pin_t p, bool high) {
        R_GPIO_PinWrite(p.encoded, high ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW);
    }

    static inline bool rl_gpio_read(rl_pin_t p) {
        gpio_level_t level;
        R_GPIO_PinRead(p.encoded, &level);
        return level == GPIO_LEVEL_HIGH;
    }

    static inline void rl_gpio_toggle(rl_pin_t p) {
        rl_gpio_write(p, !rl_gpio_read(p));
    }

    #else
    #error "Unsupported platform for rtosless_gpio.h"
    #endif

#ifdef __cplusplus
}
#endif

#endif // RTOSLESS_GPIO_H
