#include "main.h"

#define BufferSize	254

void SDRAM_Test1(void);
uint8_t SDRAM_Test2(void);

int main(void)
{
	MPU_Config();
	SCB_EnableICache(); // ʹ��ICache
	SCB_EnableDCache(); // ʹ��DCache
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

	printf("д���ʱ: %d ms\r\n",Time_End-Time_Start);

	Time_Start=HAL_GetTick();
	SDRAM_ReadBuffer(RBuffer,0,BufferSize);
	Time_End=HAL_GetTick();

	printf("������ʱ: %d ms\r\n",Time_End-Time_Start);

	for (i = 0; i < BufferSize; i++)
	{
		if(WBuffer[i]!=RBuffer[i]){
			printf("���ݱȽϴ���,��%d��\r\n",i);
			break;
		}
	}
	printf("��ʱ: %d ms\r\n",Time_End-Time_Start);
}

uint8_t SDRAM_Test2(void)
{
	uint32_t i = 0;		   // ��������
	uint16_t ReadData = 0; // ��ȡ��������
	uint8_t ReadData_8b;

	uint32_t ExecutionTime_Begin; // ��ʼʱ��
	uint32_t ExecutionTime_End;	  // ����ʱ��
	uint32_t ExecutionTime;		  // ִ��ʱ��
	float ExecutionSpeed;		  // ִ���ٶ�

	printf("*****************************************************************************************************\r\n");
	printf("�����ٶȲ���>>>\r\n");

	// д�� >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	ExecutionTime_Begin = HAL_GetTick(); // ��ȡ systick ��ǰʱ�䣬��λms

	for (i = 0; i < SDRAM_SIZE / 2; i++)
	{
		*(__IO uint16_t *)(SDRAM_ADDR + 2 * i) = (uint16_t)i; // д������
	}
	ExecutionTime_End = HAL_GetTick();										 // ��ȡ systick ��ǰʱ�䣬��λms
	ExecutionTime = ExecutionTime_End - ExecutionTime_Begin;				 // �������ʱ�䣬��λms
	ExecutionSpeed = (float)SDRAM_SIZE / 1024 / 1024 / ExecutionTime * 1000; // �����ٶȣ���λ MB/S

	printf("��16λ���ݿ��д�����ݣ���С��%d MB����ʱ: %d ms, д���ٶȣ�%.2f MB/s\r\n", SDRAM_SIZE / 1024 / 1024, ExecutionTime, ExecutionSpeed);

	// ��ȡ	>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	ExecutionTime_Begin = HAL_GetTick(); // ��ȡ systick ��ǰʱ�䣬��λms

	for (i = 0; i < SDRAM_SIZE / 2; i++)
	{
		ReadData = *(__IO uint16_t *)(SDRAM_ADDR + 2 * i); // ��SDRAM��������
	}
	ExecutionTime_End = HAL_GetTick();										 // ��ȡ systick ��ǰʱ�䣬��λms
	ExecutionTime = ExecutionTime_End - ExecutionTime_Begin;				 // �������ʱ�䣬��λms
	ExecutionSpeed = (float)SDRAM_SIZE / 1024 / 1024 / ExecutionTime * 1000; // �����ٶȣ���λ MB/S

	printf("��ȡ������ϣ���С��%d MB����ʱ: %d ms, ��ȡ�ٶȣ�%.2f MB/s\r\n", SDRAM_SIZE / 1024 / 1024, ExecutionTime, ExecutionSpeed);

	// ����У�� >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	printf("*****************************************************************************************************\r\n");
	printf("��������У��>>>\r\n");

	for (i = 0; i < SDRAM_SIZE / 2; i++)
	{
		ReadData = *(__IO uint16_t *)(SDRAM_ADDR + 2 * i); // ��SDRAM��������
		if (ReadData != (uint16_t)i)					   // ������ݣ�������ȣ���������,���ؼ��ʧ�ܽ����
		{
			printf("SDRAM����ʧ�ܣ���\r\n");
			return ERROR; // ����ʧ�ܱ�־
		}
	}

	printf("16λ���ݿ�ȶ�дͨ������8λ���ݿ��д������\r\n");
	for (i = 0; i < 255; i++)
	{
		*(__IO uint8_t *)(SDRAM_ADDR + i) = (uint8_t)i;
	}
	printf("д����ϣ���ȡ���ݲ��Ƚ�...\r\n");
	for (i = 0; i < 255; i++)
	{
		ReadData_8b = *(__IO uint8_t *)(SDRAM_ADDR + i);
		if (ReadData_8b != (uint8_t)i) // ������ݣ�������ȣ���������,���ؼ��ʧ�ܽ����
		{
			printf("8λ���ݿ�ȶ�д����ʧ�ܣ���\r\n");
			printf("����NBL0��NBL1������\r\n");
			return ERROR; // ����ʧ�ܱ�־
		}
	}
	printf("8λ���ݿ�ȶ�дͨ��\r\n");
	printf("SDRAM��д����ͨ����ϵͳ����\r\n");
	return SUCCESS; // ���سɹ���־
}
