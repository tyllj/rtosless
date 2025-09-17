#ifndef RTOSLESS_PINS_H
#define RTOSLESS_PINS_H

#include "rtosless_gpio.h"

namespace rl {

    // Port A
    constexpr pin_t PIN_PA0{port_t::A, 0};
    constexpr pin_t PIN_PA1{port_t::A, 1};
    constexpr pin_t PIN_PA2{port_t::A, 2};
    constexpr pin_t PIN_PA3{port_t::A, 3};
    constexpr pin_t PIN_PA4{port_t::A, 4};
    constexpr pin_t PIN_PA5{port_t::A, 5};
    constexpr pin_t PIN_PA6{port_t::A, 6};
    constexpr pin_t PIN_PA7{port_t::A, 7};
    constexpr pin_t PIN_PA8{port_t::A, 8};
    constexpr pin_t PIN_PA9{port_t::A, 9};
    constexpr pin_t PIN_PA10{port_t::A, 10};
    constexpr pin_t PIN_PA11{port_t::A, 11};
    constexpr pin_t PIN_PA12{port_t::A, 12};
    constexpr pin_t PIN_PA13{port_t::A, 13};
    constexpr pin_t PIN_PA14{port_t::A, 14};
    constexpr pin_t PIN_PA15{port_t::A, 15};

    // Port B
    constexpr pin_t PIN_PB0{port_t::B, 0};
    constexpr pin_t PIN_PB1{port_t::B, 1};
    constexpr pin_t PIN_PB2{port_t::B, 2};
    constexpr pin_t PIN_PB3{port_t::B, 3};
    constexpr pin_t PIN_PB4{port_t::B, 4};
    constexpr pin_t PIN_PB5{port_t::B, 5};
    constexpr pin_t PIN_PB6{port_t::B, 6};
    constexpr pin_t PIN_PB7{port_t::B, 7};
    constexpr pin_t PIN_PB8{port_t::B, 8};
    constexpr pin_t PIN_PB9{port_t::B, 9};
    constexpr pin_t PIN_PB10{port_t::B, 10};
    constexpr pin_t PIN_PB11{port_t::B, 11};
    constexpr pin_t PIN_PB12{port_t::B, 12};
    constexpr pin_t PIN_PB13{port_t::B, 13};
    constexpr pin_t PIN_PB14{port_t::B, 14};
    constexpr pin_t PIN_PB15{port_t::B, 15};

    // Port C
    constexpr pin_t PIN_PC0{port_t::C, 0};
    constexpr pin_t PIN_PC1{port_t::C, 1};
    constexpr pin_t PIN_PC2{port_t::C, 2};
    constexpr pin_t PIN_PC3{port_t::C, 3};
    constexpr pin_t PIN_PC4{port_t::C, 4};
    constexpr pin_t PIN_PC5{port_t::C, 5};
    constexpr pin_t PIN_PC6{port_t::C, 6};
    constexpr pin_t PIN_PC7{port_t::C, 7};
    constexpr pin_t PIN_PC8{port_t::C, 8};
    constexpr pin_t PIN_PC9{port_t::C, 9};
    constexpr pin_t PIN_PC10{port_t::C, 10};
    constexpr pin_t PIN_PC11{port_t::C, 11};
    constexpr pin_t PIN_PC12{port_t::C, 12};
    constexpr pin_t PIN_PC13{port_t::C, 13};
    constexpr pin_t PIN_PC14{port_t::C, 14};
    constexpr pin_t PIN_PC15{port_t::C, 15};

    // Port D
    constexpr pin_t PIN_PD0{port_t::D, 0};
    constexpr pin_t PIN_PD1{port_t::D, 1};
    constexpr pin_t PIN_PD2{port_t::D, 2};
    constexpr pin_t PIN_PD3{port_t::D, 3};
    constexpr pin_t PIN_PD4{port_t::D, 4};
    constexpr pin_t PIN_PD5{port_t::D, 5};
    constexpr pin_t PIN_PD6{port_t::D, 6};
    constexpr pin_t PIN_PD7{port_t::D, 7};
    constexpr pin_t PIN_PD8{port_t::D, 8};
    constexpr pin_t PIN_PD9{port_t::D, 9};
    constexpr pin_t PIN_PD10{port_t::D, 10};
    constexpr pin_t PIN_PD11{port_t::D, 11};
    constexpr pin_t PIN_PD12{port_t::D, 12};
    constexpr pin_t PIN_PD13{port_t::D, 13};
    constexpr pin_t PIN_PD14{port_t::D, 14};
    constexpr pin_t PIN_PD15{port_t::D, 15};

