ENTRY(PRINT_EXIT_CODE)

MEMORY
{
	MEM (wrx) : ORIGIN = 0x00000000 , LENGTH = 64M
}

SECTIONS
{
	. = 0x00010000;
	.startup . :
	{
		startup.o(.text)
	}> MEM

	.text :
	{
		*(.text)
	}> MEM

	.rodata :
	{
		*(.rodata)
	}> MEM

	.data :
	{
		*(.data)
	}> MEM

	.bss :
	{
		*(.bss)
	}>MEM

	. = . + 0x1000;
	STACK_TOP = .;
}