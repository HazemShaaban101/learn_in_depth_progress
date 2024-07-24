// this file is made by hazem shaaban bakry
// as part of course work of learn in depth: mastering embedded systems diploma

#ifndef _LED_CONTROLLER_H_
#define _LED_CONTROLLER_H_

// state enum
typedef enum
{
	LED_off,
	LED_on
}LED_states_t;


//external functions
extern void Set_Alarm_actuator(int i);
extern void Delay(unsigned int nCount);


// state methods
void LED_off_func();
void LED_on_func();


// state pointer
extern void (*LED_state_ptr)();


#endif