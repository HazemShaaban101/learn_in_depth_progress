#include <stdio.h>
#include "database.h"

extern char char_buffer[50]; extern int int_buffer;

int main() {
    buffer_init();
    printf("====================================================================================\n");
    printf("Created by: Hazem shaaban   as part of Learn in depth:mastering embedded systems\n");
    printf("            ******* Welcome to student management system *******\n");


    while(1)
    {
        //header
        printf("====================================================================================\n");
        printf("1. Add the student details manually\n");
        printf("2. Add the student details from file\n");
        printf("3. Find student details using roll number\n");
        printf("4. Find student details using first name\n");
        printf("5. Find students registered to course\n");
        printf("6. Find the total number of students\n");
        printf("7. Delete student details using roll number\n");
        printf("8. Update student details using roll number\n");
        printf("9. Show all student information\n");
        printf("10. save and exit\n");

        // ask for input and check if input is a valid number
        printf("Enter choice to preform the task:");
        scanf("%s", char_buffer);
        if (is_valid_int(char_buffer, strlen(char_buffer)))
        {
            printf("invalid input!, input must be a number between 1 and 10\n");
            continue;
        }
        // convert input to int
        int_buffer = atoi(char_buffer);

        // switch to the function requested by user and save return code
        DATABASE_STAT_t return_code = 0;
        switch (int_buffer)
        {
            case 1:
                return_code = add_student_manually();
                print_student_count();
                break;
            case 2:
                return_code = add_students_from_file();
                print_student_count();
                break;
            case 3:
                return_code = find_student_ID();
                break;
            case 4:
                return_code = find_student_name();
                break;
            case 5:
                return_code = registered_in_course();
                break;
            case 6:
                return_code = print_student_count();
                break;
            case 7:
                return_code = delete_student();
                print_student_count();
                break;
            case 8:
                return_code = update_info();
                break;
            case 9:
                return_code = print_all();
                break;
            case 10:
                return_code = save_and_exit();
                break;
            default:
                printf("invalid input!, input must be a number between 1 and 10\n");
                continue;
        }
        // for each return code, decide the proper response
        switch (return_code)
        {
            case 0:
                printf("[ERROR] Roll number taken!\n");
                break;
            case 1:
                printf("[ERROR] Invalid Roll number input!\n");
                break;
            case 2:
                printf("[ERROR] Invalid name!\n");
                break;
            case 3:
                printf("[ERROR] Invalid GPA!\n");
                break;
            case 4:
                printf("[ERROR] Invalid course number!\n");
                break;
            case 5:
                printf("[ERROR] Invalid course ID!\n");
                break;
            case 6:
                printf("[INFO] Student was added successfully!\n");
                break;
            case 7:
                //printf("[INFO] Student Found!\n");
                break;
            case 8:
                printf("[ERROR] Student not found!\n");
                break;
            case 9:
                printf("[INFO] Student deleted successfully!\n");
                break;
            case 10:
                printf("[ERROR] Invalid choice!\n");
                break;
            case 11:
                printf("[ERROR] corrupt/non existent input file. make sure input file is named students.dp\n");
                break;
            case 12:
                break;
            case 13:
                printf("[ERROR] Database is full, consider removing graduated students\n");
                break;
            case 14:
                printf("[INFO] UPDATED SUCCESSFULLY!\n");
                break;
            case 15:
                printf("[ERROR] can't open output file\n");
                break;
            case 16:
                printf("[INFO] DATA SAVED!\n");
                return 0;
            default:
                printf("error code = %d\n", return_code);
                break;
        }
    }
}
