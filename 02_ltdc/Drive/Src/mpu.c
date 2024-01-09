#include "mpu.h"

static void MPU_Set_Protection(u32 Address, u8 Size, u8 Number, u8 APer, u8 IsShar, u8 IsCach, u8 IsBuffer);

void MPU_Config(void)
{
  // 保护SDRAM区域,共32M字节
  MPU_Set_Protection(SDRAM_ADDR,                  // 基地址
                     MPU_REGION_SIZE_32MB,        // 长度
                     MPU_REGION_NUMBER2,          // NUMER2
                     MPU_REGION_FULL_ACCESS,      // 全访问
                     MPU_ACCESS_NOT_SHAREABLE,    // 禁止共享
                     MPU_ACCESS_CACHEABLE,        // 允许cache
                     MPU_ACCESS_NOT_BUFFERABLE);      // 允许缓冲
}

/**
 * @brief 配置MPU保护单元
 *
 * @param Address 设置MPU区域起始地址
 * @param Size 指定MPU区域大小
 * @param Number 指定MPU区域编号
 * @param APer 设置MPU区域访问权限
 * @param IsShar 设置MPU区域共享
 * @param IsCach 设置MPU区域缓存
 * @param IsBuffer 设置MPU区域缓冲
 */
static void MPU_Set_Protection(u32 Address, u8 Size, u8 Number, u8 APer, u8 IsShar, u8 IsCach, u8 IsBuffer)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  HAL_MPU_Disable();

  MPU_InitStruct.Enable = MPU_REGION_ENABLE;                  /* 启用MPU区域 */
  MPU_InitStruct.Number = Number;                             /* 指定MPU区域编号 */
  MPU_InitStruct.BaseAddress = Address;                       /* 设置MPU区域起始地址 */
  MPU_InitStruct.Size = Size;                                 /* 指定MPU区域大小 */
  MPU_InitStruct.SubRegionDisable = 0x00;                     /* 设置MPU区域的子区域 */
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;               /* 指定MPU区域的TEX字段级别为0 */
  MPU_InitStruct.AccessPermission = APer;                     /* 设置MPU区域访问权限 */
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE; /* 设置MPU区域的指令访问 */
  MPU_InitStruct.IsShareable = IsShar;                        /* 设置MPU区域共享 */
  MPU_InitStruct.IsCacheable = IsCach;                        /* 设置MPU区域缓存 */
  MPU_InitStruct.IsBufferable = IsBuffer;                     /* 设置MPU区域缓冲 */

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
