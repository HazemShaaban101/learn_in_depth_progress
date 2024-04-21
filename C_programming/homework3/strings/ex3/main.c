#include <stdio.h>
#include <string.h>


int main() {
    // funky way to reverse a string
    printf("Enter the string:");
    char string[100];
    gets(string);

    int length = (int) strlen(string);
    int interval = length / 2;
    int i;
    for (i = 0; i < interval; i++)
    {
        char buffer = string[i];
        string[i] = string[length - 1 - i];
        string[length - 1- i] = buffer;
    }

    printf("Reverse of string: %s\n", string);
    return 0;
}
