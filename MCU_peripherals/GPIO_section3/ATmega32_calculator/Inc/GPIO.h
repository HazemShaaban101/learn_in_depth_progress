/************************************************************************************************
				This file is the GPIO driver header for stm32f103x8 devices
				this file include:
					
				this file is incremental, meaning it is constantly updated based on
				my next project requirements. it is not fully functional for all GPIO
				functions until specified otherwise.
				
				
				*************************************************************
				*				Made by: Hazem Shaaban Bakry				*
				*				github: HazemShaaban101						*
				*				Linkedin: hazemshaaban101					*
				*************************************************************
*************************************************************************************************/


#ifndef _GPIO_H_
#define _GPIO_H_


//===============================================================================================
//	important includes
//===============================================================================================

#include "ATmega32.h"		// MCU HEADER FILE: contains register addresses

//*****************************************************************************************************************************************
//*****************************************************************************************************************************************

//===============================================================================================
//	GPIO macro definitions
//===============================================================================================
//@ref GPIO_PIN_NUMBER
#define GPIO_PIN0				((uint16_t) 0x0000)	//pin 0 selected	
#define GPIO_PIN1				((uint16_t) 0x0001)	//pin 1 selected	
#define GPIO_PIN2				((uint16_t) 0x0002)	//pin 2 selected	
#define GPIO_PIN3				((uint16_t) 0x0003)	//pin 3 selected	
#define GPIO_PIN4				((uint16_t) 0x0004)	//pin 4 selected	
#define GPIO_PIN5				((uint16_t) 0x0005)	//pin 5 selected	
#define GPIO_PIN6				((uint16_t) 0x0006)	//pin 6 selected	
#define GPIO_PIN7				((uint16_t) 0x0007)	//pin 7 selected


//@ref GPIO_MODES
#define GPIO_MODE_IN_FLOATING				0x00
#define GPIO_MODE_IN_PU						0x01
#define GPIO_MODE_OUT_PP					0x02


// @ref GPIO_PIN_VALUE
 #define GPIO_LOW						0x00000000u
 #define GPIO_HIGH						0x00000001u
 
 
// ===============================================================================================
// GPIO APIs
// ===============================================================================================
void GPIO_Pin_Init(volatile GPIO_t * GPIOx, uint8_t PinNumber, uint8_t PinMode);
void GPIO_Port_DeInit(volatile GPIO_t * GPIOx);
uint8_t GPIO_Pin_Read(volatile GPIO_t * GPIOx, uint8_t PinNumber);
uint8_t GPIO_Port_Read(volatile GPIO_t * GPIOx);
void GPIO_Pin_Write(volatile GPIO_t * GPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_Port_Write(volatile GPIO_t * GPIOx, uint8_t value);
void GPIO_Pin_Toggle(volatile GPIO_t * GPIOx, uint8_t PinNumber);




#endif
