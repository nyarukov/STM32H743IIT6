#ifndef __LED_H
#define __LED_H

#include "stm32h7xx_hal.h"
#include "stdbool.h"

enum Led_id{
	led_r = 0x2,
	led_g = 0x1,
	led_b = 0x4,
};

void Led_Init(enum Led_id id);
void Led_Set(enum Led_id id,bool value);

#endif
