#include <stdint.h>
#include <stdio.h>

#include "driver/driver.h"

//extern state pointers
extern void(*PM_state_ptr)();
extern void (*LED_state_ptr)();
extern void (*PS_state_ptr)();


int main (){
	GPIO_INITIALIZATION();
	while (1)
	{
		//Implement your Design 
		PS_state_ptr();
		PM_state_ptr();
		LED_state_ptr();
	}

}
