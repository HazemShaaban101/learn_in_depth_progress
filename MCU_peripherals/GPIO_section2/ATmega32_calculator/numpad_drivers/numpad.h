/*==================================================================================*
 *                  		code is made by hazem shaaban                   		*
 * it is submitted to Learn in depth:Mastering embedded systems as an assignment 	*
 *                                                                					*
 *  						Header file for keypad drivers  		 				*
 *                                                                  				*
 * 			this might not be the best way to do it, but it does the job     		*
 *                     				for a beginner                             		*
/*==================================================================================*/


#ifndef NUMPAD_H_
#define NUMPAD_H_

#include "MemoryMap.h"
#define F_CPU 8000000UL
#include <util/delay.h>

// numpad pin configuration
#define NUMPAD_PORT_DIR			DDRC
#define NUMPAD_WRITE			portC_data
#define NUMPAD_READ				pinC


// function prototypes
void NUMPAD_init(void);
char NUMPAD_read(void);


#endif
