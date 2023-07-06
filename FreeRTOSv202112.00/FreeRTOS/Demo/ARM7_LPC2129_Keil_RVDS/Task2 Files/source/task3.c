#include "task3.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "serial.h"
#include "LED.h"
#include "Botton.h"


#define FALSE				0
#define TRUE				1

TaskHandle_t vReadButton1_Task_Handle=NULL;					// Botton task handler
TaskHandle_t vReadButton2_Task_Handle = NULL;					// LED OFF Task Handler
TaskHandle_t vBotton_1_events_Task_handle = NULL;	// LED toggle every 100ms task handler
TaskHandle_t vBotton_2_events_Task_handle = NULL;	// LED toggle every 400ms task handler
SemaphoreHandle_t Semaphore_Handler_2;

pinState_t Botton_1= PIN_IS_LOW;												// store botton status
pinState_t Botton_2= PIN_IS_LOW;
pinState_t prv_Botton_1= PIN_IS_LOW;												// store botton status
pinState_t prv_Botton_2= PIN_IS_LOW;

static unsigned char task_1_send_flag = FALSE;
static unsigned char task_2_send_flag = FALSE;

// function to read botton status and store pressed period
void vReadButton1(void * pvParameters)
{
	for(;;)
	{
		Botton_1 = botton_read(2);					// read botton status
		if(Botton_1 != prv_Botton_1)
		{
			task_1_send_flag = TRUE;
		}
		else
		{
			//task_1_send_flag = FALSE;
		}
		prv_Botton_1 = Botton_1;
		vTaskDelay(10);									// block the task
	}
}



void vReadButton2(void * pvParameters)
{
	for(;;)
	{
		Botton_2 = botton_read(3);					// read botton status
		if(Botton_2 != prv_Botton_2)
		{
			task_2_send_flag = TRUE;
		}
		else
		{
			//task_2_send_flag = FALSE;
		}
		prv_Botton_2 = Botton_2;
		vTaskDelay(10);													// block the task 
	}
}



void vBotton_1_events(void* pvParameters)
{
	static unsigned char semaphore_state = pdFALSE ;
	for(;;)
	{
		if(task_1_send_flag == TRUE)
		{
			semaphore_state = xSemaphoreTake( Semaphore_Handler_2, ( TickType_t ) 0 );
			if(semaphore_state == pdTRUE)
			{
				led_on(3);
				vSerialPutString((signed char *)"Thank2\n", 8);
				led_off(3);
				xSemaphoreGive( Semaphore_Handler_2 );
			}
			task_1_send_flag = FALSE;
		}
		vTaskDelay(100);								// block the task
	}
}



void vBotton_2_events(void* pvParameters)
{
	static unsigned char semaphore_state = pdFALSE ;
	for(;;)
	{
		if(task_2_send_flag == TRUE)
		{
			semaphore_state = xSemaphoreTake( Semaphore_Handler_2, ( TickType_t ) 0 );
			if(semaphore_state == pdTRUE)
			{
				led_on(3);
				vSerialPutString((signed char *)"I am Here2\n", 12);
				led_off(3);
				xSemaphoreGive( Semaphore_Handler_2 );
			}
		}
		task_2_send_flag = FALSE;
		vTaskDelay(100);								// block the task
	}
}



void Create_task_3(void)
{
	Semaphore_Handler_2 = xSemaphoreCreateMutex();
	xSemaphoreGive( Semaphore_Handler_2 );
	xTaskCreate(
                    vReadButton1,       // Function that implements the task. 
                    "Read Botton 1",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    4,// Priority at which the task is created. 
                    &vReadButton1_Task_Handle);      // Used to pass out the created task's handle. 
	xTaskCreate(
                    vReadButton2,       // Function that implements the task. 
                    "Read botton 2",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    3,// Priority at which the task is created. 
                    &vReadButton2_Task_Handle);      // Used to pass out the created task's handle. 
										
	xTaskCreate(
                    vBotton_1_events,       // Function that implements the task. 
                    "Botton 1 events",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    2,// Priority at which the task is created. 
                    &vBotton_1_events_Task_handle);      // Used to pass out the created task's handle. 
										
	xTaskCreate(
                    vBotton_2_events,       // Function that implements the task. 
                    "Botton 2 events",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    2,// Priority at which the task is created. 
                    &vBotton_2_events_Task_handle);      // Used to pass out the created task's handle. 
}
