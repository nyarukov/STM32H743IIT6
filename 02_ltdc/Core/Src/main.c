#include "main.h"

#define LED_BIT(n) ((n) ? __GPIO_SET_BIT(GPIOC, led_b) : __GPIO_RESET_BIT(GPIOC, led_b))

void LCD_Test(void);
void LCD_Test1(void);

extern const uint16_t _acmickey[] ;
extern const uint16_t _ac1[];

int main(void)
{
	MPU_Config();
	SCB_EnableICache(); // 使能ICache
	SCB_EnableDCache(); // 使能DCache
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	Uart_Init(115200);
	PLL_CLK_Ptintf();
	Led_Init(led_b);
	LTDC_Init();

	//LCD_DMA2D_Image(0,0,240, 240,(u32*)_acmickey);
	LCD_DMA2D_Image(0,0,240, 135,(u32*)_ac1);
	while (1)
	{

		LED_BIT(0);
		HAL_Delay(1000);
		LED_BIT(1);
		HAL_Delay(1000);
	}
}

void LCD_Test(void)
{

	printf("DMA2D_Start\r\n");
	u32 TimeStart, TimeEnd;
	TimeStart = HAL_GetTick();
	LCD_DMA2D_Fill(0, 0, 1024, 600, RGB565(255, 0, 0));

	LCD_DMA2D_Fill(0, 0, 1024, 600, RGB565(0, 255, 0));

	LCD_DMA2D_Fill(0, 0, 1024, 600, RGB565(0, 0, 255));

	LCD_DMA2D_Fill(0, 0, 1024, 600, RGB565(0, 255, 255));

	LCD_DMA2D_Fill(0, 0, 1024, 600, RGB565(255, 255, 0));

	LCD_DMA2D_Fill(0, 0, 1024, 600, RGB565(0, 255, 255));

	LCD_DMA2D_Fill(0, 0, 1024, 600, RGB565(255, 0, 255));

	LCD_DMA2D_Fill(0, 0, 1024, 600, RGB565(255, 255, 255));

	LCD_DMA2D_Fill(0, 0, 1024, 600, RGB565(0, 0, 0));

	TimeEnd = HAL_GetTick();
	printf("DMA2D_Time=%d\r\n", TimeEnd - TimeStart);
}
void LCD_Test1(void)
{
	printf("LCD_Fill_Start\r\n");
	u32 TimeStart, TimeEnd;
	TimeStart = HAL_GetTick();
	LCD_Fill(0, 0, 1024, 600, RGB565(255, 0, 0));

	LCD_Fill(0, 0, 1024, 600, RGB565(0, 255, 0));

	LCD_Fill(0, 0, 1024, 600, RGB565(0, 0, 255));

	LCD_Fill(0, 0, 1024, 600, RGB565(0, 255, 255));

	LCD_Fill(0, 0, 1024, 600, RGB565(255, 255, 0));

	LCD_Fill(0, 0, 1024, 600, RGB565(0, 255, 255));

	LCD_Fill(0, 0, 1024, 600, RGB565(255, 0, 255));

	LCD_Fill(0, 0, 1024, 600, RGB565(255, 255, 255));

	LCD_Fill(0, 0, 1024, 600, RGB565(0, 0, 0));

	TimeEnd = HAL_GetTick();
	printf("LCD_Fill_Time=%d\r\n", TimeEnd - TimeStart);
	printf("%d\r\n", 50000000 / ((1024 + 20 + 140 + 160) * (600 + 3 + 20 + 12)));
}