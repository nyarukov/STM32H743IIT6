#ifndef __W25Q128_H
#define __W25Q128_H

#include "stm32h7xx_hal.h"
#include "softspi.h"
#include "bit_control.h"

#define W25Q80_DEVICE_ID   0x4014
#define W25Q16_DEVICE_ID   0x4015
#define W25Q32_DEVICE_ID   0x4016
#define W25Q64_DEVICE_ID   0x4017
#define W25Q128_DEVICE_ID  0x4018

#define CMD_WRITE_ENABLE                    0x06     // 写使能命令
#define CMD_VOLATILE_SR_WRITE_ENABLE        0x50     // 可挥发状态寄存器写使能命令
#define CMD_WRITE_DISABLE                   0x04     // 写禁止命令
#define CMD_MANUFACTURER_DEVICE_ID          0x90     // 制造商/设备 ID 命令
#define CMD_JEDEC_ID                        0x9F     // JEDEC ID 命令
#define CMD_READ_UNIQUE_ID                  0x4B     // 读取唯一 ID 命令
#define CMD_READ_DATA                       0x03     // 读取数据命令
#define CMD_FAST_READ                       0x0B     // 快速读取命令
#define CMD_PAGE_PROGRAM                    0x02     // 页面编程命令
#define CMD_SECTOR_ERASE_4KB                0x20     // 扇区擦除 (4KB) 命令
#define CMD_BLOCK_ERASE_32KB                0x52     // 块擦除 (32KB) 命令
#define CMD_BLOCK_ERASE_64KB                0xD8     // 块擦除 (64KB) 命令
#define CMD_CHIP_ERASE                      0xC7     // 芯片擦除命令
#define CMD_READ_STATUS_REGISTER_1          0x05     // 读取状态寄存器-1 命令
#define CMD_WRITE_STATUS_REGISTER_1         0x01     // 写入状态寄存器-1 命令
#define CMD_READ_STATUS_REGISTER_2          0x35     // 读取状态寄存器-2 命令
#define CMD_WRITE_STATUS_REGISTER_2         0x31     // 写入状态寄存器-2 命令
#define CMD_READ_STATUS_REGISTER_3          0x15     // 读取状态寄存器-3 命令
#define CMD_WRITE_STATUS_REGISTER_3         0x11     // 写入状态寄存器-3 命令
#define CMD_READ_SFDP_REGISTER              0x5A     // 读取 SFDP 寄存器命令
#define CMD_ERASE_SECURITY_REGISTER         0x44     // 擦除安全寄存器命令
#define CMD_PROGRAM_SECURITY_REGISTER       0x42     // 编程安全寄存器命令
#define CMD_READ_SECURITY_REGISTER          0x48     // 读取安全寄存器命令
#define CMD_GLOBAL_BLOCK_LOCK               0x7E     // 全局块锁定命令
#define CMD_GLOBAL_BLOCK_UNLOCK             0x98     // 全局块解锁命令
#define CMD_READ_BLOCK_LOCK                 0x3D     // 读取块锁定命令
#define CMD_INDIVIDUAL_BLOCK_LOCK           0x36     // 个别块锁定命令
#define CMD_INDIVIDUAL_BLOCK_UNLOCK         0x39     // 个别块解锁命令
#define CMD_ERASE_PROGRAM_SUSPEND           0x75     // 擦除/编程挂起命令
#define CMD_ERASE_PROGRAM_RESUME            0x7A     // 擦除/编程恢复命令
#define CMD_POWER_DOWN                      0xB9     // 关闭电源命令
#define CMD_RELEASE_POWER_DOWN_ID           0xAB     // 释放电源下降 / 读取 ID 命令
#define CMD_ENABLE_RESET                    0x66     // 启用复位命令
#define CMD_RESET_DEVICE                    0x99     // 复位设备命令
#define CMD_DUMMY_BYTE                      0xFF     // 交换数据
// 定义命令参数
#define ADDRESS_23_16(addr)              (((addr) >> 16) & 0xFF)
#define ADDRESS_15_8(addr)               (((addr) >> 8) & 0xFF)
#define ADDRESS_7_0(addr)                ((addr) & 0xFF)


void W25Q128_Init(void);
void W25Q128_ReadID(uint8_t *MID, uint16_t *DID);
void W25Q128_RESET_DEVICE(void);
void W25Q128_Write_ENABLE(void);
void W25Q128_Write_DISABLE(void);
void W25Q128_Start(void);
void W25Q128_SectorErase(uint32_t Addr);
void W25Q128_ChipErase(void);
void W25Q128_Page(uint32_t Addr,uint8_t *Txdata,uint16_t length);
void W25Q128_ReadData(uint32_t Addr,uint8_t *Rxdata,uint16_t length);
#endif
