// this file is made by hazem shaaban bakry
// as part of course work of learn in depth: mastering embedded systems diploma
// startup file for stm32f103c6
#include <stdint.h>

// extern functions and values
extern int main();
extern uint32_t _STACK_TOP;
extern uint32_t _TEXT_END;
extern uint32_t _DATA_START;
extern uint32_t _DATA_END;
extern uint32_t _BSS_START;
extern uint32_t _BSS_END;





// reset handler, the system entry point
// it initializes the system before running main
void RESET_handler()
{
	// copy data from flash to ram
	unsigned char * SOURCE = (unsigned char *) &_TEXT_END;
	unsigned char * DEST = (unsigned char *) &_DATA_START;
	int size = (unsigned char *) &_DATA_END - (unsigned char *) &_DATA_START;
	for (int i = 0; i < size; i++)
	{
		*DEST++ = *SOURCE++;
	}
	
	// initialize bss section to zero in ram
	size = (unsigned char *) &_BSS_END - (unsigned char *) &_BSS_START;
	DEST = (unsigned char *) &_BSS_START;
	for (int i = 0; i < size; i++)
	{
		*DEST++ = 0;
	}
	
	// RUN MAIN
	main();
}
// dummy function for vector table to point at
void dummy_function()
{
	RESET_handler;
}

// vector function prototypes
void NMI_handler() __attribute__((weak, alias("dummy_function")));;
void HardFault_handler() __attribute__((weak, alias("dummy_function")));;
void MEM_fault_handler() __attribute__((weak, alias("dummy_function")));;
void BusFault_handler() __attribute__((weak, alias("dummy_function")));;
void UsageFault_handler() __attribute__((weak, alias("dummy_function")));;



// vector table
volatile uint32_t vector_table[] __attribute__((section(".Vectors"))) = 
{
	(volatile uint32_t) &_STACK_TOP,
	(volatile uint32_t) RESET_handler,
	(volatile uint32_t) NMI_handler,
	(volatile uint32_t) HardFault_handler,
	(volatile uint32_t) MEM_fault_handler,
	(volatile uint32_t) BusFault_handler,
	(volatile uint32_t) UsageFault_handler	
};

void EXTI0_handler() __attribute__((weak, alias("dummy_function")));;
void EXTI1_handler() __attribute__((weak, alias("dummy_function")));;
void EXTI2_handler() __attribute__((weak, alias("dummy_function")));;
void EXTI3_handler() __attribute__((weak, alias("dummy_function")));;
void EXTI4_handler() __attribute__((weak, alias("dummy_function")));;

volatile uint32_t vector_table2[] __attribute__((section(".GPIO_ISR"))) = 
{
	(volatile uint32_t) EXTI0_handler,
	(volatile uint32_t) EXTI1_handler,
	(volatile uint32_t) EXTI2_handler,
	(volatile uint32_t) EXTI3_handler,
	(volatile uint32_t) EXTI4_handler,
};