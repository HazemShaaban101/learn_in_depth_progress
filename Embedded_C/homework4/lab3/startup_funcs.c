#include <stdint.h>

extern uint32_t _TEXT_END;
extern uint32_t _DATA_START;
extern uint32_t _DATA_END;
extern uint32_t _BSS_START;
extern uint32_t _BSS_END;
extern void main(void);




void DATA_SECTION_COPY(void)
{
	// destination is the linker_script calculated area in SRAM for data section to sit in
	unsigned char * DESTINATION = (unsigned char *) (&_DATA_START);
	// destination is the linker_script calculated area in FLASH for data section to start
	unsigned char * SOURCE = (unsigned char *) (&_TEXT_END);
	//uint32_t SIZE = (unsigned char *) (&_DATA_END) - (unsigned char *) (&_DATA_START);			*NOT NEEDED
	
	// while destination <= _DATA_END keep copying from source to destination
	while(DESTINATION < (unsigned char *) &_DATA_END)
		{
			*DESTINATION++ = *SOURCE++;
		}
		
}


void BSS_INIT(void)
{
	// destination is the linker_script calculated area in SRAM for BSS section to sit in
	unsigned char * DESTINATION = (unsigned char *) (&_BSS_START);
	//uint32_t SIZE = (unsigned char *) (&_BSS_END) - (unsigned char *) (&_BSS_START);				*NOT NEEDED
	
	// while destination <= _DATA_END keep copying from source to destination
	while(DESTINATION < (unsigned char *) &_BSS_END)
		{
			*DESTINATION++ = 0;
		}
}


// this function calls data copying function, then bss initialization function, then starts program by calling main
void STARTUP_FUNCTION()
{
	DATA_SECTION_COPY();
	BSS_INIT();
	main();
}




// dummy function for all vectors to initially point to
void VECTOR_HANDLER(void)
{
	return;
}





void N_HANDLER() __attribute__((weak, alias("VECTOR_HANDLER")));;
void H_FAULT_HANDLER() __attribute__((weak, alias("VECTOR_HANDLER")));;
void MM_FAULT_HANDLER() __attribute__((weak, alias("VECTOR_HANDLER")));;

// vectors section
void (*VECTORS[])()	__attribute__((section(".Vectors"))) = 
{
	(void (*)())				((unsigned char *) &_BSS_END + 1024),
								STARTUP_FUNCTION,
								N_HANDLER,
								H_FAULT_HANDLER,
								MM_FAULT_HANDLER
};





