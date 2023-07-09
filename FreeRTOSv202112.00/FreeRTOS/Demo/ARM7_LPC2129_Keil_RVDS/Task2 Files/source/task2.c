#include "task2.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "serial.h"
#include "LED.h"


#define TASK_2_LED											3
#define TASK_2_1_PERIOD									500
#define TASK_2_2_PERIOD									100
#define STRINGS_NUM											10
#define HEAVEY_LOAD_MAX_TASK_1					100000	
#define HEAVEY_LOAD_MAX_TASK_2					20000	

static signed char string_1[]="Thank\n";
static unsigned char string_1_size = 7;
static signed char string_2[]="I am Here\n";
static unsigned char string_2_size = 11;
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
			led_on(TASK_2_LED);
			for(string_counter = 0 ; string_counter < STRINGS_NUM ; string_counter++)
			{
				for (heavy_load_counter = 0; heavy_load_counter < HEAVEY_LOAD_MAX_TASK_1; heavy_load_counter++ )
						{
							/* do nothing */
						}
						vSerialPutString(string_1, string_1_size);
			}
			led_off(TASK_2_LED);
			xSemaphoreGive( Semaphore_Handler );
		}
		vTaskDelay(TASK_2_1_PERIOD);
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
			led_on(TASK_2_LED);
			for(string_counter = 0 ; string_counter < STRINGS_NUM ; string_counter++)
			{
				for (heavy_load_counter = 0; heavy_load_counter < HEAVEY_LOAD_MAX_TASK_2; heavy_load_counter++ )
						{
							/* do nothing */
						}
						vSerialPutString(string_2, string_2_size);
			}
			led_off(TASK_2_LED);
			xSemaphoreGive( Semaphore_Handler );
		}
		vTaskDelay(TASK_2_2_PERIOD);
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
