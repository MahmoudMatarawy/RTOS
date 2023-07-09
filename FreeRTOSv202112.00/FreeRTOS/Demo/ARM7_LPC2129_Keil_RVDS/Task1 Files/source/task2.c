#include "task2.h"
#include "LED.h"

#define LED_TOGGLE_1000_MILLI_SEC			1000
#define LED_TOGGLE_500_MILLI_SEC			500
#define LED_TOGGLE_100_MILLI_SEC			100
#define TASK_2_LED_1											2
#define TASK_2_LED_2											3
#define TASK_2_LED_3											4



TaskHandle_t Toggle_1000_TaskHandle = NULL;					// Toggle 1000 ms Task Handler
TaskHandle_t Toggle_500_TaskHandle = NULL;					// Toggle 500 ms Task Handler 
TaskHandle_t Toggle_100_TaskHandle = NULL;					// Toggle 100 ms Task Handler

// A task to toggle a LED every 1000 ms 
void vToggle1000Task(void* pvParameters)
{
	for(;;)
	{
		led_toggle(TASK_2_LED_1,LED_TOGGLE_1000_MILLI_SEC);
	}
}
  


// A task to toggle a LED every 500 ms 
void vToggle500Task(void* pvParameters)
{
	for(;;)
	{
		led_toggle(TASK_2_LED_2,LED_TOGGLE_500_MILLI_SEC);
	}
}


// A task to toggle a LED every 500 ms 
void vToggle100Task2(void* pvParameters)
{
	for(;;)
	{
		led_toggle(TASK_2_LED_3,LED_TOGGLE_100_MILLI_SEC);
	}
}



void Create_task_2(void)
{
	xTaskCreate(
                    vToggle1000Task,       // Function that implements the task. 
                    "Toggle 1000 Task",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    4,// Priority at which the task is created. 
                    &Toggle_1000_TaskHandle);      // Used to pass out the created task's handle. 
	xTaskCreate(
                    vToggle500Task,       // Function that implements the task. 
                    "Toggle 500 Task",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    3,// Priority at which the task is created. 
                    &Toggle_500_TaskHandle);      // Used to pass out the created task's handle. 
										
	xTaskCreate(
                    vToggle100Task2,       // Function that implements the task. 
                    "toggle 100 task",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    2,// Priority at which the task is created. 
                    &Toggle_100_TaskHandle);      // Used to pass out the created task's handle. 
										
	
}
