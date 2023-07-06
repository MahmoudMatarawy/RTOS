#include "task2.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "serial.h"
#include "LED.h"


SemaphoreHandle_t Semaphore_Handler = NULL;

TaskHandle_t Task_1_TaskHandle = NULL;					// Task 1 Task Handler
TaskHandle_t Task_2_TaskHandle = NULL;					// Task 2 Task Handler 

void vTask_1(void* pvParameters)
{
	static unsigned char semaphore_state = pdFALSE ;
	static unsigned char string_counter = 0;
	static unsigned int heavy_load_counter = 0;
	for(;;)
	{
		semaphore_state = xSemaphoreTake( Semaphore_Handler, ( TickType_t ) 0 );
		if(semaphore_state == pdTRUE)
		{
			led_on(2);
			for(string_counter = 0 ; string_counter < 10 ; string_counter++)
			{
				for (heavy_load_counter = 0; heavy_load_counter < 100000; heavy_load_counter++ )
						{
							/* do nothing */
						}
						vSerialPutString((signed char *)"Thank\n", 7);
			}
			led_off(2);
			xSemaphoreGive( Semaphore_Handler );
		}
		vTaskDelay(500);
	}
}
  


void vTask_2(void* pvParameters)
{
	static unsigned char semaphore_state = pdFALSE ;
	static unsigned char string_counter = 0;
	static unsigned int heavy_load_counter = 0;
	for(;;)
	{
		semaphore_state = xSemaphoreTake( Semaphore_Handler, ( TickType_t ) 0 );
		if(semaphore_state == pdTRUE)
		{
			led_on(2);
			for(string_counter = 0 ; string_counter < 10 ; string_counter++)
			{
				for (heavy_load_counter = 0; heavy_load_counter < 20000; heavy_load_counter++ )
						{
							/* do nothing */
						}
						vSerialPutString((signed char *)"I am Here\n", 11);
			}
			led_off(2);
			xSemaphoreGive( Semaphore_Handler );
		}
		vTaskDelay(100);
	}
}





void Create_task_2(void)
{
	
	Semaphore_Handler = xSemaphoreCreateMutex();
	xSemaphoreGive( Semaphore_Handler );
	xTaskCreate(
                    vTask_1,       // Function that implements the task. 
                    "task 1",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    4,// Priority at which the task is created. 
                    &Task_1_TaskHandle);      // Used to pass out the created task's handle. 
	xTaskCreate(
                    vTask_2,       // Function that implements the task. 
                    "task 2",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    3,// Priority at which the task is created. 
                    &Task_2_TaskHandle);      // Used to pass out the created task's handle. 
										

										
	
}
