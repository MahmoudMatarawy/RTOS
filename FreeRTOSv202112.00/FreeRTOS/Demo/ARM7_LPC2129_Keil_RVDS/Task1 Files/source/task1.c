#include "task1.h"
#include "LED.h"
// A task to toggle a LED every 1000 ms 
void vToggleTask(void* pvParameters)
{
	for(;;)
	{
		led_toggle(1,1000);
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