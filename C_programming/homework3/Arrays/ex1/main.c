#include <stdio.h>

int main() {    // program that outputs the sum of two arrays
                // arrays are input of user
    int i, j;   //counter vars

    float mat1[2][2]; //first matrix
    printf("Enter the elements of the 1st matrix\n");
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            printf("Enter a%d%d:", i + 1, j + 1);
            scanf("%f", &(mat1[i][j]));  //ittirates over each element and takes user input
        }
    }

    float mat2[2][2]; //second matrix
    printf("Enter the elements of the 2nd matrix\n");
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            printf("Enter b%d%d:", i + 1, j + 1);
            scanf("%f", &(mat2[i][j])); //ittirates over each element and takes user input
        }
    }

    printf("Sum of matrix:\n");
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            printf("%.1f\t",mat1[i][j] + mat2[i][j]);
        }
        printf("\n");
    }
    return 0;

}
