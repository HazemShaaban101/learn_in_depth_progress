#include <stdio.h>

int main() {
    printf("Enter a string:");
    char string[100];
    gets(string);
    int counter = 0;
    while(string[counter] != 0)
    {
        counter++;
    }

    printf("Length of string: %d\n", counter);
    return 0;
}
