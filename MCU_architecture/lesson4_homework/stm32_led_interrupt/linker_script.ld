/***********************************************************************************************
*                                                                                              *
*                    THIS PROJECT IS MADE BY: Hazem Shaaban Bakry                              *
*        As part of learn-in-depth: master embedded systems by: keroles shnouda                *
*                                                                                              *
*                                                                                              *
*                                                                                              *
***********************************************************************************************/


ENTRY(RESET_handler)

MEMORY
{
	FLASH(RX): ORIGIN = 0x08000000, LENGTH = 128K
	SRAM(RWX): ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
	.TEXT :
	{
		*(.Vectors)
		. = 0x00000058 ;
		*(.GPIO_ISR)
		*(.text)
		*(.rodata)
		. = ALIGN(4) ;
		_TEXT_END = . ;
	}>FLASH
	
	.DATA :
	{
		_DATA_START = . ;
		*(.data)
		. = ALIGN(4) ;
		_DATA_END = . ;
	}>SRAM AT>FLASH
	
	.BSS :
	{
		_BSS_START = . ;
		*(.bss)
		. = ALIGN(4) ;
		_BSS_END = . ;
	}>SRAM
	_STACK_TOP = . + 0x1000 ;
	
}