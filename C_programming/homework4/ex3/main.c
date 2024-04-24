#include <stdio.h>
#include <string.h>
void reverse(char[], int);


int main() {
    // get user input
    printf("Enter a sentence:");
    char s[50];
    gets(s);
    // calculate length of string
    int s_length = (int) strlen(s) - 1;

    //execute reverse function

    reverse(s, s_length);
    return 0;
}


void reverse(char s[], int s_length)
{
    if (s_length == 0)
    {
        printf("%c", s[s_length]);
        return;
    }

    printf("%c", s[s_length--]);
    reverse(s, s_length);
}

