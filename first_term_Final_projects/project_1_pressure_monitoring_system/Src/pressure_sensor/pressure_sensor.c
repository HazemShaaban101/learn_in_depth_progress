// this file is made by hazem shaaban bakry
// as part of course work of learn in depth: mastering embedded systems diploma

#include "pressure_sensor.h"

// pressure sensor state function pointer
void (*PS_state_ptr)() = PS_reading_pressure_func;

// pressure sensor state
PS_states_t PS_state = reading_pressure;

// reading pressure state function
void PS_reading_pressure_func()
{
	pressure_sensor_to_pressure_monitoring_comm_func(getPressureVal());
}