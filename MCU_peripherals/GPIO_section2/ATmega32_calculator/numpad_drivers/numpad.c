/*==================================================================================*
 *                  		code is made by hazem shaaban                   		*
 * it is submitted to Learn in depth:Mastering embedded systems as an assignment 	*
 *                                                                					*
 *  						Functions file for keypad drivers  		 				*
 *                                                                  				*
 * 			this might not be the best way to do it, but it does the job     		*
 *                     				for a beginner                             		*
/*==================================================================================*/



#include "numpad.h"

static char pad_matrix[4][4] = {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'?','0','=','+'}};

void NUMPAD_init(void)
{
	// first 4 pins output, last 4 pins input
	NUMPAD_PORT_DIR	= 0x0F;
	// output pins high, input pins pulled high
	NUMPAD_WRITE = 0xFF;
}

char NUMPAD_read(void)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		// turn off pin i
		NUMPAD_WRITE &= ~(1 << i);
		
		for (j = 4; j < 8; j++)
		{
			if ((NUMPAD_READ & 1<<j) == 0)
			{
				while ((NUMPAD_READ & 1<<j) == 0);		// stay in loop until button is not pressed
				
				NUMPAD_WRITE |= 1<<i;
				return pad_matrix[i][j - 4];
			}
			_delay_ms(2);	
		}
		NUMPAD_WRITE |= 1<<i;
		_delay_ms(2);
	}
	return 0;
}