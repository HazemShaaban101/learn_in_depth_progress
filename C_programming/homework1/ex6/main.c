#include <stdio.h>

int main() {
    float a, b;
    printf("Enter value of a:");
    scanf("%f", &a);
    printf("Enter value of b:");
    scanf("%f", &b);

    float buffer = a;
    a = b;
    b = buffer;

    printf("After swapping, value of a = %.3f\n", a);
    printf("After swapping, value of b = %.3f\n", b);
    return 0;
}
