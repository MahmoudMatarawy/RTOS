#include "task3.h"


TaskHandle_t Botton_Task_Handle=NULL;					// Botton task handler
TaskHandle_t LedOffTaskHandle = NULL;					// LED OFF Task Handler
TaskHandle_t Toggle_Led_100_Task_handle = NULL;	// LED toggle every 100ms task handler
TaskHandle_t Toggle_Led_400_Task_handle = NULL;	// LED toggle every 400ms task handler

pinState_t Botton= PIN_IS_LOW;												// store botton status



signed int occ ;																// store botton pressed period
int led_sta;																		// store led status 
																								// led_off_sta : Led is off
																								// led_tog_100_sta : Led in toggle mode every 100 ms
																								// led_tog_400_sta : Led in toggle mode every 400 ms																								
#define led_off_sta				1											// led off status 
#define led_tog_100_sta		2											// led toggle every 100 ms status
#define led_tog_400_sta		3											// led toggle every 400 ms status

// function to read botton status and store pressed period
void vReadButton(void * pvParameters)
{
	for(;;)
	{
		Botton = botton_read();					// read botton status
		if(Botton == PIN_IS_HIGH)
		{
			occ +=10;											// store pressed period occurrence 
		}
		vTaskDelay(10);									// block the task
	}
}


// Function to turn led off if push botton pressed shorter than 2000 ms
void vLedOff(void * pvParameters)
{
	for(;;)
	{
		if((occ < 2000)&&(occ > 0)&&(Botton == PIN_IS_LOW)&&(led_sta != led_off_sta)) // chack occurrence , pin status and led status
		{
			led_off(3);														// turn led off
			occ=0;																// clear occurrence 
			led_sta = led_off_sta ;								// store led status
		}
		vTaskDelay(50);													// block the task 
	}
}


// Function to toggle led every 100 ms if push botton pressed longer than 4000 ms 
void vToggle100Task3(void* pvParameters)
{
	for(;;)
	{
		if(Botton == PIN_IS_LOW)
		{
			if(occ > 4000)
			{
				occ = 0;										// clear occurrence
				led_sta = led_tog_100_sta;	// store led status
				while(led_sta==led_tog_100_sta)
				{
					led_toggle(3,100);					// toggle the led every 100 ms
				}
			}
		}
		vTaskDelay(100);								// block the task
	}
}

// Function to toggle the led every 400 ms if botton pressed more than 2000 ms and less than 4000 ms 
void vToggle400Task(void* pvParameters)
{
	for(;;)
	{
		if(Botton == PIN_IS_LOW)
		{
			if((occ <= 4000)&&(occ >= 2000))
			{            
				occ = 0;   													// clear occurrence
				led_sta = led_tog_400_sta;					// store led status
				while(led_sta==led_tog_400_sta)
				{
					led_toggle(3,400);									// toggle the led every 400 ms
				}
			}
		}
		vTaskDelay(100);												// block the task
	}
}



void Create_task_3(void)
{
	occ = -10;													// init. the occurrence  
	led_sta = 0 ;												// init. the led status
	xTaskCreate(
                    vReadButton,       // Function that implements the task. 
                    "Read Botton",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    4,// Priority at which the task is created. 
                    &Botton_Task_Handle);      // Used to pass out the created task's handle. 
	xTaskCreate(
                    vLedOff,       // Function that implements the task. 
                    "LED OFF",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    3,// Priority at which the task is created. 
                    &LedOffTaskHandle);      // Used to pass out the created task's handle. 
										
	xTaskCreate(
                    vToggle100Task3,       // Function that implements the task. 
                    "toggle 100 task",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    2,// Priority at which the task is created. 
                    &Toggle_Led_100_Task_handle);      // Used to pass out the created task's handle. 
										
	xTaskCreate(
                    vToggle400Task,       // Function that implements the task. 
                    "toggle 400 task",          // Text name for the task. 
                    20,      // Stack size in words, not bytes. 
                    ( void * ) 0,    // Parameter passed into the task. 
                    2,// Priority at which the task is created. 
                    &Toggle_Led_400_Task_handle);      // Used to pass out the created task's handle. 
}
