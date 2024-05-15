
/************************************************************************
 * 					BLINKING LED (MACRO APPROACH)						*
 * 						MADE BY: Hazem Shaaban							*
 * 			For master embedded systems diploma by keroles shnouda		*
 *																		*
 ************************************************************************/


// defining volatile unsigned int of 32 bits
#include <stdint.h>
typedef volatile uint32_t vuint32_t;

// defining base addresses
#define RCC_BASE 			0x40021000
#define GPIOA_BASE 			0x40010800

//defining register addresses
#define RCC_APB2ENR 		*((vuint32_t *) (RCC_BASE + 0x18))
#define GPIOA_CRH			*((vuint32_t *) (GPIOA_BASE + 0x04))
#define GPIOA_ODR			*((vuint32_t *) (GPIOA_BASE + 0x0C))

//main function, do once
int main(void)
{
	//enable RCC_APB2ENR, which enables clock for GPIO
	RCC_APB2ENR |= 1<<2;

	//set GPIOA_CRH pin 13 to output
	GPIOA_CRH &= 0xff0fffff;
	GPIOA_CRH |= 0x00200000;


    /* Loop forever */
	for(;;)
	{
		// this will toggle pin 13, then wait for a delay
		GPIOA_ODR ^= 1<<13;
		for (int i = 0; i < 50000; i++);
	}
}
