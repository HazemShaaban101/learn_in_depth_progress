#include <stdio.h>
#include <math.h>
#define PI 3.14159
#define AREA(R) (pow(R, 2)*PI)

int main() {
    printf("Enter the radius:");
    float radius;
    scanf("%f", &radius);
    float area = AREA(radius);
    printf("Area = %.2f\n", area);
    return 0;
}
