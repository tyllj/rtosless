#ifndef RTOSLESS_PINS_H
#define RTOSLESS_PINS_H

#include "rtosless_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

    // Port A
    #define RL_PIN_PA0  ((rl_pin_t)((PORT_A << 4) | 0))
    #define RL_PIN_PA1  ((rl_pin_t)((PORT_A << 4) | 1))
    #define RL_PIN_PA2  ((rl_pin_t)((PORT_A << 4) | 2))
    #define RL_PIN_PA3  ((rl_pin_t)((PORT_A << 4) | 3))
    #define RL_PIN_PA4  ((rl_pin_t)((PORT_A << 4) | 4))
    #define RL_PIN_PA5  ((rl_pin_t)((PORT_A << 4) | 5))
    #define RL_PIN_PA6  ((rl_pin_t)((PORT_A << 4) | 6))
    #define RL_PIN_PA7  ((rl_pin_t)((PORT_A << 4) | 7))
    #define RL_PIN_PA8  ((rl_pin_t)((PORT_A << 4) | 8))
    #define RL_PIN_PA9  ((rl_pin_t)((PORT_A << 4) | 9))
    #define RL_PIN_PA10 ((rl_pin_t)((PORT_A << 4) | 10))
    #define RL_PIN_PA11 ((rl_pin_t)((PORT_A << 4) | 11))
    #define RL_PIN_PA12 ((rl_pin_t)((PORT_A << 4) | 12))
    #define RL_PIN_PA13 ((rl_pin_t)((PORT_A << 4) | 13))
    #define RL_PIN_PA14 ((rl_pin_t)((PORT_A << 4) | 14))
    #define RL_PIN_PA15 ((rl_pin_t)((PORT_A << 4) | 15))

    // Port B
    #define RL_PIN_PB0  ((rl_pin_t)((PORT_B << 4) | 0))
    #define RL_PIN_PB1  ((rl_pin_t)((PORT_B << 4) | 1))
    #define RL_PIN_PB2  ((rl_pin_t)((PORT_B << 4) | 2))
    #define RL_PIN_PB3  ((rl_pin_t)((PORT_B << 4) | 3))
    #define RL_PIN_PB4  ((rl_pin_t)((PORT_B << 4) | 4))
    #define RL_PIN_PB5  ((rl_pin_t)((PORT_B << 4) | 5))
    #define RL_PIN_PB6  ((rl_pin_t)((PORT_B << 4) | 6))
    #define RL_PIN_PB7  ((rl_pin_t)((PORT_B << 4) | 7))
    #define RL_PIN_PB8  ((rl_pin_t)((PORT_B << 4) | 8))
    #define RL_PIN_PB9  ((rl_pin_t)((PORT_B << 4) | 9))
    #define RL_PIN_PB10 ((rl_pin_t)((PORT_B << 4) | 10))
    #define RL_PIN_PB11 ((rl_pin_t)((PORT_B << 4) | 11))
    #define RL_PIN_PB12 ((rl_pin_t)((PORT_B << 4) | 12))
    #define RL_PIN_PB13 ((rl_pin_t)((PORT_B << 4) | 13))
    #define RL_PIN_PB14 ((rl_pin_t)((PORT_B << 4) | 14))
    #define RL_PIN_PB15 ((rl_pin_t)((PORT_B << 4) | 15))

    // Port C
    #define RL_PIN_PC0  ((rl_pin_t)((PORT_C << 4) | 0))
    #define RL_PIN_PC1  ((rl_pin_t)((PORT_C << 4) | 1))
    #define RL_PIN_PC2  ((rl_pin_t)((PORT_C << 4) | 2))
    #define RL_PIN_PC3  ((rl_pin_t)((PORT_C << 4) | 3))
    #define RL_PIN_PC4  ((rl_pin_t)((PORT_C << 4) | 4))
    #define RL_PIN_PC5  ((rl_pin_t)((PORT_C << 4) | 5))
    #define RL_PIN_PC6  ((rl_pin_t)((PORT_C << 4) | 6))
    #define RL_PIN_PC7  ((rl_pin_t)((PORT_C << 4) | 7))
    #define RL_PIN_PC8  ((rl_pin_t)((PORT_C << 4) | 8))
    #define RL_PIN_PC9  ((rl_pin_t)((PORT_C << 4) | 9))
    #define RL_PIN_PC10 ((rl_pin_t)((PORT_C << 4) | 10))
    #define RL_PIN_PC11 ((rl_pin_t)((PORT_C << 4) | 11))
    #define RL_PIN_PC12 ((rl_pin_t)((PORT_C << 4) | 12))
    #define RL_PIN_PC13 ((rl_pin_t)((PORT_C << 4) | 13))
    #define RL_PIN_PC14 ((rl_pin_t)((PORT_C << 4) | 14))
    #define RL_PIN_PC15 ((rl_pin_t)((PORT_C << 4) | 15))

    // Port D
    #define RL_PIN_PD0  ((rl_pin_t)((PORT_D << 4) | 0))
    #define RL_PIN_PD1  ((rl_pin_t)((PORT_D << 4) | 1))
    #define RL_PIN_PD2  ((rl_pin_t)((PORT_D << 4) | 2))
    #define RL_PIN_PD3  ((rl_pin_t)((PORT_D << 4) | 3))
    #define RL_PIN_PD4  ((rl_pin_t)((PORT_D << 4) | 4))
    #define RL_PIN_PD5  ((rl_pin_t)((PORT_D << 4) | 5))
    #define RL_PIN_PD6  ((rl_pin_t)((PORT_D << 4) | 6))
    #define RL_PIN_PD7  ((rl_pin_t)((PORT_D << 4) | 7))
    #define RL_PIN_PD8  ((rl_pin_t)((PORT_D << 4) | 8))
    #define RL_PIN_PD9  ((rl_pin_t)((PORT_D << 4) | 9))
    #define RL_PIN_PD10 ((rl_pin_t)((PORT_D << 4) | 10))
    #define RL_PIN_PD11 ((rl_pin_t)((PORT_D << 4) | 11))
    #define RL_PIN_PD12 ((rl_pin_t)((PORT_D << 4) | 12))
    #define RL_PIN_PD13 ((rl_pin_t)((PORT_D << 4) | 13))
    #define RL_PIN_PD14 ((rl_pin_t)((PORT_D << 4) | 14))
    #define RL_PIN_PD15 ((rl_pin_t)((PORT_D << 4) | 15))

    // Port E
    #define RL_PIN_PE0  ((rl_pin_t)((PORT_E << 4) | 0))
    #define RL_PIN_PE1  ((rl_pin_t)((PORT_E << 4) | 1))
    #define RL_PIN_PE2  ((rl_pin_t)((PORT_E << 4) | 2))
    #define RL_PIN_PE3  ((rl_pin_t)((PORT_E << 4) | 3))
    #define RL_PIN_PE4  ((rl_pin_t)((PORT_E << 4) | 4))
    #define RL_PIN_PE5  ((rl_pin_t)((PORT_E << 4) | 5))
    #define RL_PIN_PE6  ((rl_pin_t)((PORT_E << 4) | 6))
    #define RL_PIN_PE7  ((rl_pin_t)((PORT_E << 4) | 7))
    #define RL_PIN_PE8  ((rl_pin_t)((PORT_E << 4) | 8))
    #define RL_PIN_PE9  ((rl_pin_t)((PORT_E << 4) | 9))
    #define RL_PIN_PE10 ((rl_pin_t)((PORT_E << 4) | 10))
    #define RL_PIN_PE11 ((rl_pin_t)((PORT_E << 4) | 11))
    #define RL_PIN_PE12 ((rl_pin_t)((PORT_E << 4) | 12))
    #define RL_PIN_PE13 ((rl_pin_t)((PORT_E << 4) | 13))
    #define RL_PIN_PE14 ((rl_pin_t)((PORT_E << 4) | 14))
    #define RL_PIN_PE15 ((rl_pin_t)((PORT_E << 4) | 15))

    // Port F
    #define RL_PIN_PF0  ((rl_pin_t)((PORT_F << 4) | 0))
    #define RL_PIN_PF1  ((rl_pin_t)((PORT_F << 4) | 1))
    #define RL_PIN_PF2  ((rl_pin_t)((PORT_F << 4) | 2))
    #define RL_PIN_PF3  ((rl_pin_t)((PORT_F << 4) | 3))
    #define RL_PIN_PF4  ((rl_pin_t)((PORT_F << 4) | 4))
    #define RL_PIN_PF5  ((rl_pin_t)((PORT_F << 4) | 5))
    #define RL_PIN_PF6  ((rl_pin_t)((PORT_F << 4) | 6))
    #define RL_PIN_PF7  ((rl_pin_t)((PORT_F << 4) | 7))
    #define RL_PIN_PF8  ((rl_pin_t)((PORT_F << 4) | 8))
    #define RL_PIN_PF9  ((rl_pin_t)((PORT_F << 4) | 9))
    #define RL_PIN_PF10 ((rl_pin_t)((PORT_F << 4) | 10))
    #define RL_PIN_PF11 ((rl_pin_t)((PORT_F << 4) | 11))
    #define RL_PIN_PF12 ((rl_pin_t)((PORT_F << 4) | 12))
    #define RL_PIN_PF13 ((rl_pin_t)((PORT_F << 4) | 13))
    #define RL_PIN_PF14 ((rl_pin_t)((PORT_F << 4) | 14))
    #define RL_PIN_PF15 ((rl_pin_t)((PORT_F << 4) | 15))

    // Port G
    #define RL_PIN_PG0  ((rl_pin_t)((PORT_G << 4) | 0))
    #define RL_PIN_PG1  ((rl_pin_t)((PORT_G << 4) | 1))
    #define RL_PIN_PG2  ((rl_pin_t)((PORT_G << 4) | 2))
    #define RL_PIN_PG3  ((rl_pin_t)((PORT_G << 4) | 3))
    #define RL_PIN_PG4  ((rl_pin_t)((PORT_G << 4) | 4))
    #define RL_PIN_PG5  ((rl_pin_t)((PORT_G << 4) | 5))
    #define RL_PIN_PG6  ((rl_pin_t)((PORT_G << 4) | 6))
    #define RL_PIN_PG7  ((rl_pin_t)((PORT_G << 4) | 7))
    #define RL_PIN_PG8  ((rl_pin_t)((PORT_G << 4) | 8))
    #define RL_PIN_PG9  ((rl_pin_t)((PORT_G << 4) | 9))
    #define RL_PIN_PG10 ((rl_pin_t)((PORT_G << 4) | 10))
    #define RL_PIN_PG11 ((rl_pin_t)((PORT_G << 4) | 11))
    #define RL_PIN_PG12 ((rl_pin_t)((PORT_G << 4) | 12))
    #define RL_PIN_PG13 ((rl_pin_t)((PORT_G << 4) | 13))
    #define RL_PIN_PG14 ((rl_pin_t)((PORT_G << 4) | 14))
    #define RL_PIN_PG15 ((rl_pin_t)((PORT_G << 4) | 15))

    // Port H
    #define RL_PIN_PH0  ((rl_pin_t)((PORT_H << 4) | 0))
    #define RL_PIN_PH1  ((rl_pin_t)((PORT_H << 4) | 1))
    #define RL_PIN_PH2  ((rl_pin_t)((PORT_H << 4) | 2))
    #define RL_PIN_PH3  ((rl_pin_t)((PORT_H << 4) | 3))
    #define RL_PIN_PH4  ((rl_pin_t)((PORT_H << 4) | 4))
    #define RL_PIN_PH5  ((rl_pin_t)((PORT_H << 4) | 5))
    #define RL_PIN_PH6  ((rl_pin_t)((PORT_H << 4) | 6))
    #define RL_PIN_PH7  ((rl_pin_t)((PORT_H << 4) | 7))
    #define RL_PIN_PH8  ((rl_pin_t)((PORT_H << 4) | 8))
    #define RL_PIN_PH9  ((rl_pin_t)((PORT_H << 4) | 9))
    #define RL_PIN_PH10 ((rl_pin_t)((PORT_H << 4) | 10))
    #define RL_PIN_PH11 ((rl_pin_t)((PORT_H << 4) | 11))
    #define RL_PIN_PH12 ((rl_pin_t)((PORT_H << 4) | 12))
    #define RL_PIN_PH13 ((rl_pin_t)((PORT_H << 4) | 13))
    #define RL_PIN_PH14 ((rl_pin_t)((PORT_H << 4) | 14))
    #define RL_PIN_PH15 ((rl_pin_t)((PORT_H << 4) | 15))

    // Port J
    #define RL_PIN_PJ0  ((rl_pin_t)((PORT_J << 4) | 0))
    #define RL_PIN_PJ1  ((rl_pin_t)((PORT_J << 4) | 1))
    #define RL_PIN_PJ2  ((rl_pin_t)((PORT_J << 4) | 2))
    #define RL_PIN_PJ3  ((rl_pin_t)((PORT_J << 4) | 3))
    #define RL_PIN_PJ4  ((rl_pin_t)((PORT_J << 4) | 4))
    #define RL_PIN_PJ5  ((rl_pin_t)((PORT_J << 4) | 5))
    #define RL_PIN_PJ6  ((rl_pin_t)((PORT_J << 4) | 6))
    #define RL_PIN_PJ7  ((rl_pin_t)((PORT_J << 4) | 7))
    #define RL_PIN_PJ8  ((rl_pin_t)((PORT_J << 4) | 8))
    #define RL_PIN_PJ9  ((rl_pin_t)((PORT_J << 4) | 9))
    #define RL_PIN_PJ10 ((rl_pin_t)((PORT_J << 4) | 10))
    #define RL_PIN_PJ11 ((rl_pin_t)((PORT_J << 4) | 11))
    #define RL_PIN_PJ12 ((rl_pin_t)((PORT_J << 4) | 12))
    #define RL_PIN_PJ13 ((rl_pin_t)((PORT_J << 4) | 13))
    #define RL_PIN_PJ14 ((rl_pin_t)((PORT_J << 4) | 14))
    #define RL_PIN_PJ15 ((rl_pin_t)((PORT_J << 4) | 15))

    // Port K
    #define RL_PIN_PK0  ((rl_pin_t)((PORT_K << 4) | 0))
    #define RL_PIN_PK1  ((rl_pin_t)((PORT_K << 4) | 1))
    #define RL_PIN_PK2  ((rl_pin_t)((PORT_K << 4) | 2))
    #define RL_PIN_PK3  ((rl_pin_t)((PORT_K << 4) | 3))
    #define RL_PIN_PK4  ((rl_pin_t)((PORT_K << 4) | 4))
    #define RL_PIN_PK5  ((rl_pin_t)((PORT_K << 4) | 5))
    #define RL_PIN_PK6  ((rl_pin_t)((PORT_K << 4) | 6))
    #define RL_PIN_PK7  ((rl_pin_t)((PORT_K << 4) | 7))
    #define RL_PIN_PK8  ((rl_pin_t)((PORT_K << 4) | 8))
    #define RL_PIN_PK9  ((rl_pin_t)((PORT_K << 4) | 9))
    #define RL_PIN_PK10 ((rl_pin_t)((PORT_K << 4) | 10))
    #define RL_PIN_PK11 ((rl_pin_t)((PORT_K << 4) | 11))
    #define RL_PIN_PK12 ((rl_pin_t)((PORT_K << 4) | 12))
    #define RL_PIN_PK13 ((rl_pin_t)((PORT_K << 4) | 13))
    #define RL_PIN_PK14 ((rl_pin_t)((PORT_K << 4) | 14))
    #define RL_PIN_PK15 ((rl_pin_t)((PORT_K << 4) | 15))

    // Port L
    #define RL_PIN_PL0  ((rl_pin_t)((PORT_L << 4) | 0))
    #define RL_PIN_PL1  ((rl_pin_t)((PORT_L << 4) | 1))
    #define RL_PIN_PL2  ((rl_pin_t)((PORT_L << 4) | 2))
    #define RL_PIN_PL3  ((rl_pin_t)((PORT_L << 4) | 3))
    #define RL_PIN_PL4  ((rl_pin_t)((PORT_L << 4) | 4))
    #define RL_PIN_PL5  ((rl_pin_t)((PORT_L << 4) | 5))
    #define RL_PIN_PL6  ((rl_pin_t)((PORT_L << 4) | 6))
    #define RL_PIN_PL7  ((rl_pin_t)((PORT_L << 4) | 7))
    #define RL_PIN_PL8  ((rl_pin_t)((PORT_L << 4) | 8))
    #define RL_PIN_PL9  ((rl_pin_t)((PORT_L << 4) | 9))
    #define RL_PIN_PL10 ((rl_pin_t)((PORT_L << 4) | 10))
    #define RL_PIN_PL11 ((rl_pin_t)((PORT_L << 4) | 11))
    #define RL_PIN_PL12 ((rl_pin_t)((PORT_L << 4) | 12))
    #define RL_PIN_PL13 ((rl_pin_t)((PORT_L << 4) | 13))
    #define RL_PIN_PL14 ((rl_pin_t)((PORT_L << 4) | 14))
    #define RL_PIN_PL15 ((rl_pin_t)((PORT_L << 4) | 15))

    #if defined(__AVR_ATmega328P__)  // Arduino Uno
    // Arduino digital pin mapping
    #define RL_D0  ((rl_pin_t)((PORT_D << 4) | 0))
    #define RL_D1  ((rl_pin_t)((PORT_D << 4) | 1))
    #define RL_D2  ((rl_pin_t)((PORT_D << 4) | 2))
    #define RL_D3  ((rl_pin_t)((PORT_D << 4) | 3))
    #define RL_D4  ((rl_pin_t)((PORT_D << 4) | 4))
    #define RL_D5  ((rl_pin_t)((PORT_D << 4) | 5))
    #define RL_D6  ((rl_pin_t)((PORT_D << 4) | 6))
    #define RL_D7  ((rl_pin_t)((PORT_D << 4) | 7))
    #define RL_D8  ((rl_pin_t)((PORT_B << 4) | 0))
    #define RL_D9  ((rl_pin_t)((PORT_B << 4) | 1))
    #define RL_D10 ((rl_pin_t)((PORT_B << 4) | 2))
    #define RL_D11 ((rl_pin_t)((PORT_B << 4) | 3))
    #define RL_D12 ((rl_pin_t)((PORT_B << 4) | 4))
    #define RL_D13 ((rl_pin_t)((PORT_B << 4) | 5))

    #define RL_A0 ((rl_pin_t)((PORT_C << 4) | 0))
    #define RL_A1 ((rl_pin_t)((PORT_C << 4) | 1))
    #define RL_A2 ((rl_pin_t)((PORT_C << 4) | 2))
    #define RL_A3 ((rl_pin_t)((PORT_C << 4) | 3))
    #define RL_A4 ((rl_pin_t)((PORT_C << 4) | 4))
    #define RL_A5 ((rl_pin_t)((PORT_C << 4) | 5))

