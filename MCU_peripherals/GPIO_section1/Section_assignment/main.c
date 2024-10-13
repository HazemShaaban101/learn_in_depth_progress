/*==================================================================================*
 *                  		code is made by hazem shaaban                   		*
 * it is submitted to learn in depth:mastering embedded systems as an assignment 	*
 *                                                                					*
 *     	this code turns leds on sequentially, one led for each button press			*
 *	button is debounced using flag and a buzzer starts with each button press. 		*
 *		it also increments two multiplexed 7 segment displays every second			*
 *                                                                  				*
 * 			this might not be the best way to do it, but it does the job     		*
 *                     				for a beginner                             		*
/*==================================================================================*/

#include "utility_macros.h"
#include "MemoryMap.h"
#define F_CPU 8000000UL
#include <util/delay.h>

int main()
{
	// sets all pins in port C to output
	DDRC |= 0xff;
	
	// sets pin 0 in port D as input and the rest to output
	DDRD |= 0xFF;
	RESET_BIT(DDRD, 0);
	
	
	int i = 5, step = 1, flag = 0;
	while(1)
	{
		int a, b;
		for (a = 0; a < 10; a++)
		{
			for (b = 0; b < 10; b++)
			{
				// increment 7 segments
				int c;
				for (c = 0; c < 50; c++)
				{
					// check if button is pressed
					if (READ_BIT(pinD, 0) == 1)
					{
						// check if flag is not set yet
						if (flag == 0)
						{
							// set the flag before turning on the led, if the button is not unpressed the flag will prevent the next LEDs from turning on
							flag = 1;
							TOGGLE_BIT(portD_data, i);
							
							// start buzzer for 50 ms
							SET_BIT(portD_data, 4);
							_delay_ms(50);
							RESET_BIT(portD_data, 4);
							
							// increment/decrement LED
							i = i + step;
						
							// checks the bounds of the LED sequence, if the counter goes out of bound it inverts the direction of the step and sets the counter to last LED toggled
							if (i > 7)
							{
								step = - 1;
								i = 7;
							}
							else if (i < 5)
							{
								step = 1;
								i = 5;
							}
						}
					}
					// if no button press detected, set flag to zero
					else
					{
						flag = 0;
					}
					
					// update seven segments displays using multiplexing, each gets updated for 10 milliseconds
					portC_data = (b << 4) | 0b0100;
					_delay_ms(10);
					portC_data = (a << 4) | 0b1000;
					_delay_ms(10);
				}
				
				// turn off buzzer after one second
				RESET_BIT(portD_data, 4);
			}
		}
	}
}