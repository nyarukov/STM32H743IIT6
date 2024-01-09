#include "main.h"

int main(void)
{
	MPU_Config();
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	Uart_Init(115200);
	PLL_CLK_Ptintf();
	
	System_Task();
	
  while (1)
  {
    
  }
}
