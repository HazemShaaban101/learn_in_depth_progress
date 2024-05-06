#include <stdio.h>

int main() {
    char string[1000];
    printf("Input string to reverse: ");
    gets(string);

    char *str = string;
    while (*str != '\0')
    {
        str++;
    }
    str--;
    printf("Reverse of that string is: ");
    while (str >= string)
    {
        printf("%c", *str);
        str--;
    }
    return 0;
}
