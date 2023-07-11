#include "task3.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "serial.h"
#include "LED.h"
#include "Botton.h"


#define FALSE				0
#define TRUE				1
#define TASK_3_LED											3
#define TASK_3_BOTTON_1									2
#define TASK_3_BOTTON_2									3
#define TASK_3_BOTTON_1_PERIOD									10
#define TASK_3_BOTTON_2_PERIOD									10
#define TASK_3_SEND_STRING_1_PERIOD									100
#define TASK_3_SEND_STRING_2_PERIOD									100



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
static signed char string_1[]="Thank2\n";
static unsigned char string_1_size = 8;
static signed char string_2[]="I am Here2\n";
static unsigned char string_2_size = 12;


// function to read botton status and store pressed period
void vReadButton1(void * pvParameters)
{
	for(;;)
	{
		Botton_1 = botton_read(TASK_3_BOTTON_1);					// read botton status
		if(Botton_1 != prv_Botton_1)
		{
			task_1_send_flag = TRUE;
		}
		else
		{
			//task_1_send_flag = FALSE;
		}
		prv_Botton_1 = Botton_1;
		vTaskDelay(TASK_3_BOTTON_1_PERIOD);									// block the task
	}
}



void vReadButton2(void * pvParameters)
{
	for(;;)
	{
		Botton_2 = botton_read(TASK_3_BOTTON_2);					// read botton status
		if(Botton_2 != prv_Botton_2)
		{
			task_2_send_flag = TRUE;
		}
		else
		{
			//task_2_send_flag = FALSE;
		}
		prv_Botton_2 = Botton_2;
		vTaskDelay(TASK_3_BOTTON_2_PERIOD);													// block the task 
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
				led_on(TASK_3_LED);
				vSerialPutString(string_1, string_1_size);
				led_off(TASK_3_LED);
				xSemaphoreGive( Semaphore_Handler_2 );
			}
			task_1_send_flag = FALSE;
		}
		vTaskDelay(TASK_3_SEND_STRING_1_PERIOD);								// block the task
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
				led_on(TASK_3_LED);
				vSerialPutString(string_2, string_2_size);
				led_off(TASK_3_LED);
				xSemaphoreGive( Semaphore_Handler_2 );
			}
		}
		task_2_send_flag = FALSE;
		vTaskDelay(TASK_3_SEND_STRING_2_PERIOD);								// block the task
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