    // Port E
    constexpr pin_t PIN_PE0{port_t::E, 0};
    constexpr pin_t PIN_PE1{port_t::E, 1};
    constexpr pin_t PIN_PE2{port_t::E, 2};
    constexpr pin_t PIN_PE3{port_t::E, 3};
    constexpr pin_t PIN_PE4{port_t::E, 4};
    constexpr pin_t PIN_PE5{port_t::E, 5};
    constexpr pin_t PIN_PE6{port_t::E, 6};
    constexpr pin_t PIN_PE7{port_t::E, 7};
    constexpr pin_t PIN_PE8{port_t::E, 8};
    constexpr pin_t PIN_PE9{port_t::E, 9};
    constexpr pin_t PIN_PE10{port_t::E, 10};
    constexpr pin_t PIN_PE11{port_t::E, 11};
    constexpr pin_t PIN_PE12{port_t::E, 12};
    constexpr pin_t PIN_PE13{port_t::E, 13};
    constexpr pin_t PIN_PE14{port_t::E, 14};
    constexpr pin_t PIN_PE15{port_t::E, 15};

    // Port F
    constexpr pin_t PIN_PF0{port_t::F, 0};
    constexpr pin_t PIN_PF1{port_t::F, 1};
    constexpr pin_t PIN_PF2{port_t::F, 2};
    constexpr pin_t PIN_PF3{port_t::F, 3};
    constexpr pin_t PIN_PF4{port_t::F, 4};
    constexpr pin_t PIN_PF5{port_t::F, 5};
    constexpr pin_t PIN_PF6{port_t::F, 6};
    constexpr pin_t PIN_PF7{port_t::F, 7};
    constexpr pin_t PIN_PF8{port_t::F, 8};
    constexpr pin_t PIN_PF9{port_t::F, 9};
    constexpr pin_t PIN_PF10{port_t::F, 10};
    constexpr pin_t PIN_PF11{port_t::F, 11};
    constexpr pin_t PIN_PF12{port_t::F, 12};
    constexpr pin_t PIN_PF13{port_t::F, 13};
    constexpr pin_t PIN_PF14{port_t::F, 14};
    constexpr pin_t PIN_PF15{port_t::F, 15};

    // Port G
    constexpr pin_t PIN_PG0{port_t::G, 0};
    constexpr pin_t PIN_PG1{port_t::G, 1};
    constexpr pin_t PIN_PG2{port_t::G, 2};
    constexpr pin_t PIN_PG3{port_t::G, 3};
    constexpr pin_t PIN_PG4{port_t::G, 4};
    constexpr pin_t PIN_PG5{port_t::G, 5};
    constexpr pin_t PIN_PG6{port_t::G, 6};
    constexpr pin_t PIN_PG7{port_t::G, 7};
    constexpr pin_t PIN_PG8{port_t::G, 8};
    constexpr pin_t PIN_PG9{port_t::G, 9};
    constexpr pin_t PIN_PG10{port_t::G, 10};
    constexpr pin_t PIN_PG11{port_t::G, 11};
    constexpr pin_t PIN_PG12{port_t::G, 12};
    constexpr pin_t PIN_PG13{port_t::G, 13};
    constexpr pin_t PIN_PG14{port_t::G, 14};
    constexpr pin_t PIN_PG15{port_t::G, 15};

