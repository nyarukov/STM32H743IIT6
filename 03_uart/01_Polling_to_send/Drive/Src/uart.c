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
void Uart_SendChar(uint8_t ch){
    while(((uart1.Instance->ISR)&(1<<7))==RESET);
    uart1.Instance->TDR=ch;
}
void Uart_SendString(uint8_t *str){
    while(str!='\0'){
        Uart_SendChar(*str);
        str++;
    }
}
void Uart_SendArray(uint8_t *arr,uint8_t length){
    uint16_t i;
    for (i = 0; i < length; i++)
    {
        Uart_SendChar(arr[i]);
    }
    
}
static uint64_t Pow(uint8_t x,uint64_t y){
    uint64_t i=1;
    while (y--)
    {
        i*= x;
    }
    return i;
}
void Uart_num(uint64_t num){
    uint8_t i,length=1;
    uint64_t temp =num;
    while (temp/=10)
    {
        length++;
    }
    temp =num;
    for (i = 0; i < length; i++)
    {
        Uart_SendChar(num/Pow(10,length-1-i) % 10 + '0');
    }
    Uart_SendChar('\n');
}
