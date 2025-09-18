#include "SevenSegment.h"
#include <rtosless.h>
#include <rtosless_gpio.h>
#include <rtosless_debounce.h>
SG::SevenSegment display(PIN_DISP_DAT, PIN_DISP_SHCK, PIN_DISP_STCK);
bool isRunning = true;
uint32_t offset = 0;

void setup() {
  setupPins();
  rl::gpio_pin_mode(rl::arduino::D13, rl::gpio_mode::output);
  display.init();
  display.setChar(0,'t');
  display.setChar(1,'e');
  display.setChar(2,'s');
  display.setChar(3,'t');  
}

void loop() {
  rl::kernel();
  
  if (RL_DEBOUNCED_FALLING(rl::gpio_read(PIN_BTN_1))) {
    rl::gpio_write(PIN_LED, HIGH);
    rl::timer_do_in_millis([](){rl::gpio_write(PIN_LED, LOW);}, 3000);
  }

  RL_EVERY_MILLIS(250) {
    rl::gpio_toggle(rl::arduino::D13);
  }

  auto now = rl::kernel_millis();
  auto tens = (now / 100) % 10;
  auto seconds = (now / 1000) % 60;
  auto minutes = (now / 60000) % 10;
  auto dot = (now % 1000) > 500;

  display.setDot(0, dot);
  display.setDot(2, dot);
  display.setChar(0, '0' + minutes);
  display.setChar(1, '0' + seconds / 10);
  display.setChar(2, '0' + seconds % 10);
  display.setChar(3, '0' + tens % 10);
}
