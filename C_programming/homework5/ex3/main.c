
/*this program sums two complex numbers*/


#include <stdio.h>

struct S_complex
{
    float m_real;
    float m_imaginary;
};

int main()
{
    // define two complex number struct variables
    struct S_complex number1, number2;

    // scan for first complex number
    printf("For 1st complex number\n");
    printf("Enter real and imaginary respectively:");
    scanf("%f %f", &number1.m_real, &number1.m_imaginary);

    // scan for second complex number
    printf("For 2nd complex number\n");
    printf("Enter real and imaginary respectively:");
    scanf("%f %f", &number2.m_real, &number2.m_imaginary);

    // print the result
    printf("Sum = %.1f + %.1fi", number1.m_real + number2.m_real, number1.m_imaginary + number2.m_imaginary);
    return 0;
}
