/*
 * led_interrupt.c
 *
 * Created: 8/12/2024 10:45:41 PM
 * Author : Hazem Shaaban Bakry
 * as part of learn in depth course work
 */ 

#define F_CPU 1000000ul								// Crucial for the delay function
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// registers
#define PORTD_r		(*(unsigned long *) 0x32)		// controls the state of pins in port D
#define PORTB_r		(*(unsigned long *) 0x38)		// controls the state of pins in port B

#define DDRD_r		(*(unsigned long *) 0x31)		// controls the direction of pins in port D
#define DDRB_r		(*(unsigned long *) 0x37)		// controls the direction of pins in port B

#define GICR_r		(*(unsigned long *) 0x5B)		// controls individual interrupt status
#define MCUCR_r		(*(unsigned long *) 0x55)		// interrupt 0, 1 sense control
#define MCUCSR_r	(*(unsigned long *) 0x54)		// Interrupt Sense Control 2	

void init_func()
{
	
	DDRD_r = 0b111 << 5;				// turns on bits 5, 6, 7 in the register, causing corresponding pins to be directed as output
	
	MCUCR_r |= 0b1101;					// sets interrupt 0 to detect all logical changes, and interrupt 1 to detect rising edge
	MCUCSR_r &= ~(1 << 6);				// sets interrupt 2 to detect falling edge
	GICR_r |= 0b111 << 5;				// turn on individual interrupts
	sei();								// turns on global interrupt mask
	
	
	
}

// interrupt 0 function vector
ISR(INT0_vect)
{
	PORTD_r |= 1 << 5;	// turn on pin 5 port D
	_delay_ms(1000);
}

// interrupt 1 function vector
ISR(INT1_vect)
{
	PORTD_r |= 1 << 6;	// turn on pin 6 port D
	_delay_ms(1000);
}

// interrupt 2 function vector
ISR(INT2_vect)
{
	PORTD_r |= 1 << 7;	// turn on pin 7 port D
	_delay_ms(1000);
}

int main(void)
{
    init_func();
    while (1) 
    {
		PORTD_r &= ~(0xFF);	// turn off all pins in port D
		_delay_ms(1000);
    }
}