#elif defined(__AVR_ATmega2560__)  // Arduino Mega
    // Arduino digital pin mapping
    #define RL_D0  ((rl_pin_t)((PORT_E << 4) | 0))
    #define RL_D1  ((rl_pin_t)((PORT_E << 4) | 1))
    #define RL_D2  ((rl_pin_t)((PORT_E << 4) | 4))
    #define RL_D3  ((rl_pin_t)((PORT_E << 4) | 5))
    #define RL_D4  ((rl_pin_t)((PORT_G << 4) | 5))
    #define RL_D5  ((rl_pin_t)((PORT_E << 4) | 3))
    #define RL_D6  ((rl_pin_t)((PORT_H << 4) | 3))
    #define RL_D7  ((rl_pin_t)((PORT_H << 4) | 4))
    #define RL_D8  ((rl_pin_t)((PORT_H << 4) | 5))
    #define RL_D9  ((rl_pin_t)((PORT_H << 4) | 6))
    #define RL_D10 ((rl_pin_t)((PORT_B << 4) | 4))
    #define RL_D11 ((rl_pin_t)((PORT_B << 4) | 5))
    #define RL_D12 ((rl_pin_t)((PORT_B << 4) | 6))
    #define RL_D13 ((rl_pin_t)((PORT_B << 4) | 7))
    #define RL_D14 ((rl_pin_t)((PORT_J << 4) | 1))
    #define RL_D15 ((rl_pin_t)((PORT_J << 4) | 0))
    #define RL_D16 ((rl_pin_t)((PORT_H << 4) | 1))
    #define RL_D17 ((rl_pin_t)((PORT_H << 4) | 0))
    #define RL_D18 ((rl_pin_t)((PORT_D << 4) | 3))
    #define RL_D19 ((rl_pin_t)((PORT_D << 4) | 2))
    #define RL_D20 ((rl_pin_t)((PORT_D << 4) | 1))
    #define RL_D21 ((rl_pin_t)((PORT_D << 4) | 0))
    #define RL_D22 ((rl_pin_t)((PORT_A << 4) | 0))
    #define RL_D23 ((rl_pin_t)((PORT_A << 4) | 1))
    #define RL_D24 ((rl_pin_t)((PORT_A << 4) | 2))
    #define RL_D25 ((rl_pin_t)((PORT_A << 4) | 3))
    #define RL_D26 ((rl_pin_t)((PORT_A << 4) | 4))
    #define RL_D27 ((rl_pin_t)((PORT_A << 4) | 5))
    #define RL_D28 ((rl_pin_t)((PORT_A << 4) | 6))
    #define RL_D29 ((rl_pin_t)((PORT_A << 4) | 7))
    #define RL_D30 ((rl_pin_t)((PORT_C << 4) | 7))
    #define RL_D31 ((rl_pin_t)((PORT_C << 4) | 6))
    #define RL_D32 ((rl_pin_t)((PORT_C << 4) | 5))
    #define RL_D33 ((rl_pin_t)((PORT_C << 4) | 4))
    #define RL_D34 ((rl_pin_t)((PORT_C << 4) | 3))
    #define RL_D35 ((rl_pin_t)((PORT_C << 4) | 2))
    #define RL_D36 ((rl_pin_t)((PORT_C << 4) | 1))
    #define RL_D37 ((rl_pin_t)((PORT_C << 4) | 0))
    #define RL_D38 ((rl_pin_t)((PORT_D << 4) | 7))
    #define RL_D39 ((rl_pin_t)((PORT_G << 4) | 2))
    #define RL_D40 ((rl_pin_t)((PORT_G << 4) | 1))
    #define RL_D41 ((rl_pin_t)((PORT_G << 4) | 0))
    #define RL_D42 ((rl_pin_t)((PORT_L << 4) | 7))
    #define RL_D43 ((rl_pin_t)((PORT_L << 4) | 6))
    #define RL_D44 ((rl_pin_t)((PORT_L << 4) | 5))
    #define RL_D45 ((rl_pin_t)((PORT_L << 4) | 4))
    #define RL_D46 ((rl_pin_t)((PORT_L << 4) | 3))
    #define RL_D47 ((rl_pin_t)((PORT_L << 4) | 2))
    #define RL_D48 ((rl_pin_t)((PORT_L << 4) | 1))
    #define RL_D49 ((rl_pin_t)((PORT_L << 4) | 0))
    #define RL_D50 ((rl_pin_t)((PORT_B << 4) | 3))
    #define RL_D51 ((rl_pin_t)((PORT_B << 4) | 2))
    #define RL_D52 ((rl_pin_t)((PORT_B << 4) | 1))
    #define RL_D53 ((rl_pin_t)((PORT_B << 4) | 0))

    // Analog pins
    #define RL_A0  ((rl_pin_t)((PORT_F << 4) | 0))
    #define RL_A1  ((rl_pin_t)((PORT_F << 4) | 1))
    #define RL_A2  ((rl_pin_t)((PORT_F << 4) | 2))
    #define RL_A3  ((rl_pin_t)((PORT_F << 4) | 3))
    #define RL_A4  ((rl_pin_t)((PORT_F << 4) | 4))
    #define RL_A5  ((rl_pin_t)((PORT_F << 4) | 5))
    #define RL_A6  ((rl_pin_t)((PORT_F << 4) | 6))
    #define RL_A7  ((rl_pin_t)((PORT_F << 4) | 7))
    #define RL_A8  ((rl_pin_t)((PORT_K << 4) | 0))
    #define RL_A9  ((rl_pin_t)((PORT_K << 4) | 1))
    #define RL_A10 ((rl_pin_t)((PORT_K << 4) | 2))
    #define RL_A11 ((rl_pin_t)((PORT_K << 4) | 3))
    #define RL_A12 ((rl_pin_t)((PORT_K << 4) | 4))
    #define RL_A13 ((rl_pin_t)((PORT_K << 4) | 5))
    #define RL_A14 ((rl_pin_t)((PORT_K << 4) | 6))
    #define RL_A15 ((rl_pin_t)((PORT_K << 4) | 7))

