//
// Created by Hazem on 6/11/2024.
//
#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FLUSH   fflush(stdin); fflush(stdout);

student_t * first_Student = NULL;
student_t * last_student = NULL;
int student_count = 0;

// this function creates a node dynamically for the student database, and checks if node is created or not
node_stat_t create_node()
{
    student_t * new_node = (student_t *) malloc(sizeof(student_t));

    // check if node is created
    if (new_node == NULL)
        return error_creating_node;

    // check if its first student in list
    if (last_student == NULL && first_Student == NULL)
    {
        first_Student = new_node;
        last_student = new_node;
        student_count++;
        return node_created;
    }

    // if it's not the first student, set last student's pointer to point to new node, then make the last student the new node
    else
    {
        last_student->next_student = new_node;
        last_student = new_node;
        student_count++;
        return node_created;
    }
}

// this function asks user for student info to add to a newly created node, it also sets next student pointer to NULL
// for easy checking for end of list
// functionality to be added: learning to refuse invalid inputs such as strings in ID or numbers in name
student_stat_t add_student()
{
    // if node isn't there, report error
    if (last_student == NULL)
        return error_adding_student;

    // get student info from user and save it to node
    printf("====================================================================================================\n");FLUSH
    // get student ID
    printf("Enter the ID: ");FLUSH
    scanf("%d", &(last_student->ID));FLUSH
    getchar();

    // get name with a smart way that doesn't cause valgrind to cry
    printf("Enter student full name: ");FLUSH
    fgets(last_student->name, 50, stdin);FLUSH
    last_student->name[strcspn(last_student->name, "\n")] = 0;

    //get height
    printf("Enter height: ");FLUSH
    scanf("%f", &(last_student->height));FLUSH

    //set next_student pointer to null
    last_student->next_student = NULL;

    // return status
    return student_added;
}


// this function removes the first instance of an ID from the list by linking the previous node to the next node
// then freeing current node, if there are instances of duplicate IDs you can run the function over and over until it
// prints ID not found, then you can add the student once using add student option
// a function can be added later to remove duplicates automatically
student_stat_t remove_Student()
{
    if (student_count == 0)
        return no_Students_in_list;

    printf("====================================================================================================\n");FLUSH
    fflush(stdout); fflush(stdin);FLUSH

    unsigned int wanted_ID;
    printf("Enter student ID to remove:");FLUSH
    scanf("%d", &wanted_ID);FLUSH
    // first I need a buffer for previous node to connect it with the node after the one I remove
    student_t * previous_node = NULL;
    student_t * current_node = first_Student;

    // edge case if i want to remove first student
    if (first_Student->ID == wanted_ID)
    {
        first_Student = first_Student->next_student;
        free(current_node);
        student_count--;

        // in case of deleting last student
        if (student_count == 0)
        {
            first_Student = NULL;
            last_student = NULL;
        }
        return student_removed;

    }

    // loop through students to find wanted student
    while(current_node != NULL)
    {
        if (current_node->ID == wanted_ID)
        {
            previous_node->next_student = current_node->next_student;
            free(current_node);
            student_count--;
            // in case of deleting last student                 USELESS BECAUSE IT WILL NOT LOOP THROUGH THE LINKED
            //                                                  LIST UNLESS THE WANTED ID ISN'T ATH THE FIRST NODE
            if (student_count == 0)
            {
                first_Student = NULL;
                last_student = NULL;
            }
            return student_removed;

        }
        else
        {
            previous_node = current_node;
            current_node = current_node->next_student;
        }
    }
    return ID_not_found;
}

// this function prints all student info saved inside the database, it loops through all nodes until it reaches NULL pointer
student_stat_t print_all_students()
{
    // first check if there are students in the database
    if (student_count == 0)
    {
        return no_Students_in_list;
    }
    student_t * buffer = first_Student;
    int counter = 1;
    while (buffer != NULL)
    {
        // print student info
        printf("\tRecord number %d:\n", counter);
        printf("\t\tID: %d\n", buffer->ID);
        printf("\t\tName: %s\n", buffer->name);
        printf("\t\tHeight: %.2f\n\n", buffer->height);
        counter++;

        // set buffer to point to next node
        buffer = buffer->next_student;

    }
    return no_error;
}

