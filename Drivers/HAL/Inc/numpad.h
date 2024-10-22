/************************************************************************************************
				This file is the Numpad driver Header
				this file include:
					- Numpad Port
					- Numpad Pins
					- Numpad APIs
					
				this file is incremental, meaning it is constantly updated based on
				my next project requirements. it is not fully functional for all numpad
				functions until specified otherwise.
				
				
				*************************************************************
				*				Made by: Hazem Shaaban Bakry				*
				*				github: HazemShaaban101						*
				*				Linkedin: hazemshaaban101					*
				*************************************************************
*************************************************************************************************/



//===============================================================================================
//	important includes
//===============================================================================================

#ifndef NUMPAD_H_
#define NUMPAD_H_
#include "ATmega32.h"
#include "GPIO.h"



//===============================================================================================
// Numpad Pin ports
//===============================================================================================
#define NUMPAD_PORT				GPIOB


//===============================================================================================
// Numpad Pins
//===============================================================================================
#define NP_A					(0)
#define NP_B					(1)
#define NP_C					(2)
#define NP_D					(3)
#define NP_1					(4)
#define NP_2					(5)
#define NP_3					(6)
#define NP_4					(7)



//===============================================================================================
// Numpad APIs
//===============================================================================================
void NUMPAD_init(void);
char NUMPAD_read(void);


#endif
