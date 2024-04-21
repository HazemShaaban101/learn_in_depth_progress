#include <stdio.h>

int main() {
    //transpose matrix
    int rows, columns;
    printf("Enter rows and columns of matrix:");
    scanf("%d %d", &rows, &columns);
    int matrix[rows][columns];

    printf("Enter elements of matrix:\n");
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf("Enter elements a%d%d:", i + 1, j + 1);
            scanf("%d", &matrix[i][j]); // scan into matrix elements
        }
    }

    printf("Entered matrix:\n");
    for(i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Transpose of matrix:\n");
    for(i = 0; i < columns; i++)
    {
        for (j = 0; j < rows; j++)
        {
            printf("%d\t", matrix[j][i]);
        }
        printf("\n");
    }
    return 0;
}
