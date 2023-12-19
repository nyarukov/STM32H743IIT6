#include "uart.h"

UART_HandleTypeDef uart1;

void Uart_Init(uint32_t baudrate){
    uart1.Instance=USART1;
    uart1.Init.BaudRate=baudrate;
    uart1.Init.WordLength=UART_WORDLENGTH_8B;
    uart1.Init.StopBits=UART_STOPBITS_1;
    uart1.Init.Parity=UART_PARITY_NONE;
    uart1.Init.Mode=UART_MODE_TX_RX;
    uart1.Init.HwFlowCtl=UART_HWCONTROL_NONE;
    uart1.Init.OverSampling=UART_OVERSAMPLING_16;
    uart1.Init.OneBitSampling=UART_ONE_BIT_SAMPLE_DISABLE;
    uart1.Init.ClockPrescaler=UART_PRESCALER_DIV1;
    uart1.AdvancedInit.AdvFeatureInit=UART_ADVFEATURE_NO_INIT;
    HAL_UART_Init(&uart1);
}

void Uart_SendChar(uint8_t c){
    while (((USART1->ICR) & (1<<6))!=0);
    USART1->TDR=c;
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

}