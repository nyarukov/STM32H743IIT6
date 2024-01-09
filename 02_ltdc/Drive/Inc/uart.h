#ifndef __UART_H
#define __UART_H

#include "stm32h7xx_hal.h"
#include "bit_control.h"
#include "stdio.h"

void Uart_Init(uint32_t baudrate);
void Uart_SendChar(u8 ch);
void Uart_SendString(u8 *str);
void Uart_SendArray(u8 *arr,u32 length);
void Uart_num(u64 num);
void Uart_Printf(u8 *str,u64 num);
#endif // !__UART_H
