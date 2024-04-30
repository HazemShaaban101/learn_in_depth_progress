

/*program to store info of 10 students then prints them*/

#include <stdio.h>

struct S_students
{
    char m_name[50];
    int m_roll;
    float m_marks;
};

int main() {
    // declare an array for 10 students
    struct S_students student[10];
    int i;
    printf("Enter information of students:\n");
    // scan for student info
    for (i = 0; i < 10; i++)
    {
        student[i].m_roll = i + 1;
        printf("For Roll number %d\n", student[i].m_roll);
        printf("Enter name:");
        fflush(stdin);
        fflush(stdout);
        gets(student[i].m_name);
        printf("Enter marks:");
        scanf("%f", &student[i].m_marks);
    }

    //print student info
    printf("\nDisplaying information of students:\n");
    for (i = 0; i < 10; i++)
    {
        printf("Information for Roll number %d\n", student[i].m_roll);
        printf("name: %s\n", student[i].m_name);
        printf("marks: %.1f\n", student[i].m_marks);
    }
    return 0;
}