    // Port H
    constexpr pin_t PIN_PH0{port_t::H, 0};
    constexpr pin_t PIN_PH1{port_t::H, 1};
    constexpr pin_t PIN_PH2{port_t::H, 2};
    constexpr pin_t PIN_PH3{port_t::H, 3};
    constexpr pin_t PIN_PH4{port_t::H, 4};
    constexpr pin_t PIN_PH5{port_t::H, 5};
    constexpr pin_t PIN_PH6{port_t::H, 6};
    constexpr pin_t PIN_PH7{port_t::H, 7};
    constexpr pin_t PIN_PH8{port_t::H, 8};
    constexpr pin_t PIN_PH9{port_t::H, 9};
    constexpr pin_t PIN_PH10{port_t::H, 10};
    constexpr pin_t PIN_PH11{port_t::H, 11};
    constexpr pin_t PIN_PH12{port_t::H, 12};
    constexpr pin_t PIN_PH13{port_t::H, 13};
    constexpr pin_t PIN_PH14{port_t::H, 14};
    constexpr pin_t PIN_PH15{port_t::H, 15};

    // Port J
    constexpr pin_t PIN_PJ0{port_t::J, 0};
    constexpr pin_t PIN_PJ1{port_t::J, 1};
    constexpr pin_t PIN_PJ2{port_t::J, 2};
    constexpr pin_t PIN_PJ3{port_t::J, 3};
    constexpr pin_t PIN_PJ4{port_t::J, 4};
    constexpr pin_t PIN_PJ5{port_t::J, 5};
    constexpr pin_t PIN_PJ6{port_t::J, 6};
    constexpr pin_t PIN_PJ7{port_t::J, 7};
    constexpr pin_t PIN_PJ8{port_t::J, 8};
    constexpr pin_t PIN_PJ9{port_t::J, 9};
    constexpr pin_t PIN_PJ10{port_t::J, 10};
    constexpr pin_t PIN_PJ11{port_t::J, 11};
    constexpr pin_t PIN_PJ12{port_t::J, 12};
    constexpr pin_t PIN_PJ13{port_t::J, 13};
    constexpr pin_t PIN_PJ14{port_t::J, 14};
    constexpr pin_t PIN_PJ15{port_t::J, 15};

    // Port K
    constexpr pin_t PIN_PK0{port_t::K, 0};
    constexpr pin_t PIN_PK1{port_t::K, 1};
    constexpr pin_t PIN_PK2{port_t::K, 2};
    constexpr pin_t PIN_PK3{port_t::K, 3};
    constexpr pin_t PIN_PK4{port_t::K, 4};
    constexpr pin_t PIN_PK5{port_t::K, 5};
    constexpr pin_t PIN_PK6{port_t::K, 6};
    constexpr pin_t PIN_PK7{port_t::K, 7};
    constexpr pin_t PIN_PK8{port_t::K, 8};
    constexpr pin_t PIN_PK9{port_t::K, 9};
    constexpr pin_t PIN_PK10{port_t::K, 10};
    constexpr pin_t PIN_PK11{port_t::K, 11};
    constexpr pin_t PIN_PK12{port_t::K, 12};
    constexpr pin_t PIN_PK13{port_t::K, 13};
    constexpr pin_t PIN_PK14{port_t::K, 14};
    constexpr pin_t PIN_PK15{port_t::K, 15};

    // Port L
    constexpr pin_t PIN_PL0{port_t::L, 0};
    constexpr pin_t PIN_PL1{port_t::L, 1};
    constexpr pin_t PIN_PL2{port_t::L, 2};
    constexpr pin_t PIN_PL3{port_t::L, 3};
    constexpr pin_t PIN_PL4{port_t::L, 4};
    constexpr pin_t PIN_PL5{port_t::L, 5};
    constexpr pin_t PIN_PL6{port_t::L, 6};
    constexpr pin_t PIN_PL7{port_t::L, 7};
    constexpr pin_t PIN_PL8{port_t::L, 8};
    constexpr pin_t PIN_PL9{port_t::L, 9};
    constexpr pin_t PIN_PL10{port_t::L, 10};
    constexpr pin_t PIN_PL11{port_t::L, 11};
    constexpr pin_t PIN_PL12{port_t::L, 12};
    constexpr pin_t PIN_PL13{port_t::L, 13};
    constexpr pin_t PIN_PL14{port_t::L, 14};
    constexpr pin_t PIN_PL15{port_t::L, 15};

