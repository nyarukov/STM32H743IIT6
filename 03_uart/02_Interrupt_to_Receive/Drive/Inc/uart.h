#ifndef __UART_H
#define __UART_H

#include "stm32h7xx_hal.h"

#define DATA_MAX    256
#define SIZE        20

extern UART_HandleTypeDef uart1;
extern uint8_t rxstate;
extern uint8_t rxdata[DATA_MAX],txdata[DATA_MAX];

void Uart_Init(uint32_t baudrate);
void Uart_SendChar(uint8_t c);
#endif // !__UART_H