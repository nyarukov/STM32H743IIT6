#ifndef __UART_H
#define __UART_H

#include "stm32h7xx_hal.h"

#define TX_SIZE 1024
#define RX_SIZE 1024
#define RX_MAX  255
/*位置控制结构体*/
typedef struct
{
    uint8_t *start;
    uint8_t *end;
} LCB;
/*总*/
typedef struct
{
    UART_HandleTypeDef UARTx;

    uint32_t TxCounter;
    LCB TxLocation[10];
    LCB *TxInPrt;
    LCB *TxOutPrt;
    LCB *TxEndPrt;
    
    uint32_t RxCounter;
    LCB RxLocation[10];
    LCB *RxInPrt;
    LCB *RxOutPrt;
    LCB *RxEndPrt;
} UCB;

extern UCB uart1;

void Uart_Init(uint32_t baudrate);
void RingBuffer_Init(void);
void Uart_SendChar(uint8_t c);
#endif // !__UART_H