#include <stdio.h>
#include <math.h>
int isPrimal(int x);

int main() {
    // get user input and record it
    printf("Enter two numbers(intervals):");
    int start, finish;
    scanf("%d %d", &start, &finish);

    printf("Prime numbers between %d and %d are: ", start, finish);

    // loop through interval
    for (; start <= finish; start++)
    {
        // isPrimal takes int as input and returns true if its primal, and false if it's a composite number
        if (isPrimal(start))
        {
            printf("%d ", start);
        }
    }
    printf("\n");
    return 0;
}



int isPrimal(int x)
{
    // calculate sqrt
    int square_root = (int) sqrt(x);

    // loop all values between that sqrt and 2
    for (; square_root > 1; square_root--)
    {
        // if number is dividable by any number lower than sqrt return false which means number is composite
        if (!(x % square_root))
        {
            return 0;
        }
    }
    // if you finish looping without returning, that means the number is prime, so return true
    return 1;
}
