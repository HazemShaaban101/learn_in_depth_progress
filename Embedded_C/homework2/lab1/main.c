#include "uart.h"

void PRINT_EXIT_CODE(void)
{
    int EXIT_CODE = main();
    UART_SEND_STRING("\nEXIT_CODE:");
    UART_SEND_CHAR('0');
}


int main(void)
{
    UART_SEND_STRING("Learn_in_depth: Hazem Shaaban bakry");
    return 0;
}