    #if defined(__AVR_ATmega328P__)  // Arduino Uno
    namespace arduino {
        constexpr pin_t D0  = PIN_PD0;
        constexpr pin_t D1  = PIN_PD1;
        constexpr pin_t D2  = PIN_PD2;
        constexpr pin_t D3  = PIN_PD3;
        constexpr pin_t D4  = PIN_PD4;
        constexpr pin_t D5  = PIN_PD5;
        constexpr pin_t D6  = PIN_PD6;
        constexpr pin_t D7  = PIN_PD7;
        constexpr pin_t D8  = PIN_PB0;
        constexpr pin_t D9  = PIN_PB1;
        constexpr pin_t D10 = PIN_PB2;
        constexpr pin_t D11 = PIN_PB3;
        constexpr pin_t D12 = PIN_PB4;
        constexpr pin_t D13 = PIN_PB5;

        constexpr pin_t A0 = PIN_PC0;
        constexpr pin_t A1 = PIN_PC1;
        constexpr pin_t A2 = PIN_PC2;
        constexpr pin_t A3 = PIN_PC3;
        constexpr pin_t A4 = PIN_PC4;
        constexpr pin_t A5 = PIN_PC5;
    }
    #endif

    #if defined(__AVR_ATmega2560__)  // Arduino Mega
    namespace arduino {
        // Digital pins
        constexpr pin_t D0  = PIN_PE0;
        constexpr pin_t D1  = PIN_PE1;
        constexpr pin_t D2  = PIN_PE4;
        constexpr pin_t D3  = PIN_PE5;
        constexpr pin_t D4  = PIN_PG5;
        constexpr pin_t D5  = PIN_PE3;
        constexpr pin_t D6  = PIN_PH3;
        constexpr pin_t D7  = PIN_PH4;
        constexpr pin_t D8  = PIN_PH5;
        constexpr pin_t D9  = PIN_PH6;
        constexpr pin_t D10 = PIN_PB4;
        constexpr pin_t D11 = PIN_PB5;
        constexpr pin_t D12 = PIN_PB6;
        constexpr pin_t D13 = PIN_PB7;
        constexpr pin_t D14 = PIN_PJ1;
        constexpr pin_t D15 = PIN_PJ0;
        constexpr pin_t D16 = PIN_PH1;
        constexpr pin_t D17 = PIN_PH0;
        constexpr pin_t D18 = PIN_PD3;
        constexpr pin_t D19 = PIN_PD2;
        constexpr pin_t D20 = PIN_PD1;
        constexpr pin_t D21 = PIN_PD0;
        constexpr pin_t D22 = PIN_PA0;
        constexpr pin_t D23 = PIN_PA1;
        constexpr pin_t D24 = PIN_PA2;
        constexpr pin_t D25 = PIN_PA3;
        constexpr pin_t D26 = PIN_PA4;
        constexpr pin_t D27 = PIN_PA5;
        constexpr pin_t D28 = PIN_PA6;
        constexpr pin_t D29 = PIN_PA7;
        constexpr pin_t D30 = PIN_PC7;
        constexpr pin_t D31 = PIN_PC6;
        constexpr pin_t D32 = PIN_PC5;
        constexpr pin_t D33 = PIN_PC4;
        constexpr pin_t D34 = PIN_PC3;
        constexpr pin_t D35 = PIN_PC2;
        constexpr pin_t D36 = PIN_PC1;
        constexpr pin_t D37 = PIN_PC0;
        constexpr pin_t D38 = PIN_PD7;
        constexpr pin_t D39 = PIN_PG2;
        constexpr pin_t D40 = PIN_PG1;
        constexpr pin_t D41 = PIN_PG0;
        constexpr pin_t D42 = PIN_PL7;
        constexpr pin_t D43 = PIN_PL6;
        constexpr pin_t D44 = PIN_PL5;
        constexpr pin_t D45 = PIN_PL4;
        constexpr pin_t D46 = PIN_PL3;
        constexpr pin_t D47 = PIN_PL2;
        constexpr pin_t D48 = PIN_PL1;
        constexpr pin_t D49 = PIN_PL0;
        constexpr pin_t D50 = PIN_PB3;
        constexpr pin_t D51 = PIN_PB2;
        constexpr pin_t D52 = PIN_PB1;
        constexpr pin_t D53 = PIN_PB0;

