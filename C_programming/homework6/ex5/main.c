#include <stdio.h>


struct Semployees
{
    char m_Name[50];
    int m_ID;
};
int main() {
    struct Semployees employee[3];
    struct Semployees *employee_arr[3] = {&employee[0], &employee[1], &employee[2]};
    struct Semployees *(*employee_arr_ptr)[] = &employee_arr;

    int i;
    for (i = 0; i < 3; i++)
    {
        printf("\nEnter employee %d\nname:", i+1);
        scanf("%s", (*employee_arr_ptr)[i]->m_Name);
        printf("Enter employee ID:");
        scanf("%d", &((*employee_arr_ptr)[i]->m_ID));
    }


    printf("\n====================================================\nList of employees:\n");
    for (i = 0; i < 3; i++)
    {
        printf("Employee %d\nname: %s\n", i+1, (*employee_arr_ptr)[i]->m_Name);
        printf("Employee ID: %d\n\n", (*employee_arr_ptr)[i]->m_ID);
    }

    return 0;
}
