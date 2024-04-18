#include <stdio.h>

int main() {
    printf("Enter a number:");
    float a;
    scanf("%f", &a);

    if (a > 0) printf("%.2f is positive\n", a);
    else if (a < 0) printf("%.2f is negative\n", a);
    else if (a == 0) printf("You entered zero\n");
    return 0;
}
