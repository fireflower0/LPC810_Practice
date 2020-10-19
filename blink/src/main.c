#include "LPC8xx.h"

/* スイッチ・マトリクスの設定 */
void SwitchMatrix_Init() {
  /* Enable SWM clock */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 7);

  /* Pin Assign 8 bit Configuration */
  // none

  /* Pin Assign 1 bit Configuration */
  // RESET
  LPC_SWM->PINENABLE0 = 0xffffffbfUL;
}

int main() {
  volatile int8_t SW1;

  /* スイッチ・マトリクス設定 */
  SwitchMatrix_Init();

  /* ポートの方向決定 */
  LPC_GPIO_PORT->DIR0 |= (1 << 2);  // PIO0_2を出力ポートに設定
  LPC_GPIO_PORT->DIR0 &= ~(1 << 1); // PIO0_1を入力ポートに設定

  while(1) {
    /* ポートの入力レベル(High/Low)の読み込み            */
    /* スイッチ入力SW1 (ON : 0 (Low), OFF : 1 (High)) */
    SW1 = (LPC_GPIO_PORT->PIN0 & (1 << 1)) >> 1;

    /* ポートの出力レベルの決定 */
    if (SW1 == 1) {
      /* スイッチ入力SW1 (OFF) */
      LPC_GPIO_PORT->CLR0 = 1 << 2; // PIO0_2をLowに設定 (LED消灯)
    } else {
      /* スイッチ入力SW1 (ON) */
      LPC_GPIO_PORT->SET0 = 1 << 2; // PIO0_2をHighに設定 (LED点灯)
    }
  }
}
