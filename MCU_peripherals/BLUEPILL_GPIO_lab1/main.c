// made by hazem shaaban bakry
// as part of learn in depth: mastering embedded systems

#define GPIOA_BASE 		0x40010800
#define GPIOB_BASE 		0x40010C00

#define GPIOA_IDR	(*(unsigned long *) (GPIOA_BASE + 0x8))
#define GPIOB_IDR	(*(unsigned long *) (GPIOB_BASE + 0x8))

#define GPIOA_ODR	(*(unsigned long *) (GPIOA_BASE + 0xC))
#define GPIOB_ODR	(*(unsigned long *) (GPIOB_BASE + 0xC))


void init_function(void)
{
	// first i need to enable clock for GPIOA and GPIOB through RCC APB2ENR register
	*(unsigned long *) 0x40021018 |= 0b1100;
	
	// set port A pin 1 and pin 13 as floating input(Reset state but we will code it for revision)
	*(unsigned long *) (GPIOA_BASE + 0x0) &= 0x00000000;
	*(unsigned long *) (GPIOA_BASE + 0x0) |= 0x44444444;
	*(unsigned long *) (GPIOA_BASE + 0x4) &= 0x00000000;
	*(unsigned long *) (GPIOA_BASE + 0x4) |= 0x44444444;
	
	// set port B pin 1 and pin 13 as open - drain output
	*(unsigned long *) (GPIOB_BASE + 0x0) &= 0xFFFFFF0F;
	*(unsigned long *) (GPIOB_BASE + 0x0) |= 0x00000050;
	*(unsigned long *) (GPIOB_BASE + 0x4) &= 0xFF0FFFFF;
	*(unsigned long *) (GPIOB_BASE + 0x4) |= 0x00500000;
	

}

// delay function
void DELAY_FUNC(unsigned int x)
{
	for (unsigned int i = 0; i < x; i++)
	{
		for (unsigned int j = 0; j < 255; j++);
	}
}

int main(void)
{
	init_function();
	while(1)
	{
		// checks if GPIOA pin 1 is low (button pressed because of PUR)
		if ((GPIOA_IDR & 1 << 1) == 0)
		{
			// toggles led
			GPIOB_ODR ^= (1<<1);
			// then enters a loop until the button is unpressed, this is bad design because it stops the entire program,
			// a better approach would be to add a variable in main before the while loop that holds the last value of ODR
			while ((GPIOA_IDR & 1 << 1) == 0);
		}
		// checks if GPIOA pin 13 is HIGH (button pressed because of PDR)
		if ((GPIOA_IDR & 1 << 13) > 0)
		{
			// toggles led
			GPIOB_ODR ^= (1<<13);
			DELAY_FUNC(400);
		}
		
	}
}
