#include "main.h"

int main(void)
{
  MPU_Config();
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  Uart_Init(115200);
  PLL_CLK_Ptintf();

  Key_Init();
  uint8_t sw=0;
  while (1)
  {
    sw=pollKeys();
    if(sw!=NULL){
      Uart_Printf("KEY:",sw);
    }
  }

}
