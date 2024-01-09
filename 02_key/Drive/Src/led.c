#include "led.h"

void Led_Init(uint16_t GPIO_Pinx)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructe;
	GPIO_InitStructe.Pin = GPIO_Pinx;
	GPIO_InitStructe.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructe.Pull = GPIO_PULLUP;
	GPIO_InitStructe.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructe);
	GPIOC->BSRR =GPIO_Pinx;
}
void Led_Set(uint16_t GPIO_Pinx, bool value)
{
	uint8_t led;
	switch (GPIO_Pinx)
	{
	case led_r:
		led = led_r;
		break;
	case led_g:
		led = led_g;
		break;
	case led_b:
		led = led_b;
		break;
	}
	(value==true)? (GPIOC->BSRR =led<<16UL) : (GPIOC->BSRR =led);
}
