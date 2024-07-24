// this file is made by hazem shaaban bakry
// as part of course work of learn in depth: mastering embedded systems diploma


#include "pressure_monitoring.h"

// states enum
PM_states_t PM_state = reading_pressure;

// state function pointer
void(*PM_state_ptr)() = &PM_reading_pressure_func;

int pressure_reading = 0;  //glabla variable to save reading, wasn't made local so it would show on proteus variables tab

// pressure threshold constant
const int pressure_threshold = 20;

// communication function, helps previous block decide this block's state before executing corresponding state function
void pressure_sensor_to_pressure_monitoring_comm_func(int value)
{
	pressure_reading = value;
	if (pressure_reading > pressure_threshold) // if pressure reading exceeded the pressure threshold
	{
		PM_state_ptr = PM_high_pressure_detected_func; // set current state to high pressure detected
	}
	else
	{
		PM_state_ptr = PM_reading_pressure_func; // if not higher set state pointer to reading pressure
	}
	
}




// reading pressure state
void PM_reading_pressure_func(){
	PM_state = reading_pressure;
	Delay(100000);  // wait before next reading
}

// high pressure detected state
void PM_high_pressure_detected_func(){
	PM_state = high_pressure_detected;
	pressure_monitoring_to_LED_controller_comm_func();
}