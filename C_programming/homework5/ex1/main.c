#include <stdio.h>
struct S_students get_student();
void print_student(struct S_students *student);


struct S_students
{
    char m_name[50];
    int m_roll;
    float m_grades;
};

int main() {
    struct S_students student = get_student();
    print_student(&student);
    return 0;
}
//prompts user for student info and saves it
struct S_students get_student()
{
    printf("Enter information of students\n");
    struct S_students student;
    printf("Enter name:");
    gets(student.m_name);
    printf("Enter Roll number:");
    scanf("%d", &student.m_roll);
    printf("Enter marks:");
    scanf("%f", &student.m_grades);

    return student;
}
//prints student info
void print_student(struct S_students *student)
{
    printf("\nDisplaying information\n");
    printf("name: %s\nRoll: %d\nMarks: %.2f\n", student->m_name, student ->m_roll, student->m_grades);
}
