#ifndef RTOSLESS_PINS_H
#define RTOSLESS_PINS_H

#include "rtosless_gpio.h"

namespace rl {

    // Port A
    constexpr pin_t PA0{port_t::A, 0};
    constexpr pin_t PA1{port_t::A, 1};
    constexpr pin_t PA2{port_t::A, 2};
    constexpr pin_t PA3{port_t::A, 3};
    constexpr pin_t PA4{port_t::A, 4};
    constexpr pin_t PA5{port_t::A, 5};
    constexpr pin_t PA6{port_t::A, 6};
    constexpr pin_t PA7{port_t::A, 7};
    constexpr pin_t PA8{port_t::A, 8};
    constexpr pin_t PA9{port_t::A, 9};
    constexpr pin_t PA10{port_t::A, 10};
    constexpr pin_t PA11{port_t::A, 11};
    constexpr pin_t PA12{port_t::A, 12};
    constexpr pin_t PA13{port_t::A, 13};
    constexpr pin_t PA14{port_t::A, 14};
    constexpr pin_t PA15{port_t::A, 15};

    // Port B
    constexpr pin_t PB0{port_t::B, 0};
    constexpr pin_t PB1{port_t::B, 1};
    constexpr pin_t PB2{port_t::B, 2};
    constexpr pin_t PB3{port_t::B, 3};
    constexpr pin_t PB4{port_t::B, 4};
    constexpr pin_t PB5{port_t::B, 5};
    constexpr pin_t PB6{port_t::B, 6};
    constexpr pin_t PB7{port_t::B, 7};
    constexpr pin_t PB8{port_t::B, 8};
    constexpr pin_t PB9{port_t::B, 9};
    constexpr pin_t PB10{port_t::B, 10};
    constexpr pin_t PB11{port_t::B, 11};
    constexpr pin_t PB12{port_t::B, 12};
    constexpr pin_t PB13{port_t::B, 13};
    constexpr pin_t PB14{port_t::B, 14};
    constexpr pin_t PB15{port_t::B, 15};

    // Port C
    constexpr pin_t PC0{port_t::C, 0};
    constexpr pin_t PC1{port_t::C, 1};
    constexpr pin_t PC2{port_t::C, 2};
    constexpr pin_t PC3{port_t::C, 3};
    constexpr pin_t PC4{port_t::C, 4};
    constexpr pin_t PC5{port_t::C, 5};
    constexpr pin_t PC6{port_t::C, 6};
    constexpr pin_t PC7{port_t::C, 7};
    constexpr pin_t PC8{port_t::C, 8};
    constexpr pin_t PC9{port_t::C, 9};
    constexpr pin_t PC10{port_t::C, 10};
    constexpr pin_t PC11{port_t::C, 11};
    constexpr pin_t PC12{port_t::C, 12};
    constexpr pin_t PC13{port_t::C, 13};
    constexpr pin_t PC14{port_t::C, 14};
    constexpr pin_t PC15{port_t::C, 15};

    // Port D
    constexpr pin_t PD0{port_t::D, 0};
    constexpr pin_t PD1{port_t::D, 1};
    constexpr pin_t PD2{port_t::D, 2};
    constexpr pin_t PD3{port_t::D, 3};
    constexpr pin_t PD4{port_t::D, 4};
    constexpr pin_t PD5{port_t::D, 5};
    constexpr pin_t PD6{port_t::D, 6};
    constexpr pin_t PD7{port_t::D, 7};
    constexpr pin_t PD8{port_t::D, 8};
    constexpr pin_t PD9{port_t::D, 9};
    constexpr pin_t PD10{port_t::D, 10};
    constexpr pin_t PD11{port_t::D, 11};
    constexpr pin_t PD12{port_t::D, 12};
    constexpr pin_t PD13{port_t::D, 13};
    constexpr pin_t PD14{port_t::D, 14};
    constexpr pin_t PD15{port_t::D, 15};

    // Port E
    constexpr pin_t PE0{port_t::E, 0};
    constexpr pin_t PE1{port_t::E, 1};
    constexpr pin_t PE2{port_t::E, 2};
    constexpr pin_t PE3{port_t::E, 3};
    constexpr pin_t PE4{port_t::E, 4};
    constexpr pin_t PE5{port_t::E, 5};
    constexpr pin_t PE6{port_t::E, 6};
    constexpr pin_t PE7{port_t::E, 7};
    constexpr pin_t PE8{port_t::E, 8};
    constexpr pin_t PE9{port_t::E, 9};
    constexpr pin_t PE10{port_t::E, 10};
    constexpr pin_t PE11{port_t::E, 11};
    constexpr pin_t PE12{port_t::E, 12};
    constexpr pin_t PE13{port_t::E, 13};
    constexpr pin_t PE14{port_t::E, 14};
    constexpr pin_t PE15{port_t::E, 15};

