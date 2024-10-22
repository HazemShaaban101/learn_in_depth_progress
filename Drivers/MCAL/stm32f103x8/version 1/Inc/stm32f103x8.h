/************************************************************************************************
				This file is the MCU device header for stm32f103x8 devices
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
#ifndef _STM32F103X8_H_
#define _STM32F103X8_H_


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

#define FLASH_BASE											0x08000000UL
#define SYSTEM_MEMORY_BASE									0x1FFFF000UL
#define SRAM_BASE											0x20000000UL
#define PERIPHERALS_BASE									0x40000000UL
#define CORTEX_M3_INTERNAL_PERIPHERALS_BASE					oxE0000000UL

//*****************************************************************************************************************************************
//*****************************************************************************************************************************************

//===============================================================================================
//	AHB peripheral base addresses
//===============================================================================================

// RCC
#define RCC_BASE											0x40021000UL

//===============================================================================================
//	APB1 peripheral base addresses
//===============================================================================================

// empty

//===============================================================================================
//	APB2 peripheral base addresses
//===============================================================================================

// GPIO
#define GPIOA_BASE											0x40010800UL
#define GPIOB_BASE											0x40010C00UL
#define GPIOC_BASE											0x40011000UL
#define GPIOD_BASE											0x40011400UL
#define GPIOE_BASE											0x40011800UL


// EXTI
#define EXTI_BASE											0x40010400UL


// AFIO
#define AFIO_BASE											0x40010000UL





//*****************************************************************************************************************************************
//*****************************************************************************************************************************************

//===============================================================================================
//	Peripheral registers
//===============================================================================================

//GPIO	(General purpose input/output)
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_t;

//AFIO	(Alternate functions input/output)
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RESERVED;
	volatile uint32_t MAPR2;
}AFIO_t;

//EXTI (External interrupts)
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_t;

// RCC	(Reset and clock control)
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_t;


//*****************************************************************************************************************************************
//*****************************************************************************************************************************************

//===============================================================================================
//	Peripheral instances
//===============================================================================================

//GPIO
#define GPIOA								((volatile GPIO_t *) GPIOA_BASE)
#define GPIOB								((volatile GPIO_t *) GPIOB_BASE)
#define GPIOC								((volatile GPIO_t *) GPIOC_BASE)
#define GPIOD								((volatile GPIO_t *) GPIOD_BASE)
#define GPIOE								((volatile GPIO_t *) GPIOE_BASE)


// EXTI
#define EXTI								((volatile EXTI_t *) EXTI_BASE)

// AFIO
#define AFIO								((volatile AFIO_t *) AFIO_BASE)

// RCC
#define RCC									((volatile RCC_t *) RCC_BASE)



//*****************************************************************************************************************************************
//*****************************************************************************************************************************************

//===============================================================================================
//	quick clock management macros
//===============================================================================================

// GPIO
#define GPIOA_CLK_EN()						(RCC->APB2ENR |= 1 << 2)
#define GPIOB_CLK_EN()						(RCC->APB2ENR |= 1 << 3)
#define GPIOC_CLK_EN()						(RCC->APB2ENR |= 1 << 4)
#define GPIOD_CLK_EN()						(RCC->APB2ENR |= 1 << 5)
#define GPIOE_CLK_EN()						(RCC->APB2ENR |= 1 << 6)

// AFIO
#define AFIO_CLK_EN()						(RCC->APB2ENR |= 1 << 0)


//*****************************************************************************************************************************************
//*****************************************************************************************************************************************



#endif