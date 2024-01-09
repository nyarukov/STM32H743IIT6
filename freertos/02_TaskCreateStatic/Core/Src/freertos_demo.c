#include "freertos_demo.h"

static void MX_FREERTOS_Init(void);

/**
 * @brief 初始化
 *
 */
void System_Task(void)
{
  Led_Init(led_b);
  Led_Init(led_g);
  Led_Init(led_r);

  osKernelInitialize();
  MX_FREERTOS_Init();
  osKernelStart();
}

TaskHandle_t Create_Handle;
StackType_t Create_Buff[128];
StaticTask_t Create_TCB;
void CreateTask(void *argument);

TaskHandle_t Cet_Handle;
// StackType_t Cet_Buff[128];
// StaticTask_t Cet_TCB;
void CetTask(void *argument);

TaskHandle_t LED1_Handle;
StackType_t LED1_Buff[128];
StaticTask_t LED1_TCB;
void LED1Task(void *argument);

TaskHandle_t LED2_Handle;
StackType_t LED2_Buff[128];
StaticTask_t LED2_TCB;
void LED2Task(void *argument);

TaskHandle_t LED3_Handle;
StackType_t LED3_Buff[128];
StaticTask_t LED3_TCB;
void LED3Task(void *argument);

void MX_FREERTOS_Init(void)
{
  Create_Handle = xTaskCreateStatic(CreateTask,"Create_Task",128,NULL,osPriorityIdle,Create_Buff,&Create_TCB);
}
void CreateTask(void *argument)
{
  taskENTER_CRITICAL();
  Uart_SendString((uint8_t *)"Create_Task\n");
  LED1_Handle = xTaskCreateStatic(LED1Task,"LED1_Task",128,NULL,osPriorityLow1,LED1_Buff,&LED1_TCB);
  LED2_Handle = xTaskCreateStatic(LED2Task,"LED2_Task",128,NULL,osPriorityLow2,LED2_Buff,&LED2_TCB);
  LED3_Handle = xTaskCreateStatic(LED3Task,"LED3_Task",128,NULL,osPriorityLow3,LED3_Buff,&LED3_TCB);
  xTaskCreate(CetTask,"Cet_Task",128,NULL,osPriorityLow4,&Cet_Handle);
  //Cet_Handle = xTaskCreateStatic(CetTask,"Cet_Task",128,NULL,osPriorityLow4,Cet_Buff,&Cet_TCB);
  vTaskDelete(Create_Handle);
  taskEXIT_CRITICAL();
}

void CetTask(void *argument){
  for(;;){
    Uart_Printf((uint8_t *)"LED1_Task:",uxTaskPriorityGet(LED1_Handle));
    Uart_Printf((uint8_t *)"LED2_Task:",uxTaskPriorityGet(LED2_Handle));
    Uart_Printf((uint8_t *)"LED3_Task:",uxTaskPriorityGet(LED3_Handle));
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void LED1Task(void *argument)
{
  for (;;)
  {
    __GPIO_SET_BIT(GPIOC, led_b);
    vTaskDelay(pdMS_TO_TICKS(100));
    __GPIO_RESET_BIT(GPIOC, led_b);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void LED2Task(void *argument)
{
  for (;;)
  { 
    __GPIO_SET_BIT(GPIOC, led_g);
    vTaskDelay(pdMS_TO_TICKS(100));
    __GPIO_RESET_BIT(GPIOC, led_g);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void LED3Task(void *argument)
{
  for (;;)
  {
    __GPIO_SET_BIT(GPIOC, led_r);
    vTaskDelay(pdMS_TO_TICKS(100));
    __GPIO_RESET_BIT(GPIOC, led_r);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
