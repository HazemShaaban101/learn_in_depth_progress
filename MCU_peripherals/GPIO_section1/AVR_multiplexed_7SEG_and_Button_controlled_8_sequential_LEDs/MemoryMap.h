/*==================================================================================*
 *                  		code is made by hazem shaaban                   		*
 * it is submitted to Learn in depth:Mastering embedded systems as an assignment 	*
 *                                                                					*
 *  this header file contains all addresses for useful registers to the project  	*
 *                                                                  				*
 * 			this might not be the best way to do it, but it does the job     		*
 *                     				for a beginner                             		*
/*==================================================================================*/

#include <stdint.h>


#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_

// port A
#define pinA		*((volatile unsigned char *) 0x39)
#define DDRA		*((volatile unsigned char *) 0x3A)
#define portA_data	*((volatile unsigned char *) 0x3B)

// port B
#define pinB		*((volatile unsigned char *) 0x36)
#define DDRB		*((volatile unsigned char *) 0x37)
#define portB_data	*((volatile unsigned char *) 0x38)

// port C
#define pinC		*((volatile unsigned char *) 0x33)
#define DDRC		*((volatile unsigned char *) 0x34)
#define portC_data	*((volatile unsigned char *) 0x35)

// port D
#define pinD		*((volatile unsigned char *) 0x30)
#define DDRD		*((volatile unsigned char *) 0x31)
#define portD_data	*((volatile unsigned char *) 0x32)



#endif