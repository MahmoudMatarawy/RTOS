#include "LED.h"


#define Led_1_Pin PIN2
#define Led_1_Port  PORT_0
#define Led_2_Pin PIN3
#define Led_2_Port  PORT_0
#define Led_3_Pin PIN4
#define Led_3_Port  PORT_0
#define Led_4_Pin PIN5
#define Led_4_Port  PORT_0
#define Led_5_Pin PIN6
#define Led_5_Port  PORT_0
void led_off(unsigned char led_num)
{
	if(1 == led_num)
		GPIO_write(Led_1_Port , Led_1_Pin , PIN_IS_LOW);		// Set LED pin LOW
	else if(2 == led_num)
		GPIO_write(Led_2_Port , Led_2_Pin , PIN_IS_LOW);		// Set LED pin LOW
	else if(3 == led_num)
		GPIO_write(Led_3_Port , Led_3_Pin , PIN_IS_LOW);		// Set LED pin LOW
	else if(4 == led_num)
		GPIO_write(Led_4_Port , Led_4_Pin , PIN_IS_LOW);		// Set LED pin LOW
	else if(5 == led_num)
		GPIO_write(Led_5_Port , Led_5_Pin , PIN_IS_LOW);		// Set LED pin LOW
	else{
		// do nothing
	}
}



void led_toggle(unsigned char led_num,int period)
{
	if(1 == led_num)
		GPIO_write(Led_1_Port , Led_1_Pin , PIN_IS_HIGH);		// Set LED pin high
	else if(2 == led_num)
		GPIO_write(Led_2_Port , Led_2_Pin , PIN_IS_HIGH);		// Set LED pin high
	else if(3 == led_num)
		GPIO_write(Led_3_Port , Led_3_Pin , PIN_IS_HIGH);		// Set LED pin high
	else if(4 == led_num)
		GPIO_write(Led_4_Port , Led_4_Pin , PIN_IS_HIGH);		// Set LED pin high
	else if(5 == led_num)
		GPIO_write(Led_5_Port , Led_5_Pin , PIN_IS_HIGH);		// Set LED pin high
	else{
		// do nothing
	}
		
	vTaskDelay(period);													// Block the task 
		
	if(1 == led_num)
		GPIO_write(Led_1_Port , Led_1_Pin , PIN_IS_LOW);		// Set LED pin LOW
	else if(2 == led_num)
		GPIO_write(Led_2_Port , Led_2_Pin , PIN_IS_LOW);		// Set LED pin LOW
	else if(3 == led_num)
		GPIO_write(Led_3_Port , Led_3_Pin , PIN_IS_LOW);		// Set LED pin LOW
	else if(4 == led_num)
		GPIO_write(Led_4_Port , Led_4_Pin , PIN_IS_LOW);		// Set LED pin LOW
	else if(5 == led_num)
		GPIO_write(Led_5_Port , Led_5_Pin , PIN_IS_LOW);		// Set LED pin LOW
	else{
		// do nothing
	}
				
	vTaskDelay(period);													// Block the task 
}


