#include "Botton.h"

#define Botton_Pin	PIN0							// Botton Pin 
#define Botton_Port PORT_0						// Botton Port

// Function to read botton status
pinState_t botton_read(void)
{
	pinState_t state;
	state = GPIO_read(Botton_Port,Botton_Pin);				// Read Botton status
	return state;
}

