#include <stdio.h>
int power(int, int);

int main() {
    int a, b = -1;

    //prompt user for base input
    printf("Enter base number:");
    scanf("%d", &a);

    //prompt user for power number(has to be positive)
    while (b < 0)
    {
        printf("Enter power number(positive integer):");
        scanf("%d", &b);
    }


    printf("%d ^ %d = ", a, b);
    printf("%d\n", power(a, b));
    return 0;
}

int power(int a, int b)
{
    if (b == 0)
    {
        return 1;
    }

    return a * power(a, --b);
}
