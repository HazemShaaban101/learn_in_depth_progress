#include <stdio.h>

int main() {
    printf("Enter three numbers:");
    float a, b, c;
    scanf("%f %f %f", &a, &b, &c);

    if (a > b && a > c)
    {
        printf("Largest number = %.2f\n", a);
    }
    else if (b > a && b > c)
    {
        printf("Largest number = %.2f\n", b);
    }
    else if (c > a && c > b)
    {
        printf("Largest number = %.2f\n", c);
    }
    else
    {
        printf("all three numbers are equal\n");
    }
    return 0;
}
