#include "LPC8xx.h"

#define RCK 3
#define SER 1
#define SCK 2

void SwitchMatrix_Init() {
  // Enable SWM clock
  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 7);

  // Pin Assign 8 bit Configuration
  // none

  // Pin Assign 1 bit Configuration
  // RESET
  LPC_SWM->PINENABLE0 = 0xffffffbfUL;
}

void degit_disp(uint8_t n) {
  volatile int16_t i;
  volatile uint8_t out_data;

  LPC_GPIO_PORT->CLR0 = 1 << RCK;

  for (i = 7; i >= 0; i--) {
    LPC_GPIO_PORT->CLR0 = 1 << SCK;
    out_data = n & (1 << i);
    out_data = (out_data >> i) & 0x1;
    if (out_data == 1) {
      LPC_GPIO_PORT->SET0 = 1 << SER;
    } else {
      LPC_GPIO_PORT->CLR0 = 1 << SER;
    }
    LPC_GPIO_PORT->SET0 = 1 << SCK;
  }

  LPC_GPIO_PORT->CLR0 = 1 << SCK;
  LPC_GPIO_PORT->SET0 = 1 << RCK;
}

int main(void) {
  volatile int32_t i, j;
  volatile const uint8_t degit_data[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00100111, // 7
    0b01111111, // 8
    0b01101111, // 9
  };

  SwitchMatrix_Init();

  LPC_GPIO_PORT->DIR0 |= (1 << RCK);
  LPC_GPIO_PORT->DIR0 |= (1 << SER);
  LPC_GPIO_PORT->DIR0 |= (1 << SCK);

  for (i = 0; i < 10; i++) {
    degit_disp(degit_data[i]);
    for (j = 0; j < 0xFFFFF; j++);
  }
}
