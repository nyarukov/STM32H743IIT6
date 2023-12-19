#ifndef __UART_H
#define __UART_H

#include "stm32h7xx_hal.h"

extern UART_HandleTypeDef uart1;

void Uart_Init(uint32_t baudrate);
void Uart_SendChar(uint8_t c);
#endif // !__UART_H