#include "LED.h"
#include "Botton.h"

// Functions Prototype
extern void vReadButton(void * pvParameters);
extern void vLedOff(void * pvParameters);
extern void vToggle100Task(void* pvParameters);
extern void vToggle400Task(void* pvParameters);

extern void Create_all_tasks(void);
