#ifndef __KEY_H
#define __KEY_H

#include "stm32h7xx_hal.h"
#include "bit_control.h"
#include "uart.h"

#define ROW_PORT    GPIOG
#define ROW_PIN_1   GPIO_PIN_2
#define ROW_PIN_2   GPIO_PIN_3
#define ROW_PIN_3   GPIO_PIN_4
#define ROW_PIN_4   GPIO_PIN_5

#define COL_PORT    GPIOD
#define COL_PIN_1   GPIO_PIN_12
#define COL_PIN_2   GPIO_PIN_13
#define COL_PIN_3   GPIO_PIN_14
#define COL_PIN_4   GPIO_PIN_15

void Key_Matrix(void);
u8 pollKeys(void);

#endif // !__KEY_H
