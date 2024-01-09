#include "ltdc_driver.h"

/* Red Color Channels      Green Color Channels    Blue Color Channels     */
/* LCD_R0  - PG13          LCD_G0  - PE5           LCD_B0  - PG14          */
/* LCD_R1  - PA2           LCD_G1  - PE6           LCD_B1  - PG12          */
/* LCD_R2  - PH8           LCD_G2  - PH13          LCD_B2  - PD6           */
/* LCD_R3  - PH9           LCD_G3  - PH14          LCD_B3  - PA8           */
/* LCD_R4  - PH10          LCD_G4  - PH15          LCD_B4  - PI4           */
/* LCD_R5  - PH11          LCD_G5  - PI0           LCD_B5  - PI5           */
/* LCD_R6  - PH12          LCD_G6  - PI1           LCD_B6  - PI6           */
/* LCD_R7  - PG6           LCD_G7  - PI2           LCD_B7  - PI7           */

/* Control Signals         Touch Panel Signals     */
/* LCD_DE   - PF10         TP_INT - PF6            */
/* LCD_BIT  - PH6          TP_SCL - PF7            */
/* LCD_VSYNC- PI9          TP_MISO- PF8            */
/* LCD_HSYNC- PI10         TP_MOSI- PF9            */
/* LCD_PCLK - PG7   */

LTDC_HandleTypeDef hltdc;

static void LTDC_Layer1_Config(void);

void LTDC_Init(void)
{
    SDRAM_Init();
    Clear_SDRAM(1024,600,0);
    hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    hltdc.Init.HorizontalSync = 19;
    hltdc.Init.VerticalSync = 2;
    hltdc.Init.AccumulatedHBP = 159;
    hltdc.Init.AccumulatedVBP = 22;
    hltdc.Init.AccumulatedActiveW = 1183;
    hltdc.Init.AccumulatedActiveH = 622;
    hltdc.Init.TotalWidth = 1343;
    hltdc.Init.TotalHeigh = 634;
    hltdc.Init.Backcolor.Blue = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Red = 0xFF;
    HAL_LTDC_Init(&hltdc);

    LTDC_Layer1_Config();
    LTCD_BIT(1);
}

void LTDC_Layer1_Config(void){

    LTDC_LayerCfgTypeDef Ltdc_layer1_init;

    Ltdc_layer1_init.WindowX0=0;
    Ltdc_layer1_init.WindowX1=1024;
    Ltdc_layer1_init.WindowY0=0;
    Ltdc_layer1_init.WindowY1=600;
    Ltdc_layer1_init.PixelFormat=LTDC_PIXEL_FORMAT_RGB565;
    Ltdc_layer1_init.Alpha=255;
    Ltdc_layer1_init.Alpha0=0;
    Ltdc_layer1_init.BlendingFactor1=LTDC_BLENDING_FACTOR1_CA;
    Ltdc_layer1_init.BlendingFactor2=LTDC_BLENDING_FACTOR2_CA;
    Ltdc_layer1_init.FBStartAdress=0xC0000000;
    Ltdc_layer1_init.ImageWidth=1024;
    Ltdc_layer1_init.ImageHeight=600;
    Ltdc_layer1_init.Backcolor.Blue=0;
    Ltdc_layer1_init.Backcolor.Green=0;
    Ltdc_layer1_init.Backcolor.Red=0;

    HAL_LTDC_ConfigLayer(&hltdc,&Ltdc_layer1_init,LTDC_LAYER_1);
}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef *hltdc)
{
    RCC_PeriphCLKInitTypeDef LtdcRccStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    LtdcRccStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    LtdcRccStruct.PLL3.PLL3M = 5;
    LtdcRccStruct.PLL3.PLL3N = 100;
    LtdcRccStruct.PLL3.PLL3P = 2;
    LtdcRccStruct.PLL3.PLL3Q = 2;
    LtdcRccStruct.PLL3.PLL3R = 10;
    LtdcRccStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_2;
    LtdcRccStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
    LtdcRccStruct.PLL3.PLL3FRACN = 0;
    HAL_RCCEx_PeriphCLKConfig(&LtdcRccStruct);

    __HAL_RCC_LTDC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    /*BT*/
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    /*B3*/
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF13_LTDC;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    /*R1*/
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    /*B2*/
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    /*G0,G1*/
    GPIO_InitStruct.Pin = 0x0060;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    /*DE*/
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
    /*R7,PCLK,B1,R0,B0*/
    GPIO_InitStruct.Pin = 0x70C0;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
    /*R2,R3,R4,R5,R6,G2,G3,G4*/
    GPIO_InitStruct.Pin = 0xFF00;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
    /*G5,G6,G7,B4,B5,B6,B7,VS,HS*/
    GPIO_InitStruct.Pin = 0x06F7;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
}