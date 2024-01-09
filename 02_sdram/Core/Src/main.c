#include "main.h"

#define BufferSize	254

void SDRAM_Test1(void);
uint8_t SDRAM_Test2(void);

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
	Led_Init(led_r);
	SDRAM_Init();
	SDRAM_Test1();
	

	while (1)
	{
		__GPIO_RESET_BIT(GPIOC,led_r);
		HAL_Delay(500);
		__GPIO_SET_BIT(GPIOC,led_r);
		HAL_Delay(500);
	}
}
void SDRAM_Test1(void){
	u8 WBuffer[BufferSize];
	u8 RBuffer[BufferSize];
	u32 Time_Start;
	u32 Time_End;
	u16 i;

	for (i = 0; i < BufferSize; i++)
	{
		WBuffer[i]=0x66;
	}

	printf("\r\n*****************************************************************************************************\r\n");

	Time_Start=HAL_GetTick();
	SDRAM_WriteBuffer(WBuffer,0,BufferSize);
	Time_End=HAL_GetTick();

	printf("写入耗时: %d ms\r\n",Time_End-Time_Start);

	Time_Start=HAL_GetTick();
	SDRAM_ReadBuffer(RBuffer,0,BufferSize);
	Time_End=HAL_GetTick();

	printf("读出耗时: %d ms\r\n",Time_End-Time_Start);

	for (i = 0; i < BufferSize; i++)
	{
		if(WBuffer[i]!=RBuffer[i]){
			printf("数据比较错误,第%d行\r\n",i);
			break;
		}
	}
	printf("耗时: %d ms\r\n",Time_End-Time_Start);
}

uint8_t SDRAM_Test2(void)
{
	uint32_t i = 0;		   // 计数变量
	uint16_t ReadData = 0; // 读取到的数据
	uint8_t ReadData_8b;

	uint32_t ExecutionTime_Begin; // 开始时间
	uint32_t ExecutionTime_End;	  // 结束时间
	uint32_t ExecutionTime;		  // 执行时间
	float ExecutionSpeed;		  // 执行速度

	printf("*****************************************************************************************************\r\n");
	printf("进行速度测试>>>\r\n");

	// 写入 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	ExecutionTime_Begin = HAL_GetTick(); // 获取 systick 当前时间，单位ms

	for (i = 0; i < SDRAM_SIZE / 2; i++)
	{
		*(__IO uint16_t *)(SDRAM_ADDR + 2 * i) = (uint16_t)i; // 写入数据
	}
	ExecutionTime_End = HAL_GetTick();										 // 获取 systick 当前时间，单位ms
	ExecutionTime = ExecutionTime_End - ExecutionTime_Begin;				 // 计算擦除时间，单位ms
	ExecutionSpeed = (float)SDRAM_SIZE / 1024 / 1024 / ExecutionTime * 1000; // 计算速度，单位 MB/S

	printf("以16位数据宽度写入数据，大小：%d MB，耗时: %d ms, 写入速度：%.2f MB/s\r\n", SDRAM_SIZE / 1024 / 1024, ExecutionTime, ExecutionSpeed);

	// 读取	>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	ExecutionTime_Begin = HAL_GetTick(); // 获取 systick 当前时间，单位ms

	for (i = 0; i < SDRAM_SIZE / 2; i++)
	{
		ReadData = *(__IO uint16_t *)(SDRAM_ADDR + 2 * i); // 从SDRAM读出数据
	}
	ExecutionTime_End = HAL_GetTick();										 // 获取 systick 当前时间，单位ms
	ExecutionTime = ExecutionTime_End - ExecutionTime_Begin;				 // 计算擦除时间，单位ms
	ExecutionSpeed = (float)SDRAM_SIZE / 1024 / 1024 / ExecutionTime * 1000; // 计算速度，单位 MB/S

	printf("读取数据完毕，大小：%d MB，耗时: %d ms, 读取速度：%.2f MB/s\r\n", SDRAM_SIZE / 1024 / 1024, ExecutionTime, ExecutionSpeed);

	// 数据校验 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	printf("*****************************************************************************************************\r\n");
	printf("进行数据校验>>>\r\n");

	for (i = 0; i < SDRAM_SIZE / 2; i++)
	{
		ReadData = *(__IO uint16_t *)(SDRAM_ADDR + 2 * i); // 从SDRAM读出数据
		if (ReadData != (uint16_t)i)					   // 检测数据，若不相等，跳出函数,返回检测失败结果。
		{
			printf("SDRAM测试失败！！\r\n");
			return ERROR; // 返回失败标志
		}
	}

	printf("16位数据宽度读写通过，以8位数据宽度写入数据\r\n");
	for (i = 0; i < 255; i++)
	{
		*(__IO uint8_t *)(SDRAM_ADDR + i) = (uint8_t)i;
	}
	printf("写入完毕，读取数据并比较...\r\n");
	for (i = 0; i < 255; i++)
	{
		ReadData_8b = *(__IO uint8_t *)(SDRAM_ADDR + i);
		if (ReadData_8b != (uint8_t)i) // 检测数据，若不相等，跳出函数,返回检测失败结果。
		{
			printf("8位数据宽度读写测试失败！！\r\n");
			printf("请检查NBL0和NBL1的连接\r\n");
			return ERROR; // 返回失败标志
		}
	}
	printf("8位数据宽度读写通过\r\n");
	printf("SDRAM读写测试通过，系统正常\r\n");
	return SUCCESS; // 返回成功标志
}
