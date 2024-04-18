

/*simple calculator program*/

#include <stdio.h>

int main() {
    printf("Enter operator either + or - or * or /:");
    char operator;
    scanf("%c", &operator);
    float a, b;
    printf("enter two operands:");
    scanf("%f %f", &a, &b);
    switch(operator)
    {
        case '+':
            printf("%.2f %c %.2f = %.2f\n", a, operator, b, a + b);
            break;
        case '-':
            printf("%.2f %c %.2f = %.2f\n", a, operator, b, a - b);
            break;
        case '*':
            printf("%.2f %c %.2f = %.2f\n", a, operator, b, a * b);
            break;
        case '/':
            printf("%.2f %c %.2f = %.2f\n", a, operator, b, a / b);
            break;
        default:
            printf("wrong operator\n");
            break;
    }
    return 0;
}
