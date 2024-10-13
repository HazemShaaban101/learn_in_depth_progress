/*==================================================================================*
 *                  		code is made by hazem shaaban                   		*
 * it is submitted to Learn in depth:Mastering embedded systems as an assignment 	*
 *                                                                					*
 *     			this code turns on 8 LEDs ascendingly and then turns them 			*
 *									off descindingly								*
 *                                                                  				*
 * 			this might not be the best way to do it, but it does the job     		*
 *                     				for a beginner                             		*
/*==================================================================================*/


#include "MemoryMap.h"
#define F_CPU 8000000UL
#include <util/delay.h>


int main()
{
	DDRA |= 0xFF;
	while(1)
	{
		int i = 0, j = 0;
		for (i = 0; i < 8; i++)
		{
			portA_data |= (1 << i);
			_delay_ms(500);
		}
		for (i = 7; i >= 0; i--)
		{
			portA_data &= ~(1 << i);
			_delay_ms(500);
		}
	}
}