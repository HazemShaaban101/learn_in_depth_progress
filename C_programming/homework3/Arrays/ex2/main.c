#include <stdio.h>

int main() {
    // get the number of elements from user
    int element_num;
    printf("Enter the number of data:");
    scanf("%d", &element_num);
    // make array size of user input
    float array[element_num];
    int i;
    for (i = 0; i < element_num; i++)
    {
        printf("%d. Enter number:", i + 1);
        scanf("%f", array + i);
    }

    float sum = 0;
    for (i = 0; i < element_num; i++)
    {
        // calculate sum of all elements inside array
        sum+= array[i];
    }
    // print out the average = sum / number of elements
    printf("Average = %.2f\n", sum / (float) element_num);
    return 0;
}
