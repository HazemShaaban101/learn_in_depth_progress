/***********************************************************************************************
*                                                                                              *
*                    THIS PROJECT IS MADE BY: Hazem Shaaban Bakry                              *
*        As part of learn-in-depth: master embedded systems by: keroles shnouda        	       *
*                                                                                              *
*        project description: this project is a bare-metal software for a blinking led         *
*        using stm32f103c6, everything is made by hand including source code, startup          *
*        linker script, and makefile                                                           *
*                                                                                              *
*                                                                                              *
***********************************************************************************************/


.global RESET_HANDLER

.section .Vectors
.word _STACK_TOP
.word RESET_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER
.word VECTOR_HANDLER







.section .text
RESET_HANDLER:
	bl main
	b .
.thumb_func
VECTOR_HANDLER:
	b RESET_HANDLER