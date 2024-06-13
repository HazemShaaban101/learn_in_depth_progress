//
// Created by Hazem on 6/11/2024.
//

#ifndef STUDENTDB_DATABASE_H
#define STUDENTDB_DATABASE_H

// useful structs

// the node that holds student info, plus a pointer to the next node

typedef struct student_t
{
    unsigned int ID;
    char name[50];
    float height;
    struct student_t *next_student;
}student_t;

// node creation status
typedef enum
{
    node_created,
    error_creating_node
}node_stat_t;

typedef enum
{
    no_error,
    student_added,
    error_adding_student,
    student_removed,
    ID_not_found,
    no_Students_in_list,
    cannot_reverse
}student_stat_t;

node_stat_t create_node();
student_stat_t add_student();
student_stat_t remove_Student();
student_stat_t print_all_students();
student_stat_t delete_all_students();
student_stat_t print_nth_student();
int count_nodes(student_t * head);
student_stat_t print_nth_student_backwards();
student_stat_t find_middle();
int floyd_cycle();
student_stat_t reverse_list();
void free_all();




#endif //STUDENTDB_DATABASE_H
