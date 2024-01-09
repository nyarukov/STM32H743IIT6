#ifndef __SDRAM_H
#define __SDRAM_H

#include "stm32h7xx_hal.h"
#include "bit_control.h"
#include "uart.h"

#define SDRAM_ADDR                  ((u32)(0XC0000000))     //SDRAM开始地址
#define SDRAM_SIZE		            (32 * 1024 * 1024)
#define SDRAM_TIMEOUT               ((uint32_t)0x1000)
#define FMC_COMMAND_TARGET_BANK     FMC_SDRAM_CMD_TARGET_BANK1	 

//SDRAM配置参数
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)


void SDRAM_Init(void);
void SDRAM_WriteBuffer(u8 *pBuffer,u32 WriteAddr,u32 n);
void SDRAM_ReadBuffer(u8 *pBuffer,u32 ReadAddr,u32 n);
#endif // !__SDRAM_H