#ifndef __RCC_H
#define __RCC_H

#include "stm32h7xx_hal.h"
#include "uart.h"

void SystemClock_Config(void);
void MPU_Config(void);
void Error_Handler(void);
void MX_GPIO_Init(void);
void PLL_CLK_Ptintf(void);
#endif
