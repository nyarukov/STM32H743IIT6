#include "rcc.h"

void RCC_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStructe = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStructe = {0};
	HAL_StatusTypeDef ret = HAL_OK;

	MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)){}

	RCC_OscInitStructe.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStructe.HSEState = RCC_HSE_ON;
	RCC_OscInitStructe.HSIState = RCC_HSE_OFF;
	RCC_OscInitStructe.CSIState = RCC_CSI_OFF;
	RCC_OscInitStructe.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStructe.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStructe.PLL.PLLM = 5;
	RCC_OscInitStructe.PLL.PLLN = 160;
	RCC_OscInitStructe.PLL.PLLP = 2;
	RCC_OscInitStructe.PLL.PLLQ = 2;
	RCC_OscInitStructe.PLL.PLLR = 4;
	RCC_OscInitStructe.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
	RCC_OscInitStructe.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
	ret = HAL_RCC_OscConfig(&RCC_OscInitStructe);
	if (ret != HAL_OK)
	{
		while (1)
		{
			;
		}
	}

	RCC_ClkInitStructe.ClockType = (RCC_CLOCKTYPE_SYSCLK | \
									RCC_CLOCKTYPE_D1PCLK1 | \
									RCC_CLOCKTYPE_HCLK | \
									RCC_CLOCKTYPE_PCLK1 | \
									RCC_CLOCKTYPE_PCLK2 | \
									RCC_CLOCKTYPE_D3PCLK1);				
	RCC_ClkInitStructe.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStructe.SYSCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStructe.AHBCLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStructe.APB1CLKDivider = RCC_APB1_DIV2;
	RCC_ClkInitStructe.APB2CLKDivider = RCC_APB2_DIV2;
	RCC_ClkInitStructe.APB3CLKDivider = RCC_APB3_DIV2;
	RCC_ClkInitStructe.APB4CLKDivider = RCC_APB4_DIV2;
	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStructe, FLASH_LATENCY_4);
	if (ret != HAL_OK)
	{
		while (1)
		{
			;
		}
	}
}