        // Analog pins
        constexpr pin_t A0  = PIN_PF0;
        constexpr pin_t A1  = PIN_PF1;
        constexpr pin_t A2  = PIN_PF2;
        constexpr pin_t A3  = PIN_PF3;
        constexpr pin_t A4  = PIN_PF4;
        constexpr pin_t A5  = PIN_PF5;
        constexpr pin_t A6  = PIN_PF6;
        constexpr pin_t A7  = PIN_PF7;
        constexpr pin_t A8  = PIN_PK0;
        constexpr pin_t A9  = PIN_PK1;
        constexpr pin_t A10 = PIN_PK2;
        constexpr pin_t A11 = PIN_PK3;
        constexpr pin_t A12 = PIN_PK4;
        constexpr pin_t A13 = PIN_PK5;
        constexpr pin_t A14 = PIN_PK6;
        constexpr pin_t A15 = PIN_PK7;
    }
    #endif

    #if defined(__AVR_ATmega32U4__)  // Arduino Micro
    namespace arduino {
        constexpr pin_t D0  = PIN_PD2;
        constexpr pin_t D1  = PIN_PD3;
        constexpr pin_t D2  = PIN_PD1;
        constexpr pin_t D3  = PIN_PD0;
        constexpr pin_t D4  = PIN_PD4;
        constexpr pin_t D5  = PIN_PC6;
        constexpr pin_t D6  = PIN_PD7;
        constexpr pin_t D7  = PIN_PE6;
        constexpr pin_t D8  = PIN_PB4;
        constexpr pin_t D9  = PIN_PB5;
        constexpr pin_t D10 = PIN_PB6;
        constexpr pin_t D11 = PIN_PB7;
        constexpr pin_t D12 = PIN_PD6;
        constexpr pin_t D13 = PIN_PC7;

        constexpr pin_t A0 = PIN_PF7;
        constexpr pin_t A1 = PIN_PF6;
        constexpr pin_t A2 = PIN_PF5;
        constexpr pin_t A3 = PIN_PF4;
        constexpr pin_t A4 = PIN_PF1;
        constexpr pin_t A5 = PIN_PF0;
    }
    #endif

    #ifdef RA4M1  // Define this macro when compiling for RA4M1-based boards
    namespace arduino {

        // Digital pins
        constexpr pin_t D0  = pin_t{port_t::P3, 1};   // P301
        constexpr pin_t D1  = pin_t{port_t::P3, 2};   // P302
        constexpr pin_t D2  = pin_t{port_t::P1, 5};   // P105
        constexpr pin_t D3  = pin_t{port_t::P1, 4};   // P104
        constexpr pin_t D4  = pin_t{port_t::P1, 3};   // P103 (CANTX)
        constexpr pin_t D5  = pin_t{port_t::P1, 2};   // P102 (CANRX)
        constexpr pin_t D6  = pin_t{port_t::P1, 6};   // P106
        constexpr pin_t D7  = pin_t{port_t::P1, 7};   // P107
        constexpr pin_t D8  = pin_t{port_t::P3, 4};   // P304
        constexpr pin_t D9  = pin_t{port_t::P3, 3};   // P303
        constexpr pin_t D10 = pin_t{port_t::P1, 12};  // P112
        constexpr pin_t D11 = pin_t{port_t::P1, 9};   // P109
        constexpr pin_t D12 = pin_t{port_t::P1, 10};  // P110
        constexpr pin_t D13 = pin_t{port_t::P1, 11};  // P111

        // Analog pins
        constexpr pin_t A0 = pin_t{port_t::P1, 14};   // P014_AN09
        constexpr pin_t A1 = pin_t{port_t::P0, 0};    // P000_AN00
        constexpr pin_t A2 = pin_t{port_t::P0, 1};    // P001_AN01
        constexpr pin_t A3 = pin_t{port_t::P0, 2};    // P002_AN02
        constexpr pin_t A4 = pin_t{port_t::P1, 1};    // P101_AN21 (SDA)
        constexpr pin_t A5 = pin_t{port_t::P1, 0};    // P100_AN22 (SCL)

    }
    #endif

} // namespace rl




#endif // RTOSLESS_PINS_H
