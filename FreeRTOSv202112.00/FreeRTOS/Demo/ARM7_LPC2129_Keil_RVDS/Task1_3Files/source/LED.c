#include "LED.h"


#define LedPin PIN2
#define LedPort  PORT_0


void led_off(void)
{
	GPIO_write(LedPort , LedPin , PIN_IS_LOW);		// Set LED pin LOW
}



void led_toggle(int period)
{
	GPIO_write(LedPort , LedPin , PIN_IS_HIGH);	// Set LED pin high
		
	vTaskDelay(period);													// Block the task 
		
	GPIO_write(LedPort , LedPin , PIN_IS_LOW);		// Set LED pin LOW
				
	vTaskDelay(period);													// Block the task 
}


