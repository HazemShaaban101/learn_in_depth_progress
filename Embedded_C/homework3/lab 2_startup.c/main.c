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


// define base addresses
#define RCC_BASE		0x40021000
#define GPIOA_BASE		0x40010800


//define GPIO clock address
#define RCC_APB2ENR			*((vuint32_t *) (RCC_BASE + 0x18))


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


//define some variables for different sections to appear
int const CONSTANT[3];
int BSS[3];


void main(void){
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