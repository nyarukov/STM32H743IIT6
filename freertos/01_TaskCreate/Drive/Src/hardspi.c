#include "hardspi.h"
/*
W25Q128
SPI_NSS     --- PA4
SPI_CLK     --- PA5
SPI_MISO    --- PA6
SPI_MOSI    --- PA7
*/
SPI_HandleTypeDef spi;

void SPI_Init(void)
{
    spi.Instance = SPI1;
    spi.Init.Mode = SPI_MODE_MASTER;
    spi.Init.Direction = SPI_DIRECTION_2LINES;
    spi.Init.DataSize = SPI_DATASIZE_8BIT;
    spi.Init.CLKPolarity = SPI_POLARITY_HIGH;
    spi.Init.CLKPhase = SPI_PHASE_2EDGE;
    spi.Init.NSS = SPI_NSS_SOFT;
    spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    spi.Init.TIMode = SPI_TIMODE_DISABLE;
    spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi.Init.CRCPolynomial = 7;
    spi.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
    spi.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
    spi.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
    spi.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    spi.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    spi.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
    spi.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
    spi.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
    spi.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
    spi.Init.IOSwap = SPI_IO_SWAP_DISABLE;
    HAL_SPI_Init(&spi);
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    RCC_PeriphCLKInitTypeDef SpiRccStruct;
    GPIO_InitTypeDef SpiStruct;

    SpiRccStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI123;
    SpiRccStruct.PLL2.PLL2M = 5;
    SpiRccStruct.PLL2.PLL2N = 192;
    SpiRccStruct.PLL2.PLL2P = 6;
    SpiRccStruct.PLL2.PLL2Q = 2;
    SpiRccStruct.PLL2.PLL2N = 2;
    SpiRccStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_2;
    SpiRccStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
    SpiRccStruct.PLL2.PLL2FRACN = 0;
    SpiRccStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL2;
    HAL_RCCEx_PeriphCLKConfig(&SpiRccStruct);

    __HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    SpiStruct.Pin = GPIO_PIN_4;
    SpiStruct.Mode = GPIO_MODE_OUTPUT_PP;
    SpiStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &SpiStruct);
    __GPIO_SET_BIT(GPIOA,GPIO_PIN_4);

    SpiStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
    SpiStruct.Mode = GPIO_MODE_AF_PP;
    SpiStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    SpiStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &SpiStruct);
    
    SpiStruct.Pin = GPIO_PIN_6;
    SpiStruct.Mode = GPIO_MODE_INPUT;
    SpiStruct.Pull = GPIO_NOPULL;
    SpiStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &SpiStruct);
}
void SPI_SendByte(uint8_t txdata)
{
    HAL_SPI_Transmit(&spi, &txdata, 1, 5000);
}
uint8_t SPI_ReveiceByte(void)
{
    uint8_t rxdata;
    HAL_SPI_Receive(&spi, &rxdata, 1, 50000);
    return rxdata;
}
uint8_t SPI_Send_Reveice_Byte(uint8_t txdata)
{
    uint8_t rxdata;
    HAL_SPI_TransmitReceive(&spi, &txdata, &rxdata, 1, 50000);
    return rxdata;
}
