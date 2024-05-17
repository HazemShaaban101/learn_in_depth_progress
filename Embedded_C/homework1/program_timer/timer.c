#include "timer.h"

void dummy_function()
{
    printf("=");
}

void program_start()
{
    printf("===========start of program===========\n");
    static clock_t CLK;
    CLK = clock();
}

void program_end()
{
    static clock_t CLK;
    double runtime = (clock() - (double) CLK) / CLOCKS_PER_SEC;
    printf("program runtime = %lf\n", runtime);
}