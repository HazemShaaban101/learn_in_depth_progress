/***********************************************************************************************
*                                                                                              *
*                    THIS PROJECT IS MADE BY: Hazem Shaaban Bakry                              *
*        As part of learn-in-depth: master embedded systems by: keroles shnouda                *
*                                                                                              *
*        project description: this project is a bare-metal software for a blinking led         *
*        using stm32f103c6, everything is made by hand including source code, startup          *
*        linker script, and makefile                                                           *
*                                                                                              *
*                                                                                              *
***********************************************************************************************/


#include <stdint.h>
typedef volatile uint32_t vuint32_t;


//define GPIO address
#define GPIOA_BASE		0x40010800






//struct of CRH to choose pinmode of pin 13
typedef union{
	vuint32_t all_pins;
	struct{
		vuint32_t RESERVED:20;
		vuint32_t pin13_mode:4;
	}m_pins;
}CRH_r;


//struct of ODR to toggle individual pins
typedef union{
	vuint32_t all_pins;
	struct{
		vuint32_t pin0:1;
		vuint32_t pin1:1;
		vuint32_t pin2:1;
		vuint32_t pin3:1;
		vuint32_t pin4:1;
		vuint32_t pin5:1;
		vuint32_t pin6:1;
		vuint32_t pin7:1;
		vuint32_t pin8:1;
		vuint32_t pin9:1;
		vuint32_t pin10:1;
		vuint32_t pin11:1;
		vuint32_t pin12:1;
		vuint32_t pin13:1;
	}m_pins;
}ODR_r;




// define global pointers to CRH register and ODR register responsible for GPIOA_BASE
volatile CRH_r *GPIOA_CRH = (volatile CRH_r *) (GPIOA_BASE + 0x04);
volatile ODR_r *GPIOA_ODR = (volatile ODR_r *) (GPIOA_BASE + 0x0C);



// requirements:
//		APB1 clock speed is 4 MHz
//		APB2 clock speed is 2 MHz
//		AHB clock speed is 8 MHz
//		SYSCLK clock speed is 8 MHz
//		only use HSI clock

// registers
#define RCC_BASE		0x40021000
#define RCC_CR			*((uint32_t *) (RCC_BASE + 0x00))	// clock control register
#define RCC_CFGR		*((uint32_t *) (RCC_BASE + 0x04))	// clock config register
#define RCC_APB2ENR		*((vuint32_t *) (RCC_BASE + 0x18))	// APB2ENR enable peripherals


void clock_init()
{
	// HSI is set by default as the default clock
	
	// SW reg is set by dafualt to take HSI as SYSCLK
	// AHB prescaler is set to 1 by default
	// APB1 prescaler is set to 1 by default, we need to change it to 2
	RCC_CFGR &= 0xFFFFF8FF;
	RCC_CFGR |= 4 << 8;
	
	// APB1 prescaler is set to 1 by default, we need to change it to 4
	RCC_CFGR &= 0xFFFFC7FF;
	RCC_CFGR |= 5 << 11;
	
}

// main function
void main(void){
	clock_init(); // initialize clocks for entire system
	
	// start the clock for GPIO
	RCC_APB2ENR |= 1<<2;
	
	
	// set pin 13 pinmode to output
	GPIOA_CRH->m_pins.pin13_mode = 2;
	
	//forever loop
	while(69)
	{
		GPIOA_ODR->m_pins.pin13 ^= 1;
		for (int i = 0; i < 5000; i++);
	}
}