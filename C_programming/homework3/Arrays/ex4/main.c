#include <stdio.h>

int main() {
    int array[100];
    printf("Enter number of elements:");
    int element_number;
    scanf("%d", &element_number);
    int i;
    for (i = 0; i < element_number; i++)
    {
        scanf("%d", &array[i]);
    }

    printf("Enter the element to be inserted: ");
    int new_element;
    scanf("%d", &new_element);
    int location_of_new_element;
    scanf("%d", &location_of_new_element);
    location_of_new_element--;

    for (i = element_number - 1; i >= location_of_new_element; i--)
    {
        array[i + 1] = array[i];
    }
    array[location_of_new_element] = new_element;
    element_number++;
    fflush(stdout);
    for(i = 0; i < element_number; i++)
    {
        printf("%d  ", array[i]);
    }
    printf("\n");
    return 0;
}
