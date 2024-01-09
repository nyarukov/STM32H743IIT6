#ifndef __SPI_H
#define __SPI_H

#include "stm32h7xx_hal.h"
#include "bit_control.h"

extern SPI_HandleTypeDef spi;

void SPI_Init(void);
void SPI_SendByte(uint8_t txdata);
uint8_t SPI_ReveiceByte(void);
uint8_t SPI_Send_Reveice_Byte(uint8_t txdata);

#endif // !__SPI_H