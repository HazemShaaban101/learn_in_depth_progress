/*==================================================================================*
 *                  		code is made by hazem shaaban                   		*
 * it is submitted to learn in depth:mastering embedded systems as an assignment 	*
 *                                                                					*
 *     	this code turns leds on sequentially, one led for each button press			*
 *		button is debounced using flag. it also increments two multiplexed 			*
 *						7 segment displays every second								*
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
	// sets all pins in port a to output
	DDRA |= 0xff;
	
	// sets pin 0 in port c as input
	RESET_BIT(DDRC, 0);
	
	// sets all pins in port d to output
	DDRD |= 0xff;
	// turns on pull up resistance for pin 0 port c
	SET_BIT(portC_data, 0);
	
	int i = 0, j = 0, step = 1, flag = 0;
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
					if (READ_BIT(pinC, 0) == 0)
					{
						// check if flag is not set yet
						if (flag == 0)
						{
							// set the flag before turning on the led, if the button is not unpressed the flag will prevent the next leds from turning on
							flag = 1;
							TOGGLE_BIT(portA_data, i);
							i = i + step;
						
							// checks the bounds of the led sequence, if the counter goes out of bound it inverts the direction of the step and sets the counter to last led toggled
							if (i > 7)
							{
								step = - 1;
								i = 7;
							}
							else if (i < 0)
							{
								step = 1;
								i = 0;
							}
						}
					}
					// if no button press detected, set flag to zero
					else
					{
						flag = 0;
					}
					
					// update seven segments displays using multiplexing, each gets updated for 10 milliseconds
					portD_data = (0b0010 << 4) | b;
					_delay_ms(10);
					portD_data = (0b0001 << 4) | a;
					_delay_ms(10);
				}
			}
		}
	}
}