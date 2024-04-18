#include <stdio.h>

int main() {
    printf("Enter an integer you want to check:");
    int a;
    scanf("%d", &a);

    if(a % 2)
    {
        printf("%d is odd\n", a);
    }
    else
    {
        printf("%d is even\n", a);
    }
    return 0;
}
