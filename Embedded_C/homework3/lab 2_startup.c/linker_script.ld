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



ENTRY(RESET_HANDLER)

MEMORY
{
	FLASH (RX): ORIGIN = 0x08000000 , LENGTH = 128K
	SRAM (WRX): ORIGIN = 0x20000000 , LENGTH = 20K
}


SECTIONS
{	
	.text :
	{
		*(.Vectors)
		*(.text)
		*(.rodata)
		. = ALIGN(4) ;
		_TEXT_END = . ;
	}>FLASH
	
	.data :
	{
		_DATA_START = . ;
		*(.data)
		. = ALIGN(4);
		_DATA_END = . ;
	}>FLASH
	
	.bss :
	{
		_BSS_START = . ;
		*(.bss)
		. = ALIGN(4);
		_BSS_END = . ;
	}>SRAM
	_STACK_TOP = . + 0x1000;
}