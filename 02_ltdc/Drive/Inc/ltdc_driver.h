#ifndef __LTDC_DRIVER_H
#define __LTDC_DRIVER_H

#include "stm32h7xx_hal.h"
#include "bit_control.h"
#include "sdram.h"

#define LTCD_BIT(n)      ((n)? __GPIO_SET_BIT(GPIOH,GPIO_PIN_6):__GPIO_RESET_BIT(GPIOH,GPIO_PIN_6))

void LTDC_Init(void);

#endif // !__LTDC_DRIVER_H
