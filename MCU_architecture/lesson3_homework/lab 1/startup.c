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

// define linker symbols

extern unsigned int _STACK_TOP;
extern unsigned int _TEXT_END;
extern unsigned int _DATA_START;
extern unsigned int _DATA_END;
extern unsigned int _BSS_START;
extern unsigned int _BSS_END;


extern void main(void);

void RESET_HANDLER(void)
{
	// copy data section to ram
	//unsigned int SIZE = (unsigned char *) &_DATA_END - (unsigned char *) &_DATA_START;			NO LONGER USED
	unsigned char *SOURCE = (unsigned char *) &_TEXT_END;
	unsigned char *DESTINATION = (unsigned char *) &_DATA_START;
	while (DESTINATION < (unsigned char *) &_DATA_END)
	{
		*DESTINATION++ = *SOURCE++;
	}
	
	// initialize bss section in ram
	//SIZE = (unsigned char *) &_BSS_END - (unsigned char *) &_BSS_START;							NO LONGER USED
	DESTINATION = (unsigned char *) &_BSS_START;
	while (DESTINATION < (unsigned char *) &_BSS_END)
	{
		*DESTINATION++ = 0;
	}
	
	//call main function
	main();
}


// default handler, any vector table handler will execute this vector handler unless it was defined by user
void VECTOR_HANDLER(void)
{
	RESET_HANDLER();
}

void NMI_HANDLER(void)__attribute__((weak, alias("VECTOR_HANDLER")));;
void BUS_FAULT_HANDLER(void)__attribute__((weak, alias("VECTOR_HANDLER")));;
void H_FAULT_HANDLER(void)__attribute__((weak, alias("VECTOR_HANDLER")));;



//vector section
volatile uint32_t vectors[] __attribute__((section(".Vectors"))) = {
	(uint32_t)	&_STACK_TOP,
	(uint32_t)	&RESET_HANDLER,
	(uint32_t)	&NMI_HANDLER,
	(uint32_t)	&BUS_FAULT_HANDLER,
	(uint32_t)	&H_FAULT_HANDLER
};