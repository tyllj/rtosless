#include <rtosless.h>
#include <rtosless_gpio.h>
#include <rtosless_debounce.h>
#include <rtosless_kernel.h>
#include <rtosless_timer.h>
#include <rtosless_loop_timer.h>

#include "SevenSegment.h"

SG::SevenSegment display(PIN_DISP_DAT, PIN_DISP_SHCK, PIN_DISP_STCK);

void setup() {
  setupPins();
  display.init();
  display.setChar(0,'t');
  display.setChar(1,'e');
  display.setChar(2,'s');
  display.setChar(3,'t');  
}

void loop() {
  rl_kernel(millis(), micros());
  
  if (RL_DEBOUNCED_FALLING(rl_gpio_read(PIN_BTN_1))) {
    rl_gpio_write(PIN_LED_YELLOW, HIGH);
    rl_timer_do_in_millis(3000, [](void*) { rl_gpio_write(PIN_LED_YELLOW, LOW); }, nullptr);
    //_delay_ms(3000);
    //rl_gpio_write(PIN_LED_YELLOW, LOW);
  }

  RL_EVERY_MILLIS(250) {
    rl_gpio_toggle(PIN_LED_RED);
  }

  uint32_t now = rl_millis();
  uint32_t tens = (now / 100) % 10;
  uint32_t seconds = (now / 1000) % 60;
  uint32_t minutes = (now / 60000) % 10;
  bool dot = (now % 1000) > 500;

  display.setDot(0, dot);
  display.setDot(2, dot);
  display.setChar(0, '0' + minutes);
  display.setChar(1, '0' + seconds / 10);
  display.setChar(2, '0' + seconds % 10);
  display.setChar(3, '0' + tens % 10);
}