    // Port F
    constexpr pin_t PF0{port_t::F, 0};
    constexpr pin_t PF1{port_t::F, 1};
    constexpr pin_t PF2{port_t::F, 2};
    constexpr pin_t PF3{port_t::F, 3};
    constexpr pin_t PF4{port_t::F, 4};
    constexpr pin_t PF5{port_t::F, 5};
    constexpr pin_t PF6{port_t::F, 6};
    constexpr pin_t PF7{port_t::F, 7};
    constexpr pin_t PF8{port_t::F, 8};
    constexpr pin_t PF9{port_t::F, 9};
    constexpr pin_t PF10{port_t::F, 10};
    constexpr pin_t PF11{port_t::F, 11};
    constexpr pin_t PF12{port_t::F, 12};
    constexpr pin_t PF13{port_t::F, 13};
    constexpr pin_t PF14{port_t::F, 14};
    constexpr pin_t PF15{port_t::F, 15};

    // Port G
    constexpr pin_t PG0{port_t::G, 0};
    constexpr pin_t PG1{port_t::G, 1};
    constexpr pin_t PG2{port_t::G, 2};
    constexpr pin_t PG3{port_t::G, 3};
    constexpr pin_t PG4{port_t::G, 4};
    constexpr pin_t PG5{port_t::G, 5};
    constexpr pin_t PG6{port_t::G, 6};
    constexpr pin_t PG7{port_t::G, 7};
    constexpr pin_t PG8{port_t::G, 8};
    constexpr pin_t PG9{port_t::G, 9};
    constexpr pin_t PG10{port_t::G, 10};
    constexpr pin_t PG11{port_t::G, 11};
    constexpr pin_t PG12{port_t::G, 12};
    constexpr pin_t PG13{port_t::G, 13};
    constexpr pin_t PG14{port_t::G, 14};
    constexpr pin_t PG15{port_t::G, 15};

    // Port H
    constexpr pin_t PH0{port_t::H, 0};
    constexpr pin_t PH1{port_t::H, 1};
    constexpr pin_t PH2{port_t::H, 2};
    constexpr pin_t PH3{port_t::H, 3};
    constexpr pin_t PH4{port_t::H, 4};
    constexpr pin_t PH5{port_t::H, 5};
    constexpr pin_t PH6{port_t::H, 6};
    constexpr pin_t PH7{port_t::H, 7};
    constexpr pin_t PH8{port_t::H, 8};
    constexpr pin_t PH9{port_t::H, 9};
    constexpr pin_t PH10{port_t::H, 10};
    constexpr pin_t PH11{port_t::H, 11};
    constexpr pin_t PH12{port_t::H, 12};
    constexpr pin_t PH13{port_t::H, 13};
    constexpr pin_t PH14{port_t::H, 14};
    constexpr pin_t PH15{port_t::H, 15};

    // Port J
    constexpr pin_t PJ0{port_t::J, 0};
    constexpr pin_t PJ1{port_t::J, 1};
    constexpr pin_t PJ2{port_t::J, 2};
    constexpr pin_t PJ3{port_t::J, 3};
    constexpr pin_t PJ4{port_t::J, 4};
    constexpr pin_t PJ5{port_t::J, 5};
    constexpr pin_t PJ6{port_t::J, 6};
    constexpr pin_t PJ7{port_t::J, 7};
    constexpr pin_t PJ8{port_t::J, 8};
    constexpr pin_t PJ9{port_t::J, 9};
    constexpr pin_t PJ10{port_t::J, 10};
    constexpr pin_t PJ11{port_t::J, 11};
    constexpr pin_t PJ12{port_t::J, 12};
    constexpr pin_t PJ13{port_t::J, 13};
    constexpr pin_t PJ14{port_t::J, 14};
    constexpr pin_t PJ15{port_t::J, 15};

