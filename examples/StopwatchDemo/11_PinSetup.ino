#include <rtosless_gpio.h>

namespace {
    void setupPins() {
      rl_gpio_pin_mode(PIN_DISP_DAT, OUTPUT);
      rl_gpio_pin_mode(PIN_DISP_STCK, OUTPUT);
      rl_gpio_pin_mode(PIN_DISP_SHCK, OUTPUT);
      rl_gpio_pin_mode(PIN_LED_YELLOW, OUTPUT);
      rl_gpio_pin_mode(PIN_LED_RED, OUTPUT);
      rl_gpio_pin_mode(PIN_BTN_1, INPUT_PULLUP);
      rl_gpio_pin_mode(PIN_BTN_2, INPUT_PULLUP);
    }
}
