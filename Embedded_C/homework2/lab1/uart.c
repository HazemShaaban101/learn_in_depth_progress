#include "uart.h"

// these are the functions to send anything to terminal using UART0

#define UART0_BASE      0x101f1000
#define UART0DR         *((volatile unsigned int*) UART0_BASE)


void UART_SEND_CHAR(char input_char)
{
    UART0DR = (unsigned int) input_char;
}

void UART_SEND_INT(int input_int)
{   
    UART0DR = input_int;
}

void UART_SEND_STRING(char *string)
{
    while(*string)
    {
        // increment pointer but dereference old pointer
        UART0DR = (unsigned int) *string++;
    }
}