#elif defined(__AVR_ATmega32U4__)  // Arduino Micro
    #define RL_D0  ((rl_pin_t)((PORT_D << 4) | 2))
    #define RL_D1  ((rl_pin_t)((PORT_D << 4) | 3))
    #define RL_D2  ((rl_pin_t)((PORT_D << 4) | 1))
    #define RL_D3  ((rl_pin_t)((PORT_D << 4) | 0))
    #define RL_D4  ((rl_pin_t)((PORT_D << 4) | 4))
    #define RL_D5  ((rl_pin_t)((PORT_C << 4) | 6))
    #define RL_D6  ((rl_pin_t)((PORT_D << 4) | 7))
    #define RL_D7  ((rl_pin_t)((PORT_E << 4) | 6))
    #define RL_D8  ((rl_pin_t)((PORT_B << 4) | 4))
    #define RL_D9  ((rl_pin_t)((PORT_B << 4) | 5))
    #define RL_D10 ((rl_pin_t)((PORT_B << 4) | 6))
    #define RL_D11 ((rl_pin_t)((PORT_B << 4) | 7))
    #define RL_D12 ((rl_pin_t)((PORT_D << 4) | 6))
    #define RL_D13 ((rl_pin_t)((PORT_C << 4) | 7))

    #define RL_A0 ((rl_pin_t)((PORT_F << 4) | 7))
    #define RL_A1 ((rl_pin_t)((PORT_F << 4) | 6))
    #define RL_A2 ((rl_pin_t)((PORT_F << 4) | 5))
    #define RL_A3 ((rl_pin_t)((PORT_F << 4) | 4))
    #define RL_A4 ((rl_pin_t)((PORT_F << 4) | 1))
    #define RL_A5 ((rl_pin_t)((PORT_F << 4) | 0))

