#include "exti.h"

static GPIO_Config gpio_config[GPIO_MAX]={
    {GPIOI,GPIO_PIN_0,GPIO_MODE_IT_RISING,GPIO_PULLUP,GPIO_SPEED_HIGH,EXTI0_IRQn},
    {GPIOI,GPIO_PIN_1,GPIO_MODE_IT_RISING,GPIO_PULLUP,GPIO_SPEED_HIGH,EXTI1_IRQn},
    {GPIOI,GPIO_PIN_2,GPIO_MODE_IT_RISING,GPIO_PULLUP,GPIO_SPEED_HIGH,EXTI2_IRQn}
};

void EXTI_Config(void){
    GPIO_InitTypeDef GPIO_InitStructe;
    ECH11_RCC_GPIOx_CLK();
    uint16_t i;
    for (i = 0; i < GPIO_MAX; i++)
    {
        GPIO_InitStructe.Pin=gpio_config[i].pin;
        GPIO_InitStructe.Mode=gpio_config[i].mode;
        GPIO_InitStructe.Pull=gpio_config[i].pull;
        GPIO_InitStructe.Speed=gpio_config[i].speed;
        HAL_GPIO_Init(gpio_config[i].gpiox,&GPIO_InitStructe);
        HAL_NVIC_SetPriority(gpio_config[i].irq,4,0);
        HAL_NVIC_EnableIRQ(gpio_config[i].irq);
    }
}

