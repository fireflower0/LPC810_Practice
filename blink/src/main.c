#include "LPC8xx.h"

void SwitchMatrix_Init() {
  // Enable SWM clock
  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 7);

  // Pin Assign 8 bit Configuration
  // none

  // Pin Assign 1 bit Configuration
  // RESET
  LPC_SWM->PINENABLE0 = 0xffffffbfUL;
}

int main() {
  volatile int8_t SW1;

  SwitchMatrix_Init();

  LPC_GPIO_PORT->DIR0 |= (1 << 2);
  LPC_GPIO_PORT->DIR0 &= ~(1 << 1);

  while(1) {
    SW1 = (LPC_GPIO_PORT->PIN0 & (1 << 1)) >> 1;

    if (SW1 == 1) {
      LPC_GPIO_PORT->CLR0 = 1 << 2;
    } else {
      LPC_GPIO_PORT->SET0 = 1 << 2;
    }
  }
}
