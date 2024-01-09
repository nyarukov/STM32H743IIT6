#ifndef __LED_H
#define __LED_H

#include "stm32h7xx_hal.h"
#include "stdbool.h"
#include "bit_control.h"

#define led_g	GPIO_PIN_0
#define led_r	GPIO_PIN_1
#define led_b	GPIO_PIN_2

void Led_Init(u16 GPIO_Pinx);
void Led_Set(u16 GPIO_Pinx,bool value);

#endif
