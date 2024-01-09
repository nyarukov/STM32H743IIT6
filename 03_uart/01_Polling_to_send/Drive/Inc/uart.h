#ifndef __UART_H
#define __UART_H

#include "stm32h7xx_hal.h"

extern UART_HandleTypeDef uart1;

void Uart_Init(uint32_t baudrate);
void Uart_SendChar(uint8_t ch);
void Uart_SendString(uint8_t *str);
void Uart_SendArray(uint8_t *arr,uint8_t length);
void Uart_num(uint64_t num);
#endif // !__UART_H