/************************************************************************************************
				This file is the GPIO driver header for stm32f103x8 devices
				this file include:
					- GPIO pin configuration struct (was made obsolete by separating pin output speed from the initialization function)
					- @ref GPIO_PIN_NUMBER
					- @ref GPIO_PIN_MODE
					- @ref GPIO_PIN_SPEED
					- @ref GPIO_PIN_VALUE
					- GPIO APIs
					
					
					
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

#include "stm32f103x8.h"		// MCU HEADER FILE: contains register addresses


//*****************************************************************************************************************************************
//*****************************************************************************************************************************************

//===============================================================================================
//	GPIO pin configuration struct
//===============================================================================================

typedef struct
{
	uint16_t	PinNumber;	// must be set to the corresponding value of the desired pin based on @ref GPIO_PIN_NUMBER
	uint8_t		PinMode;	// must be set to the corresponding value of desired pin mode based on @ref GPIO_PIN_MODE
	uint8_t		PinSpeed;	// must be set to the corresponding value of desired pin speed based on @ref GPIO_PIN_SPEED
}GPIO_PIN_CONFIG_t;




// ===============================================================================================
// GPIO macro references
// ===============================================================================================


//@ref GPIO_PIN_NUMBER
// #define GPIO_PIN0				((uint16_t) 0x0001)	//pin 0 selected	(0b 0000 0000 0000 0001)
// #define GPIO_PIN1				((uint16_t) 0x0002)	//pin 1 selected	(0b 0000 0000 0000 0010)
// #define GPIO_PIN2				((uint16_t) 0x0004)	//pin 2 selected	(0b 0000 0000 0000 0100)
// #define GPIO_PIN3				((uint16_t) 0x0008)	//pin 3 selected	(0b 0000 0000 0000 1000)
// #define GPIO_PIN4				((uint16_t) 0x0010)	//pin 4 selected	(0b 0000 0000 0001 0000)
// #define GPIO_PIN5				((uint16_t) 0x0020)	//pin 5 selected	(0b 0000 0000 0010 0000)
// #define GPIO_PIN6				((uint16_t) 0x0040)	//pin 6 selected	(0b 0000 0000 0100 0000)
// #define GPIO_PIN7				((uint16_t) 0x0080)	//pin 7 selected	(0b 0000 0000 1000 0000)
// #define GPIO_PIN8				((uint16_t) 0x0100)	//pin 8 selected	(0b 0000 0001 0000 0000)
// #define GPIO_PIN9				((uint16_t) 0x0200)	//pin 9 selected	(0b 0000 0010 0000 0000)
// #define GPIO_PIN10				((uint16_t) 0x0400)	//pin 10 selected	(0b 0000 0100 0000 0000)
// #define GPIO_PIN11				((uint16_t) 0x0800)	//pin 11 selected	(0b 0000 1000 0000 0000)
// #define GPIO_PIN12				((uint16_t) 0x1000)	//pin 12 selected	(0b 0001 0000 0000 0000)
// #define GPIO_PIN13				((uint16_t) 0x2000)	//pin 13 selected	(0b 0010 0000 0000 0000)
// #define GPIO_PIN14				((uint16_t) 0x4000)	//pin 14 selected	(0b 0100 0000 0000 0000)
// #define GPIO_PIN15				((uint16_t) 0x8000)	//pin 15 selected	(0b 1000 0000 0000 0000)
// #define GPIO_ALLPINS			((uint16_t) 0xFFFF)	//all pins selected	(0b 1111 1111 1111 1111)

#define GPIO_PIN0				((uint16_t) 0x0000)	//pin 0 selected	
#define GPIO_PIN1				((uint16_t) 0x0001)	//pin 1 selected	
#define GPIO_PIN2				((uint16_t) 0x0002)	//pin 2 selected	
#define GPIO_PIN3				((uint16_t) 0x0003)	//pin 3 selected	
#define GPIO_PIN4				((uint16_t) 0x0004)	//pin 4 selected	
#define GPIO_PIN5				((uint16_t) 0x0005)	//pin 5 selected	
#define GPIO_PIN6				((uint16_t) 0x0006)	//pin 6 selected	
#define GPIO_PIN7				((uint16_t) 0x0007)	//pin 7 selected	
#define GPIO_PIN8				((uint16_t) 0x0008)	//pin 8 selected	
#define GPIO_PIN9				((uint16_t) 0x0009)	//pin 9 selected	
#define GPIO_PIN10				((uint16_t) 0x000A)	//pin 10 selected	
#define GPIO_PIN11				((uint16_t) 0x000B)	//pin 11 selected	
#define GPIO_PIN12				((uint16_t) 0x000C)	//pin 12 selected	
#define GPIO_PIN13				((uint16_t) 0x000D)	//pin 13 selected	
#define GPIO_PIN14				((uint16_t) 0x000E)	//pin 14 selected	
#define GPIO_PIN15				((uint16_t) 0x000F)	//pin 15 selected	



// @ref GPIO_PIN_MODE
 // 0: Analog mode
 // 1: Floating input (reset state)
 // 2: Input with pull-up
 // 3: Input with pull-down
 // 4: General purpose output push-pull
 // 5: General purpose output Open-drain
 // 6: Alternate function output Push-pull
 // 7: Alternate function output Open-drain
 // 8: Alternate function input
 
 #define GPIO_MODE_ANALOG				0x00000000u		// 0: Analog mode
 #define GPIO_MODE_IN_FLOATING			0x00000001u		// 1: Floating input (reset state)
 #define GPIO_MODE_IN_PU				0x00000002u		// 2: Input with pull-up
 #define GPIO_MODE_IN_PD				0x00000003u		// 3: Input with pull-down
 #define GPIO_MODE_OUT_PP				0x00000004u		// 4: General purpose output push-pull
 #define GPIO_MODE_OUT_OD				0x00000005u		// 5: General purpose output Open-drain
 #define GPIO_MODE_AFOUT_PP				0x00000006u		// 6: Alternate function output Push-pull
 #define GPIO_MODE_AFOUT_OD				0x00000007u		// 7: Alternate function output Open-drain
 
 #define GPIO_MODE_AFI					0x00000008u		// 8: Alternate function input
 
 
// @ref GPIO_PIN_SPEED
 // 1: Output mode, max speed 10 MHz.
 // 2: Output mode, max speed 2 MHz.
 // 3: Output mode, max speed 50 MHz.
 
 #define GPIO_SPEED_10M					0x00000001u	 // 1: Output mode, max speed 10 MHz.
 #define GPIO_SPEED_2M					0x00000002u	 // 2: Output mode, max speed 2 MHz.
 #define GPIO_SPEED_50M					0x00000003u	 // 3: Output mode, max speed 50 MHz.
 
 
 // @ref GPIO_PIN_VALUE
 #define GPIO_LOW						0x00000000u
 #define GPIO_HIGH						0x00000001u
 
 
 
//*****************************************************************************************************************************************
//*****************************************************************************************************************************************


// ===============================================================================================
// GPIO APIs
// ===============================================================================================

void GPIO_Pin_Init(volatile GPIO_t * GPIOx, uint8_t PinNumber, uint8_t PinMode);
void GPIO_Port_DeInit(volatile GPIO_t * GPIOx);
uint8_t GPIO_Pin_Read(volatile GPIO_t * GPIOx, uint16_t PinNumber);
uint16_t GPIO_Port_Read(volatile GPIO_t * GPIOx);
void GPIO_Pin_Write(volatile GPIO_t * GPIOx, uint16_t PinNumber, uint8_t value);
void GPIO_Port_Write(volatile GPIO_t * GPIOx, uint16_t value);
void GPIO_Pin_Toggle(volatile GPIO_t * GPIOx, uint16_t PinNumber);
void GPIO_Pin_Output_Speed(volatile GPIO_t * GPIOx, uint8_t PinNumber, uint8_t PinSpeed);


#endif