// this file is made by hazem shaaban bakry
// as part of course work of learn in depth: mastering embedded systems diploma

#ifndef _PRESSURE_MONITORING_H_
#define _PRESSURE_MONITORING_H_

// states enum
typedef enum
{
	reading_pressure,
	high_pressure_detected
}PM_states_t;

// prototypes
void PM_reading_pressure_func();
void PM_high_pressure_detected_func();

// external functions
extern void Delay(unsigned int nCount);
extern int getPressureVal();
extern void pressure_monitoring_to_LED_controller_comm_func();

// state pointer
extern void(*PM_state_ptr)();


#endif