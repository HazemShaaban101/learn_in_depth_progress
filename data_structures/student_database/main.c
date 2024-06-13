#include <stdio.h>
#include "database.h"

int function_Return;
extern student_t * first_Student;
extern student_t * last_student;


int main() {
    while (1)
    {
        printf("====================================================================================================\n");
        fflush(stdout); fflush(stdin);
        printf("\t\t\t Choose one of the following options\n");
        fflush(stdout); fflush(stdin);
        printf("\n1: Add student\n2: Delete student\n3: View students\n4: Delete all\n5: print student at an index n\n"
               "6: print student count\n7: print student at index n from the back\n8: find the student at the middle of database\n"
               "9: detect a loop in database through floyd cycle algorithm\n10: reverse student list\n");
        fflush(stdout); fflush(stdin);
        printf("\nenter option number:");
        fflush(stdout); fflush(stdin);

        int option = 0;
        scanf("%d", &option);

        switch(option)
        {
            case 1:
                if (create_node() == error_creating_node)
                {
                    printf("couldn't create student, memory is full!\n");
                    break;
                }
                if (add_student() == error_adding_student)
                {
                    printf("couldn't add student, please try again\n");
                    break;
                }
                else
                {
                    printf("student added successfully\n");
                    break;
                }

            case 2:
                function_Return = remove_Student();
                if (function_Return == ID_not_found)
                {
                    printf("Student ID not found, enter a valid id\n");
                    break;
                }
                else if (function_Return == no_Students_in_list)
                {
                    printf("Empty student list!\n");
                    break;
                }
                else
                {
                    printf("student removed\n");
                    break;
                }

            case 3:
                function_Return = print_all_students();
                if (function_Return == no_Students_in_list)
                {
                    printf("Empty student list!\n");
                    break;
                }
                break;

            case 4:
                function_Return = delete_all_students();
                if (function_Return == no_Students_in_list)
                {
                    printf("Empty student list!\n");
                    break;
                }
                else if(function_Return == no_error)
                {
                    printf("ALL STUDENTS DELETED!\n");
                    break;
                }
            case 5:
                function_Return = print_nth_student();
                if (function_Return == no_Students_in_list)
                {
                    printf("Empty student list!\n");
                    break;
                }

                else if(function_Return == ID_not_found)
                {
                    printf("No student with that index, enter a correct index\n");
                    break;
                }
                else if(function_Return == no_error)
                    break;

            case 6:
                printf("number of students: %d\n", count_nodes(first_Student));
                break;

            case 7:
                function_Return = print_nth_student_backwards();
                if (function_Return == no_Students_in_list)
                {
                    printf("Empty student list!\n");
                    break;
                }

                else if(function_Return == ID_not_found)
                {
                    printf("No student with that index, enter a correct index\n");
                    break;
                }
                else if(function_Return == no_error)
                    break;

            case 8:
                function_Return = find_middle();
                if (function_Return == no_Students_in_list)
                {
                    printf("Empty student list!\n");
                    break;
                }
                else if (function_Return == no_error)
                    break;

            case 9:
                if (floyd_cycle())
                {
                    printf("there is a loop!\n");
                    break;
                }
                else
                {
                    printf("no loop detected!\n");
                    break;
                }
            case 10:
                function_Return = reverse_list();
                if (function_Return == cannot_reverse)
                {
                    printf("cannot reverse list, list is too short\n");
                    break;
                }
                if (function_Return == no_error)
                {
                    printf("Student list reversed!\n");
                    break;
                }
            case 69:
                free_all();
                return 0;

            default:
                printf("Wrong option, please try again\n");
                break;
        }
    }
}