#elif defined(RA4M1)  // Define this macro when compiling for RA4M1-based boards
    // Digital pins - Note: RA4M1 uses different port numbering (P0, P1, P3, etc.)
    // Using custom port values for RA4M1 since it doesn't follow standard A-L naming
    #define RA4M1_PORT_P0 0x10
    #define RA4M1_PORT_P1 0x11
    #define RA4M1_PORT_P3 0x13

    #define RL_D0  ((rl_pin_t)((RA4M1_PORT_P3 << 4) | 1))   // P301
    #define RL_D1  ((rl_pin_t)((RA4M1_PORT_P3 << 4) | 2))   // P302
    #define RL_D2  ((rl_pin_t)((RA4M1_PORT_P1 << 4) | 5))   // P105
    #define RL_D3  ((rl_pin_t)((RA4M1_PORT_P1 << 4) | 4))   // P104
    #define RL_D4  ((rl_pin_t)((RA4M1_PORT_P1 << 4) | 3))   // P103 (CANTX)
    #define RL_D5  ((rl_pin_t)((RA4M1_PORT_P1 << 4) | 2))   // P102 (CANRX)
    #define RL_D6  ((rl_pin_t)((RA4M1_PORT_P1 << 4) | 6))   // P106
    #define RL_D7  ((rl_pin_t)((RA4M1_PORT_P1 << 4) | 7))   // P107
    #define RL_D8  ((rl_pin_t)((RA4M1_PORT_P3 << 4) | 4))   // P304
    #define RL_D9  ((rl_pin_t)((RA4M1_PORT_P3 << 4) | 3))   // P303
    #define RL_D10 ((rl_pin_t)((RA4M1_PORT_P1 << 4) | 12))  // P112
    #define RL_D11 ((rl_pin_t)((RA4M1_PORT_P1 << 4) | 9))   // P109
    #define RL_D12 ((rl_pin_t)((RA4M1_PORT_P1 << 4) | 10))  // P110
    #define RL_D13 ((rl_pin_t)((RA4M1_PORT_P1 << 4) | 11))  // P111

    // Analog pins
    #define RL_A0 ((rl_pin_t)((RA4M1_PORT_P0 << 4) | 14))   // P014_AN09
    #define RL_A1 ((rl_pin_t)((RA4M1_PORT_P0 << 4) | 0))    // P000_AN00
    #define RL_A2 ((rl_pin_t)((RA4M1_PORT_P0 << 4) | 1))    // P001_AN01
    #define RL_A3 ((rl_pin_t)((RA4M1_PORT_P0 << 4) | 2))    // P002_AN02
    #define RL_A4 ((rl_pin_t)((RA4M1_PORT_P1 << 4) | 1))    // P101_AN21 (SDA)
    #define RL_A5 ((rl_pin_t)((RA4M1_PORT_P1 << 4) | 0))    // P100_AN22 (SCL)

#endif

#ifdef __cplusplus
}
#endif

#endif // RTOSLESS_PINS_H
