

/* this program adds two distances in feet and prints the final distance*/

#include <stdio.h>

struct S_distance
{
    int m_feet;
    float m_inch;
};

int main() {
    struct S_distance distance1, distance2;
    // scan first distance
    printf("Enter information for first distance\n");
    printf("Enter feet:");
    scanf("%d", &distance1.m_feet);
    printf("Enter Inch:");
    scanf("%f", &distance1.m_inch);

    // scan second distance
    printf("Enter information for second distance\n");
    printf("Enter feet:");
    scanf("%d", &distance2.m_feet);
    printf("Enter Inch:");
    scanf("%f", &distance2.m_inch);

    // add the two distances, no need to define another variable, we are going to overwrite an existing variable
    distance1.m_feet = distance1.m_feet + distance2.m_feet;
    distance1.m_inch = distance1.m_inch + distance2.m_inch;

    // this while loop ensures that even if user inputs inches more than 12(one foot) it will always be converted to feet
    while (distance1.m_inch > 12.0)
    {
        distance1.m_feet++;
        distance1.m_inch -= 12;
    }

    printf("Sum of distances = %d\' - %.1f\"\n", distance1.m_feet, distance1.m_inch);

    return 0;
}
