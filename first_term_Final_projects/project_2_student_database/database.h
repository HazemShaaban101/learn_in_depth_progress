//
// Created by Hazem on 7/5/2024.
//

#ifndef STUDENT_DATABASE_QUEUE_DATABASE_H
#define STUDENT_DATABASE_QUEUE_DATABASE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// student info struct
typedef struct
{
    char first_name[50];
    char last_name[50];
    int roll_ID;
    float GPA;
    int course_count;
    int course_ID[10];
}STUDENT_t;

//
struct students
{
    STUDENT_t * head;
    STUDENT_t * base;
    int count;
    int size;
}student_queue_buffer;

typedef enum
{
    rollnumber_taken,
    invalid_rollnumber_input,
    invalid_name,
    invalid_GPA,
    invalid_course_number,
    invalid_course_ID,
    student_added_successfully,
    student_found,
    student_not_found,
    student_deleted_successfully,
    invalid_choice,
    corrupt_file,
    no_error_or_all_errors_printed,
    database_full,
    student_updated_successfully,
    cant_open_output_file,
    data_saved
}DATABASE_STAT_t;


// methods
int is_valid_float(const char * buffer, int length);
int is_valid_name(const char * buffer, int length);
int is_valid_int(const char * buffer, int length);
void print_student(int index);
void buffer_init();
DATABASE_STAT_t add_student_manually();
DATABASE_STAT_t add_students_from_file();
DATABASE_STAT_t find_student_ID();
DATABASE_STAT_t find_student_name();
DATABASE_STAT_t registered_in_course();
DATABASE_STAT_t delete_student();
DATABASE_STAT_t update_info();
DATABASE_STAT_t print_student_count();
DATABASE_STAT_t print_all();
DATABASE_STAT_t save_and_exit();
#endif //STUDENT_DATABASE_QUEUE_DATABASE_H
