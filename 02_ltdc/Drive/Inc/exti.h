#ifndef __EXTI_H
#define __EXTI_H

#include "stm32h7xx_hal.h"
#include "bit_control.h"

/*------------------------SW----------------------------------*/
#define ECH11_RCC_GPIOx_CLK()       __HAL_RCC_GPIOI_CLK_ENABLE();
#define GPIO_MAX    3

typedef struct{
    GPIO_TypeDef *gpiox;
    u16 pin;
    u32 mode;
    u32 pull;
    u32 speed;
    IRQn_Type irq;
}GPIO_Config;

void EXTI_Config(void);

#endif // !__EXIT_H
