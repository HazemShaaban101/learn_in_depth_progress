// this file is made by hazem shaaban bakry
// as part of course work of learn in depth: mastering embedded systems diploma

#ifndef _PRESSURE_SENSOR_H
#define _PRESSURE_SENSOR_H

// state enum
typedef enum
{
	reading_pressure
}PS_states_t;


//external functions
extern int getPressureVal();
extern void pressure_sensor_to_pressure_monitoring_comm_func(int value);


// state methods
void PS_reading_pressure_func();


// state pointer
extern void (*PS_state_ptr)();


#endif