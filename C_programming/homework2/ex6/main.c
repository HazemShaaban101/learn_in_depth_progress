#include <stdio.h>

int main() {
    printf("Enter an integer:");
    int a;
    scanf("%d", &a);
    int i, sum = 0;
    for (i = 0; i <= a; i++)
    {
        sum += i;
    }
    printf("Sum = %d\n", sum);
    return 0;
}
