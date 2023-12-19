#include "led.h"

void Led_Init(enum Led_id id)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructe;
	GPIO_InitStructe.Pin = id;
	GPIO_InitStructe.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructe.Pull = GPIO_PULLUP;
	GPIO_InitStructe.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructe);
	GPIOC->BSRR =id;
}
void Led_Set(enum Led_id id, bool value)
{
	uint8_t led;
	switch (id)
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
