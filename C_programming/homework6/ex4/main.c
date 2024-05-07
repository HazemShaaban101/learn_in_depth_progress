#include <stdio.h>

int main()
{
    // get size of array, if it's lower than one or higher than 15 print error and ask again
    int size = 0;
    printf("Input the number of elements to store in the array (max 15):");
    while (!(size > 0 && size <= 15))
    {
        scanf("%d", &size);

        if (!(size > 0 && size <= 15))
        {
            printf("error, size of array invalid, enter a size between 1 and 15!:");
        }
    }

    // ask for elements of array by looping for the input size, incrementing the pointer to the array by one for each element
    printf("Input 5 number of elements in the array:\n");
    int i, arr[size], *ptr_to_arr = &arr[0];
    for (i = 0; i < size; i++)
    {
        printf("element - %d:", i + 1);
        scanf("%d", ptr_to_arr++);
    }

    // decrement pointer by one to point at last element of array
    i--, ptr_to_arr--;

    // print the element pointed to by pointer then decrement it
    printf("\nThe elements of array in reverse order are:\n");
    for (; i >= 0; i--)
    {
        printf ("element - %d: %d\n", i+1, *(ptr_to_arr--));
    }
    return 0;
}