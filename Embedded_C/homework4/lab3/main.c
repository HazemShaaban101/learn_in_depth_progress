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




// define base addresses of peripherals and modules
#define SYSCTL_base 			0x400FE000
#define GPIOF_base				0x40025000

// define pointer to the bits that enable GPIO port F
vuint32_t * GPIOF_ENABLE = (vuint32_t *) (SYSCTL_base + 0x108);

// define array to manipulate specific bits

typedef struct{
	uint32_t pin0:1;
	uint32_t pin1:1;
	uint32_t pin2:1;
	uint32_t pin3:1;
	uint32_t pin4:1;
	uint32_t pin5:1;
	uint32_t pin6:1;
	uint32_t RESERVED:26;
}BIT_MANIPULATION_r;


// array of bits to enable specific pins
volatile BIT_MANIPULATION_r * GPIOF_DEN = (volatile BIT_MANIPULATION_r *) (GPIOF_base + 0x51C);

// array of bits to change pin direction
volatile BIT_MANIPULATION_r * GPIOF_DIR = (volatile BIT_MANIPULATION_r *) (GPIOF_base + 0x400);

// array of bits to change pin data
volatile BIT_MANIPULATION_r * GPIOF_DATA = (volatile BIT_MANIPULATION_r *) (GPIOF_base + 0x3FC);



void main(void)
{
	// enable GPIO port F
	*GPIOF_ENABLE = 0x20;
	//wait a delay for gpio port to start
	for (uint32_t i = 0; i < 200; i++);
	
	// enable pin 3 of port F
	GPIOF_DEN->pin3 = 1;
	
	// direction of pin 3 is output
	GPIOF_DIR->pin3 = 1;
	
	// loop and toggle pin on and off
	while (69)
	{
		GPIOF_DATA->pin3 ^= 1;
		for (uint32_t i = 0; i < 200000; i++);
	}
}