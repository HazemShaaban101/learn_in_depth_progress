#include <stdio.h>

int main() {
    // define int m = 29
    int m = 29;
    printf("Address of m: 0x%p\n", &m);
    printf("value of m = %d\n\n", m);


    //pointer to m
    int *ab = &m;
    printf("Now ab is assigned with the address of m.\n");
    printf("Address inside pointer ab: 0x%p\n", ab);
    printf("Content inside the memory pointed to by ab: %d\n\n", *ab);

    // m is assigned to 34
    m = 34;
    printf("The value of m assigned to 34 now.\n");
    printf("Address of m: 0x%p\n", &m);
    printf("value of m = %d\n\n", m);

    // value inside memory pointed to by ab is assigned to 7
    *ab = 7;
    printf("The pointer variable ab is assigned with the value 7 now.\n");
    printf("Address inside pointer ab: 0x%p\n", ab);
    printf("Content inside the memory pointed to by ab: %d\n\n", *ab);
    return 0;
}
