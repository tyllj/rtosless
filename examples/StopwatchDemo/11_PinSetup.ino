#include <rtosless_gpio.h>

namespace {
    void setupPins() {
      rl::gpio_pin_mode(PIN_DISP_DAT, rl::gpio_mode::output);
      rl::gpio_pin_mode(PIN_DISP_STCK, rl::gpio_mode::output);
      rl::gpio_pin_mode(PIN_DISP_SHCK, rl::gpio_mode::output);
      rl::gpio_pin_mode(PIN_LED, rl::gpio_mode::output);
      rl::gpio_pin_mode(PIN_BTN_1, rl::gpio_mode::input_pullup);
      rl::gpio_pin_mode(PIN_BTN_2, rl::gpio_mode::input_pullup);
    }
}
