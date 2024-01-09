#include "freertos_demo.h"

static void MX_FREERTOS_Init(void);

/**
 * @brief 初始化
 *
 */
void System_Task(void)
{
  osKernelInitialize();
	MX_FREERTOS_Init();
	osKernelStart();
  Led_Init(led_b);
  Led_Init(led_g);
  Led_Init(led_r);
}

void LED1Task(void *argument);
void LED2Task(void *argument);
void LED3Task(void *argument);

void MX_FREERTOS_Init(void)
{
  TaskHandle_t LED1_Task;
  xTaskCreate(LED1Task,"LED1_Task",128,NULL,osPriorityNormal1,&LED1_Task);
  TaskHandle_t LED2_Task;
  xTaskCreate(LED2Task,"LED2_Task",128,NULL,osPriorityNormal1,&LED2_Task);
  TaskHandle_t LED3_Task;
  xTaskCreate(LED3Task,"LED3_Task",128,NULL,osPriorityNormal1,&LED3_Task);

}

void LED1Task(void *argument)
{
  for(;;){
  Uart_SendString((uint8_t *)"LED1_Task\n");
  __GPIO_SET_BIT(GPIOC, led_b);
  osDelay(100);
  __GPIO_RESET_BIT(GPIOC, led_b);
  osDelay(100);
  }
}

void LED2Task(void *argument)
{
  for(;;){
    Uart_SendString((uint8_t *)"LED2_Task\n");
    __GPIO_SET_BIT(GPIOC, led_g);
    osDelay(100);
    __GPIO_RESET_BIT(GPIOC, led_g);
    osDelay(100);
  }

}

void LED3Task(void *argument)
{
  for(;;){
    Uart_SendString((uint8_t *)"LED3_Task\n");
    __GPIO_SET_BIT(GPIOC, led_r);
    osDelay(100);
    __GPIO_RESET_BIT(GPIOC, led_r);
    osDelay(100);
  }
}
