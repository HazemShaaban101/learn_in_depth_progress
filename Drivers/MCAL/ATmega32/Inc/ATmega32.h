/************************************************************************************************
				This file is the MCU device header for ATmega32 devices
				this file include:
					- base address for each memory device
					- base address for each peripheral
					- peripheral registers
					- peripheral instances
					- clock managment macros
					- interrupt definitions
					- other useful MCU configuration macros
					
				this file is incremental, meaning it is constantly updated based on
				my next project requirements. it is not fully functional for all MCU
				peripherals until specified otherwise.
				
				
				*************************************************************
				*				Made by: Hazem Shaaban Bakry				*
				*				github: HazemShaaban101						*
				*				Linkedin: hazemshaaban101					*
				*************************************************************
*************************************************************************************************/


#ifndef _ATMEGA32_H_
#define _ATMEGA32_H_

//===============================================================================================
//	important includes
//===============================================================================================

#include <Stdlib.h>
#include <stdint.h>
#include <stdio.h>

//*****************************************************************************************************************************************
//*****************************************************************************************************************************************


//===============================================================================================
//	Memory base addresses
//===============================================================================================
#define SRAM						(0x60)


//===============================================================================================
//	Peripheral base addresses
//===============================================================================================

#define GPIOA_BASE						(0x39)
#define GPIOB_BASE						(0x36)
#define GPIOC_BASE						(0x33)
#define GPIOD_BASE						(0x30)




//*****************************************************************************************************************************************
//*****************************************************************************************************************************************

//===============================================================================================
//	Peripheral registers
//===============================================================================================

//GPIO
typedef struct
{
	volatile uint8_t PIN;
	volatile uint8_t DDR;
	volatile uint8_t PORT;
}GPIO_t;


//*****************************************************************************************************************************************
//*****************************************************************************************************************************************

//===============================================================================================
//	Peripheral instances
//===============================================================================================
#define GPIOA							((GPIO_t *) GPIOA_BASE)
#define GPIOB							((GPIO_t *) GPIOB_BASE)
#define GPIOC							((GPIO_t *) GPIOC_BASE)
#define GPIOD							((GPIO_t *) GPIOD_BASE)


#endif