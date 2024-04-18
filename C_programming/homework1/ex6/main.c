#include <stdio.h>

int main() {
    int a, b;
    printf("Enter value of a: ");
    scanf("%d", &a);
    printf("Enter value of b: ");
    scanf("%d", &b);

    int buffer = a;
    a = b;
    b = buffer;

    printf("After swapping, value of a = %d\n", a);
    printf("After swapping, value of b = %d\n", b);
    return 0;
}