// this function deletes all students and free all the memory taken by the nodes, then sets first and last student
// pointers to NULL to reset to initial state
student_stat_t delete_all_students()
{
    // first check if there are students in the database
    if (student_count == 0)
    {
        return no_Students_in_list;
    }


    student_t * buffer = first_Student;
    while (buffer != NULL)
    {
        student_t * next_Student = buffer->next_student;
        free(buffer);
        buffer = next_Student;
        student_count--;
    }

    // when done set first and last students to NULL
    first_Student = NULL;
    last_student = NULL;
    return no_error;
}

// this function finds student at index chosen by user
student_stat_t print_nth_student()
{
    printf("====================================================================================================\n");
    // check if list is empty
    if (student_count == 0)
        return no_Students_in_list;

    // get index from user
    unsigned int index = 0;
    printf("Enter student index:");
    scanf("%d", &index);
    // check if index is correct
    if (index >= student_count)
        return ID_not_found;

    // define counter and buffer to loop through the database
    unsigned counter = 0;
    student_t * buffer = first_Student;
    // loop until counter matches index
    while (counter != index)
    {
        buffer = buffer->next_student;
        counter++;
    }


    printf("\t\tID: %d\n", buffer->ID);
    printf("\t\tName: %s\n", buffer->name);
    printf("\t\tHeight: %.2f\n\n", buffer->height);

    return no_error;
}

// counts students recursively, we already have student count but a function was demanded so there you go
int count_nodes(student_t * head)
{
    if (head == NULL)
        return 0;

    return 1 + count_nodes(head->next_student);
}

student_stat_t print_nth_student_backwards()
{
    // check if list is empty
    if (student_count == 0)
        return no_Students_in_list;

    // get index from user
    unsigned int index = 0;
    printf("enter index to find from the end of the list:");
    scanf("%d", &index);
    // check if index is correct
    if (index >= student_count)
        return ID_not_found;



    student_t *current = first_Student;
    student_t *reference = first_Student;

    // shift reference from start by index
    for (; index > 0; index--)
    {
        reference = reference->next_student;
    }

    // shift both pointers until reference->next_student is null
    while(reference->next_student)
    {
        reference = reference->next_student;
        current = current->next_student;
    }
    // voilà you got the nth index from the back!

    printf("\t\tID: %d\n", current->ID);
    printf("\t\tName: %s\n", current->name);
    printf("\t\tHeight: %.2f\n\n", current->height);
    return no_error;
}

student_stat_t find_middle()
{
    // check if list is empty
    if (student_count == 0)
        return no_Students_in_list;

    // define two pointers, one increments by 1 step, the other increments by 2 steps
    // when fast pointer reaches the last node where next_Student is NULL, the slow
    // pointer will be at the middle, if the number of nodes is even increment slow
    // pointer by one before printing
    student_t * slow_pointer = first_Student;
    student_t * fast_pointer = first_Student;

    while (fast_pointer->next_student && fast_pointer->next_student->next_student)
    {
        fast_pointer = fast_pointer->next_student->next_student;
        slow_pointer = slow_pointer->next_student;
    }
    if (fast_pointer->next_student)
        slow_pointer = slow_pointer->next_student;

    printf("\t\tID: %d\n", slow_pointer->ID);
    printf("\t\tName: %s\n", slow_pointer->name);
    printf("\t\tHeight: %.2f\n\n", slow_pointer->height);
    return no_error;
}


int floyd_cycle()
{
    // check if list is empty
    if (student_count == 0)
        return 0;

    student_t * fast_ptr = first_Student;
    student_t * slow_ptr = first_Student;

    while (fast_ptr->next_student && fast_ptr->next_student->next_student)
    {
        fast_ptr = fast_ptr->next_student->next_student;
        slow_ptr = slow_ptr->next_student;
        if (fast_ptr == slow_ptr)
            return 1;
    }
    return 0;
}

student_stat_t reverse_list()
{
    if (student_count < 2)
    {
        return cannot_reverse;
    }

    last_student = first_Student;
    student_t * next_buffer = NULL;
    student_t * current_buffer = first_Student->next_student;
    student_t * prev_buffer = first_Student;



    // loop through all elements, reversing the pointer from (prev_buffer to buffer) into (buffer to prev_buffer)
    while (current_buffer)
    {
        next_buffer = current_buffer->next_student;
        current_buffer->next_student = prev_buffer;
        prev_buffer = current_buffer;
        current_buffer = next_buffer;
    }
    last_student->next_student = NULL;
    first_Student = prev_buffer;
    return no_error;
}


void free_all()
{
    student_t * buffer = first_Student;

    // free all heap memory
    while (buffer)
    {
        student_t * next_buffer = buffer->next_student;
        free(buffer);
        buffer = next_buffer;
    }
}