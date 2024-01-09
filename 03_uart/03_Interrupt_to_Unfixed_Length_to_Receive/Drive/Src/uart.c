#include "uart.h"

UCB uart1;
uint8_t TxBuff[TX_SIZE],RxBuff[RX_SIZE];

void Uart_Init(uint32_t baudrate){
    uart1.UARTx.Instance=USART1;
    uart1.UARTx.Init.BaudRate=baudrate;
    uart1.UARTx.Init.WordLength=UART_WORDLENGTH_8B;
    uart1.UARTx.Init.StopBits=UART_STOPBITS_1;
    uart1.UARTx.Init.Parity=UART_PARITY_NONE;
    uart1.UARTx.Init.Mode=UART_MODE_TX_RX;
    uart1.UARTx.Init.HwFlowCtl=UART_HWCONTROL_NONE;
    uart1.UARTx.Init.OverSampling=UART_OVERSAMPLING_16;
    uart1.UARTx.Init.OneBitSampling=UART_ONE_BIT_SAMPLE_DISABLE;
    uart1.UARTx.Init.ClockPrescaler=UART_PRESCALER_DIV1;
    uart1.UARTx.AdvancedInit.AdvFeatureInit=UART_ADVFEATURE_NO_INIT;
    HAL_UART_Init(&uart1.UARTx);

    
    __HAL_UART_ENABLE_IT(&uart1.UARTx,UART_IT_RXNE);
    RingBuffer_Init();
}
void RingBuffer_Init(void){
    uart1.TxCounter=0;
    uart1.TxInPrt=&uart1.TxLocation[0];
    uart1.TxOutPrt=&uart1.TxLocation[0];
    uart1.TxEndPrt=&uart1.TxLocation[9];
    uart1.TxInPrt->start=TxBuff;

    uart1.RxCounter=0;
    uart1.RxInPrt=&uart1.RxLocation[0];
    uart1.RxOutPrt=&uart1.RxLocation[0];
    uart1.RxEndPrt=&uart1.RxLocation[9];
    uart1.RxInPrt->start=RxBuff;

    __HAL_UART_ENABLE_IT(&uart1.UARTx,UART_IT_IDLE);
    HAL_UART_Receive_IT(&uart1.UARTx,&uart1.TxInPrt->star,RX_MAX+1);
}
void HAL_UART_MspInit(UART_HandleTypeDef *huart){
    RCC_PeriphCLKInitTypeDef Uart_RCC_PeriphCLKInit;
    GPIO_InitTypeDef Uart_GPIO_Init;

    Uart_RCC_PeriphCLKInit.PeriphClockSelection=RCC_PERIPHCLK_USART1;
    Uart_RCC_PeriphCLKInit.Usart16ClockSelection=RCC_USART16CLKSOURCE_D2PCLK2;
    HAL_RCCEx_PeriphCLKConfig(&Uart_RCC_PeriphCLKInit);
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    Uart_GPIO_Init.Pin= GPIO_PIN_9 | GPIO_PIN_10;
    Uart_GPIO_Init.Mode =GPIO_MODE_AF_PP;
    Uart_GPIO_Init.Pull=GPIO_NOPULL;
    Uart_GPIO_Init.Speed=GPIO_SPEED_FREQ_LOW;
    Uart_GPIO_Init.Alternate=GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA,&Uart_GPIO_Init);
    HAL_NVIC_SetPriority(USART1_IRQn,3,0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    uint16_t i;
    for (i = 0; i <RX_MAX; i++)
    {
       TxBuff[i]=RxBuff[i];
    }
    HAL_UART_Receive_IT(&uart1.UARTx,RxBuff,RX_MAX);
}
void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart){
    uart1.RxInPrt->end = &RxBuff[uart1.UARTx.RxXferCount-1];
    uart1.RxInPrt++;
}

void Uart_SendChar(uint8_t c){
    while (((USART1->ICR) & (1<<6))!=0);
    USART1->TDR=c;
}
