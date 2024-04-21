#include <stdio.h>
#include <string.h>

int main() {
    printf("Enter a string: ");
    char string[100];
    gets(string);
    strlwr(string);
    fflush(stdout);
    printf("Enter a character to find frequency: ");
    char character;
    scanf("%c", &character);



    int i, count = 0;
    for (i = 0; i < strlen(string); i++)
    {
        if (string[i] == character) count++;
    }

    printf("Frequency of %c = %d\n", character, count);
    return 0;
}
