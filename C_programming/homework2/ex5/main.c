#include <stdio.h>

int main() {
    printf("Enter a character:");
    char c;
    scanf("%c", &c);
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) printf("%c is an alphabet\n", c);
    else printf("%c is not an alphabet\n", c);
    return 0;
}
