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
void CreateTask(void *argument);

TaskHandle_t Key_Handle;
TaskHandle_t LED1_Handle;
TaskHandle_t LED2_Handle;
TaskHandle_t LED3_Handle;
void KeyTask(void *argument);
void LED1Task(void *argument);
void LED2Task(void *argument);
void LED3Task(void *argument);


void MX_FREERTOS_Init(void)
{
  xTaskCreate(CreateTask,"Create_Task",128,NULL,osPriorityIdle,&Create_Handle);
}

void CreateTask(void *argument)
{
  taskENTER_CRITICAL();
  Uart_SendString((uint8_t *)"Create_Task\n");
  xTaskCreate(LED1Task,"LED1_Task",128,NULL,osPriorityLow1,&LED1_Handle);
  xTaskCreate(LED2Task,"LED2_Task",128,NULL,osPriorityLow2,&LED2_Handle);
  xTaskCreate(LED3Task,"LED3_Task",128,NULL,osPriorityLow3,&LED3_Handle);
  xTaskCreate(KeyTask,"Key_Task",128,NULL,osPriorityLow4,&Key_Handle);
  vTaskDelete(Create_Handle);
  taskEXIT_CRITICAL();
}

void KeyTask(void *argument){
  for(;;){

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void LED1Task(void *argument)
{
  uint32_t num=0;
  for (;;)
  {
    Uart_Printf((uint8_t *)"LED1_Task:",++num);
    __GPIO_SET_BIT(GPIOC, led_b);
    vTaskDelay(pdMS_TO_TICKS(100));
    __GPIO_RESET_BIT(GPIOC, led_b);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void LED2Task(void *argument)
{
  uint32_t num=0;
  for (;;)
  {
    Uart_Printf((uint8_t *)"LED2_Task:",++num);
    __GPIO_SET_BIT(GPIOC, led_g);
    vTaskDelay(pdMS_TO_TICKS(100));
    __GPIO_RESET_BIT(GPIOC, led_g);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void LED3Task(void *argument)
{
  uint32_t num=0;
  for (;;)
  {
    Uart_Printf((uint8_t *)"LED3_Task:",++num);
    __GPIO_SET_BIT(GPIOC, led_r);
    vTaskDelay(pdMS_TO_TICKS(100));
    __GPIO_RESET_BIT(GPIOC, led_r);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
