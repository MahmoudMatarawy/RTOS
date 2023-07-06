#include "task1.h"
#include "LED.h"
#include "Botton.h"

#define OFF			0
#define ON			1

static unsigned char prog_state =  OFF;

static unsigned char btn_state =  PIN_IS_LOW;
static unsigned char prv_btn_state =  PIN_IS_LOW;

// A task to read the botton 
void vReadBtn(void* pvParameters)
{
	for(;;)
	{
		btn_state = botton_read(1);
		if((btn_state == PIN_IS_LOW) && (prv_btn_state == PIN_IS_HIGH))
		{
			if(prog_state == OFF)
				prog_state = ON;
			else if(prog_state == ON)
				prog_state = OFF;
			else{
				// do nothing
			}
		}
		prv_btn_state = btn_state;
		vTaskDelay(10);
	}
}


void vLedUpdate(void * pvParameters)
{
	for(;;)
	{
		if(prog_state == OFF)
			led_off(1);
		else if(prog_state == ON)
			led_on(1);
		else{
			// do nothing
		}
		vTaskDelay(10);
	}
}



TaskHandle_t ReadBtnTaskHandle = NULL;					// Read botton Task Handler
TaskHandle_t vLedUpdateTaskHandle = NULL;					// Led update Task Handler


void Create_task_1(void)
{
		xTaskCreate(
                    vReadBtn,       // Function that implements the task. 
                    "Read botton",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    4,// Priority at which the task is created. 
                    &ReadBtnTaskHandle);      // Used to pass out the created task's handle. 
		xTaskCreate(
                    vLedUpdate,       // Function that implements the task. 
                    "LED update",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    4,// Priority at which the task is created. 
                    &vLedUpdateTaskHandle);      // Used to pass out the created task's handle.
}

