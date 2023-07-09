#include "task1.h"
#include "LED.h"


#define LED_TOGGLE_1000_MILLI_SEC			1000
#define TASK_1_LED											1


// A task to toggle a LED every 1000 ms 
void vToggleTask(void* pvParameters)
{
	for(;;)
	{
		led_toggle(TASK_1_LED,LED_TOGGLE_1000_MILLI_SEC);
	}
}
TaskHandle_t ToggleTaskHandle = NULL;					// Toggle Task Handler

void Create_task_1(void)
{
		xTaskCreate(
                    vToggleTask,       // Function that implements the task. 
                    "Toggle Task",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    4,// Priority at which the task is created. 
                    &ToggleTaskHandle);      // Used to pass out the created task's handle. 
}