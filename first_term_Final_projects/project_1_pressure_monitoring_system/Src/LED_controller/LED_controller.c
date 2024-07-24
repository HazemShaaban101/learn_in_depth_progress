// this file is made by hazem shaaban bakry
// as part of course work of learn in depth: mastering embedded systems diploma

#include "LED_controller.h"

// led state function pointer
void (*LED_state_ptr)() = LED_off_func;

// current state
LED_states_t LED_state = LED_off;

// communication function, helps previous block decide this block's state before executing corresponding state function
void pressure_monitoring_to_LED_controller_comm_func()
{
	LED_state_ptr = LED_on_func;
}

// led off state function
void LED_off_func()
{
	LED_state = LED_off;
	Set_Alarm_actuator(0); // make sure led if OFF
}


// led on state function
void LED_on_func()
{
	LED_state = LED_on;
	Set_Alarm_actuator(1); // turn on alarm
	Delay(6000000); // wait 60 seconds
	Set_Alarm_actuator(0); // turn off alarm
	LED_state_ptr = LED_off_func; // set current state to reading pressure
}