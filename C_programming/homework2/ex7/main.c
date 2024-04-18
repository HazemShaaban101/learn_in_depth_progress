#include <stdio.h>

int main() {
    printf("Enter an integer:");
    int a;
    scanf("%d", &a);
    if (a < 0)
    {
        printf("Error!!! Factorial of negative number doesn't exist.\n");
        return -1;
    }

    int factorial = 1;
    int i;
    for (i = 1; i <= a; i++)
    {
        factorial *= i;
    }

    printf("Factorial = %d\n", factorial);
    return 0;
}
