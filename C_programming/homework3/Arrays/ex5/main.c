#include <stdio.h>

int main() {
    int element_number;
    printf("Enter no of elements:");
    scanf("%d", &element_number);

    int array[element_number];
    int i;
    for (i = 0; i < element_number; i++)
    {
        scanf("%d", &array[i]);
    }

    int search_for;
    printf("Enter the elements to be searched:");
    scanf("%d", &search_for);

    for (i = 0; i < element_number; i++)
    {
        if (array[i] == search_for)
        {
            printf("Number found at location = %d\n", i + 1);
            return 0;
        }
    }
    printf("element not found\n");
    return -1;
}
