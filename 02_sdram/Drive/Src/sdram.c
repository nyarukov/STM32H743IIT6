#include "sdram.h"

/* Address Bus  Data Bus        Control and Clock Signals   Bank Select Signals */
/* A0  - PF0    D0  - PD14      SDRAM_RAS  - PF11           SDRAM_BS0   - PG4 */
/* A1  - PF1    D1  - PD15      SDRAM_CAS  - PG15           SDRAM_BS1   - PG5 */
/* A2  - PF2    D2  - PD0                                   SDRAM_CLK   - PG8 */
/* A3  - PF3    D3  - PD1                               pc3    SDRAM_CKE   - PH2 */
/* A4  - PF4    D4  - PE7                               pc2    SDRAM_CS    - PH3 */
/* A5  - PF5    D5  - PE8                                   SDRAM_LDQM  - PE0 */
/* A6  - PF12   D6  - PE9                                   SDRAM_UDQM  - PE1 */
/* A7  - PF13   D7  - PE10                              pc0    SDRAM_WE    - PH5 */
/* A8  - PF14   D8  - PE11 */
/* A9  - PF15   D9  - PE12 */
/* A10 - PG0    D10 - PE13 */
/* A11 - PG1    D11 - PE14 */
/* A12 - PG2    D12 - PE15 */
/*              D13 - PD8 */
/*              D14 - PD9 */
/*              D15 - PD10 */

SDRAM_HandleTypeDef SDRAM_Handler;
FMC_SDRAM_CommandTypeDef SDRAM_Command;

static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);

void SDRAM_Init(void)
{
    FMC_SDRAM_TimingTypeDef SDRAM_Timing;

    SDRAM_Handler.Instance                  = FMC_SDRAM_DEVICE;                     // SDRAM在BANK5,6
    SDRAM_Handler.Init.SDBank               = FMC_SDRAM_BANK1;                      // SDRAM接在BANK5上
    SDRAM_Handler.Init.ColumnBitsNumber     = FMC_SDRAM_COLUMN_BITS_NUM_9;          // 列数量
    SDRAM_Handler.Init.RowBitsNumber        = FMC_SDRAM_ROW_BITS_NUM_13;            // 行数量
    SDRAM_Handler.Init.MemoryDataWidth      = FMC_SDRAM_MEM_BUS_WIDTH_16;           // 数据宽度为16位
    SDRAM_Handler.Init.InternalBankNumber   = FMC_SDRAM_INTERN_BANKS_NUM_4;         // 一共4个BANK
    SDRAM_Handler.Init.CASLatency           = FMC_SDRAM_CAS_LATENCY_3;              // CAS为2
    SDRAM_Handler.Init.WriteProtection      = FMC_SDRAM_WRITE_PROTECTION_DISABLE;   // 失能写保护
    SDRAM_Handler.Init.SDClockPeriod        = FMC_SDRAM_CLOCK_PERIOD_2;             // SDRAM时钟为HCLK/2=200M/2=100M=10ns
    SDRAM_Handler.Init.ReadBurst            = FMC_SDRAM_RBURST_ENABLE;              // 使能突发
    SDRAM_Handler.Init.ReadPipeDelay        = FMC_SDRAM_RPIPE_DELAY_1;              // 读通道延时

    SDRAM_Timing.LoadToActiveDelay      = 2;    // 加载模式寄存器到激活时间的延迟为2个时钟周期
    SDRAM_Timing.ExitSelfRefreshDelay   = 7;    // 退出自刷新延迟为8个时钟周期
    SDRAM_Timing.SelfRefreshTime        = 4;    // 自刷新时间为6个时钟周期
    SDRAM_Timing.RowCycleDelay          = 7;    // 行循环延迟为7个时钟周期
    SDRAM_Timing.WriteRecoveryTime      = 2;    // 恢复延迟为5个时钟周期
    SDRAM_Timing.RPDelay                = 2;    // 行预充电延迟为2个时钟周期
    SDRAM_Timing.RCDDelay               = 2;    // 行到列延迟为2个时钟周期
    
    HAL_SDRAM_Init(&SDRAM_Handler, &SDRAM_Timing);

    SDRAM_Initialization_Sequence(&SDRAM_Handler,&SDRAM_Command);
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *hsdram)
{
    RCC_PeriphCLKInitTypeDef FmcRccStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    FmcRccStruct.PeriphClockSelection = RCC_PERIPHCLK_FMC;
    FmcRccStruct.FmcClockSelection = RCC_FMCCLKSOURCE_D1HCLK;

    HAL_RCCEx_PeriphCLKConfig(&FmcRccStruct);

    __HAL_RCC_FMC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    // GPIO_InitStruct.Pin = 0xC703;
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    // GPIO_InitStruct.Pin = 0XFF83;
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    // GPIO_InitStruct.Pin = 0XF83F;
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // GPIO_InitStruct.Pin = 0X8137;
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    // GPIO_InitStruct.Pin = 0X0026;
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

}
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command)
{
    __IO uint32_t tmpmrd = 0;

	Command->CommandMode 				= FMC_SDRAM_CMD_CLK_ENABLE;	
	Command->CommandTarget 				= FMC_COMMAND_TARGET_BANK; 	
	Command->AutoRefreshNumber 		    = 1;
	Command->ModeRegisterDefinition 	= 0;
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);	

	HAL_Delay(1);		
    
	Command->CommandMode 				= FMC_SDRAM_CMD_PALL;		
	Command->CommandTarget 				= FMC_COMMAND_TARGET_BANK;	
	Command->AutoRefreshNumber 		    = 1;
	Command->ModeRegisterDefinition 	= 0;
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT); 

	Command->CommandMode 				= FMC_SDRAM_CMD_AUTOREFRESH_MODE;	
	Command->CommandTarget 				= FMC_COMMAND_TARGET_BANK;          
	Command->AutoRefreshNumber			= 8;                               
	Command->ModeRegisterDefinition 	= 0;
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);	


	tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2 |
            SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL     |
            SDRAM_MODEREG_CAS_LATENCY_3             |
            SDRAM_MODEREG_OPERATING_MODE_STANDARD   |
            SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    Command->CommandMode				= FMC_SDRAM_CMD_LOAD_MODE;	
	Command->CommandTarget 				= FMC_COMMAND_TARGET_BANK;	
	Command->AutoRefreshNumber 		    = 1;
	Command->ModeRegisterDefinition 	= tmpmrd;

	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);	
	
	HAL_SDRAM_ProgramRefreshRate(hsdram, 918);  
}

/**
 * @brief 在指定地址(WriteAddr+Bank5_SDRAM_ADDR)开始,连续写入n个字节.
 *
 * @param pBuffer 字节指针
 * @param WriteAddr 要写入的地址
 * @param n 要写入的字节数
 */
void SDRAM_WriteBuffer(u8 *pBuffer, u32 WriteAddr, u32 n)
{
    for (; n != 0; n--)
    {
        *(__IO u8 *)(SDRAM_ADDR + WriteAddr) = *pBuffer;
        WriteAddr++;
        pBuffer++;
    }
}

/**
 * @brief 在指定地址((WriteAddr+Bank5_SDRAM_ADDR))开始,连续读出n个字节.
 *
 * @param pBuffer 字节指针
 * @param ReadAddr 要读出的起始地址
 * @param n 要写入的字节数
 */
void SDRAM_ReadBuffer(u8 *pBuffer, u32 ReadAddr, u32 n)
{
    for (; n != 0; n--)
    {

        *pBuffer++ = *(__IO u8 *)(SDRAM_ADDR + ReadAddr);
        ReadAddr++;
    }
}
