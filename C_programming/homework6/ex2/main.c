#include <stdio.h>

int main() {
    char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int i;
    printf("The alphabet are:\n");
    for (i = 0; i < 26; i++)
    {
        printf("%c  ", *(alphabet + i));
    }
    return 0;
}