    // Port K
    constexpr pin_t PK0{port_t::K, 0};
    constexpr pin_t PK1{port_t::K, 1};
    constexpr pin_t PK2{port_t::K, 2};
    constexpr pin_t PK3{port_t::K, 3};
    constexpr pin_t PK4{port_t::K, 4};
    constexpr pin_t PK5{port_t::K, 5};
    constexpr pin_t PK6{port_t::K, 6};
    constexpr pin_t PK7{port_t::K, 7};
    constexpr pin_t PK8{port_t::K, 8};
    constexpr pin_t PK9{port_t::K, 9};
    constexpr pin_t PK10{port_t::K, 10};
    constexpr pin_t PK11{port_t::K, 11};
    constexpr pin_t PK12{port_t::K, 12};
    constexpr pin_t PK13{port_t::K, 13};
    constexpr pin_t PK14{port_t::K, 14};
    constexpr pin_t PK15{port_t::K, 15};

    // Port L
    constexpr pin_t PL0{port_t::L, 0};
    constexpr pin_t PL1{port_t::L, 1};
    constexpr pin_t PL2{port_t::L, 2};
    constexpr pin_t PL3{port_t::L, 3};
    constexpr pin_t PL4{port_t::L, 4};
    constexpr pin_t PL5{port_t::L, 5};
    constexpr pin_t PL6{port_t::L, 6};
    constexpr pin_t PL7{port_t::L, 7};
    constexpr pin_t PL8{port_t::L, 8};
    constexpr pin_t PL9{port_t::L, 9};
    constexpr pin_t PL10{port_t::L, 10};
    constexpr pin_t PL11{port_t::L, 11};
    constexpr pin_t PL12{port_t::L, 12};
    constexpr pin_t PL13{port_t::L, 13};
    constexpr pin_t PL14{port_t::L, 14};
    constexpr pin_t PL15{port_t::L, 15};

    #if defined(__AVR_ATmega328P__)  // Arduino Uno
    namespace arduino {
        constexpr pin_t D0  = PD0;
        constexpr pin_t D1  = PD1;
        constexpr pin_t D2  = PD2;
        constexpr pin_t D3  = PD3;
        constexpr pin_t D4  = PD4;
        constexpr pin_t D5  = PD5;
        constexpr pin_t D6  = PD6;
        constexpr pin_t D7  = PD7;
        constexpr pin_t D8  = PB0;
        constexpr pin_t D9  = PB1;
        constexpr pin_t D10 = PB2;
        constexpr pin_t D11 = PB3;
        constexpr pin_t D12 = PB4;
        constexpr pin_t D13 = PB5;

        constexpr pin_t A0 = PC0;
        constexpr pin_t A1 = PC1;
        constexpr pin_t A2 = PC2;
        constexpr pin_t A3 = PC3;
        constexpr pin_t A4 = PC4;
        constexpr pin_t A5 = PC5;
    }
    #endif

    #if defined(__AVR_ATmega2560__)  // Arduino Mega
    namespace arduino {
        constexpr pin_t D0  = PE0;
        constexpr pin_t D1  = PE1;
        constexpr pin_t D2  = PE4;
        constexpr pin_t D3  = PE5;
        constexpr pin_t D4  = PG5;
        constexpr pin_t D5  = PE3;
        constexpr pin_t D6  = PH3;
        constexpr pin_t D7  = PH4;
        constexpr pin_t D8  = PH5;
        constexpr pin_t D9  = PH6;
        constexpr pin_t D10 = PB4;
        constexpr pin_t D11 = PB5;
        constexpr pin_t D12 = PB6;
        constexpr pin_t D13 = PB7;

        constexpr pin_t A0 = PF0;
        constexpr pin_t A1 = PF1;
        constexpr pin_t A2 = PF2;
        constexpr pin_t A3 = PF3;
        constexpr pin_t A4 = PF4;
        constexpr pin_t A5 = PF5;
        constexpr pin_t A6 = PF6;
        constexpr pin_t A7 = PF7;
    }
    #endif

    #if defined(__AVR_ATmega32U4__)  // Arduino Micro
    namespace arduino {
        constexpr pin_t D0  = PD2;
        constexpr pin_t D1  = PD3;
        constexpr pin_t D2  = PD1;
        constexpr pin_t D3  = PD0;
        constexpr pin_t D4  = PD4;
        constexpr pin_t D5  = PC6;
        constexpr pin_t D6  = PD7;
        constexpr pin_t D7  = PE6;
        constexpr pin_t D8  = PB4;
        constexpr pin_t D9  = PB5;
        constexpr pin_t D10 = PB6;
        constexpr pin_t D11 = PB7;
        constexpr pin_t D12 = PD6;
        constexpr pin_t D13 = PC7;

        constexpr pin_t A0 = PF7;
        constexpr pin_t A1 = PF6;
        constexpr pin_t A2 = PF5;
        constexpr pin_t A3 = PF4;
        constexpr pin_t A4 = PF1;
        constexpr pin_t A5 = PF0;
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
