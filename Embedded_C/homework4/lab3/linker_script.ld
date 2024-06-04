ENTRY(STARTUP_FUNCTION)

MEMORY
{
	FLASH (RX): ORIGIN = 0x00000000, LENGTH = 512M
	SRAM (WRX): ORIGIN = 0x20000000, LENGTH = 512M
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
		. = ALIGN(4) ;
		_DATA_END = . ;
	}>SRAM AT>FLASH
	
	.bss :
	{
		_BSS_START = . ;
		*(.bss)
		. = ALIGN(4) ;
		_BSS_END = . ;
	}>SRAM
	
}