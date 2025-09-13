#include "Button.h"
#include "SevenSegment.h"
#include "Rtos.h"

SG::SevenSegment display(PIN_DISP_DAT, PIN_DISP_SHCK, PIN_DISP_STCK);
bool isRunning = true;
uint32_t offset = 0;

void setup() {
  display.init();
}

void loop() {
  rl::kernel();

  RL_EVERY_MILLIS(500) {

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
