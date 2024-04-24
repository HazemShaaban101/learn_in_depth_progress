#include <stdio.h>
int factorial(int x);

int main() {
    int x;

    // just wanted to try using goto, could have used a while loop instead
    label1:
    {
        // prompt user for positive input
        printf("enter a positive integer: ");
        scanf("%d", &x);
    }
    // if user input is negative, yell at him then goto label1
    if (x <= 0)
    {
        printf("I SAID POSITIVE!!!!\n");
        goto label1;
    }

    //printf the output of the factorial function
    printf("factorial of %d = %d\n", x, factorial(x));
    return 0;
}


// factorial function calls itself but with less x each time until it reaches end case which returns 1
// if return case is not met, it returns x * factorial of x - 1
int factorial (int x)
{
    if (x == 1)
    {
        return 1;
    }
    return x * factorial(x - 1);
}