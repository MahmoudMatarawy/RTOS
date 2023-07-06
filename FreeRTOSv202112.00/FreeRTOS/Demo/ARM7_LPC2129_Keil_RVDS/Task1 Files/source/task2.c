#include "task2.h"
#include "LED.h"


TaskHandle_t Toggle_1000_TaskHandle = NULL;					// Toggle 1000 ms Task Handler
TaskHandle_t Toggle_500_TaskHandle = NULL;					// Toggle 500 ms Task Handler 
TaskHandle_t Toggle_100_TaskHandle = NULL;					// Toggle 100 ms Task Handler

// A task to toggle a LED every 1000 ms 
void vToggle1000Task(void* pvParameters)
{
	for(;;)
	{
		led_toggle(2,1000);
	}
}
  


// A task to toggle a LED every 500 ms 
void vToggle500Task(void* pvParameters)
{
	for(;;)
	{
		led_toggle(2,500);
	}
}


// A task to toggle a LED every 500 ms 
void vToggle100Task(void* pvParameters)
{
	for(;;)
	{
		led_toggle(2,100);
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
                    vToggle100Task,       // Function that implements the task. 
                    "toggle 100 task",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    2,// Priority at which the task is created. 
                    &Toggle_100_TaskHandle);      // Used to pass out the created task's handle. 
										
	
}
