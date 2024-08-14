// made by hazem shaaban bakry
// as part of learn in depth: mastering embedded systems


void init_function(void)
{
	// first i need to enable clock for GPIO through RCC APB2ENR register
	*(unsigned long *) 0x40021018 |= 0b101;
	
	// set port A pin 5 to input pull down mode and pin 7 to output mode
	*(unsigned long *) 0x40010800 &= 0x0FFFF0FF;
	*(unsigned long *) 0x40010800 |= 0x24444444;
	
	// turn on GPIOA interrupts
	// To configure the 20 lines as interrupt sources, use the following procedure:
 // • Configure the mask bits of the 20 Interrupt lines (EXTI_IMR)
	*(unsigned long *) 0x40010400 |= 1 << 2;
 // • Configure the Trigger Selection bits of the Interrupt lines (EXTI_RTSR and EXTI_FTSR)
	//*(unsigned long *) 0x40010408 |= 1 << 2;	// rising edge
	*(unsigned long *) 0x4001040C |= 1 << 2;	// falling edge
 // • Configure the enable and mask bits that control the NVIC IRQ channel mapped to the 
// External Interrupt Controller (EXTI) so that an interrupt coming from one of the 20 lines 
// can be correctly acknowledged.
	*(unsigned long *) 0xE000E100 |= 1 << 8;
}

	
	
	
	

int main(void)
{
	init_function();
	while(1)
	{
		continue;
	}
}


void EXTI2_handler()
{
	*(unsigned long *) 0x4001080C ^= 1 << 7;
	*(unsigned long *) 0x40010414 |= (1 << 2);
}