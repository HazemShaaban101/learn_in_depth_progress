//
// Created by Hazem on 7/5/2024.
//

#include "database.h"

STUDENT_t student_info[50];// the database that will hold student information
int int_buffer; char char_buffer[50]; float float_buffer;// these hold the input data before we put them in the database to verify validity

// this function initialized the queue buffer, it is non-circular, so we don't need a tail pointer
void buffer_init()
{
    printf("initializing buffer.....");
    student_queue_buffer.count = 0;
    student_queue_buffer.size = 50;
    student_queue_buffer.base = student_info;
    student_queue_buffer.head = student_info;
    printf("DONE\n");
}

DATABASE_STAT_t add_students_from_file() {
    printf("====================================================================================\n");
    // read file and check if it's read correctly
    FILE *input_file = fopen("./students.dp", "r");
    if (input_file == NULL) {
        return corrupt_file;
    }
    // the string buffer that will read lines from file
    char file_buffer[256] = {0};

    // loop through all file, reading it line by line
    while (fgets(file_buffer, sizeof(file_buffer), input_file) != NULL) {
        // check if database is full
        if (student_queue_buffer.count == student_queue_buffer.size)
        {
            return database_full;
        }
        int ID = 0;
        char first_name[50] = {0};
        char last_name[50] = {0};
        float GPA = 0.0;
        int number_of_courses = 0;
        if (sscanf(file_buffer, "%d %s %s %f %d", &ID, first_name, last_name, &GPA, &number_of_courses) != 5) {
            if (ID == 0)
			{
				printf("[ERROR] Invalid Roll number input!\n");
				continue;
			}
			if (is_valid_name(first_name, strlen(first_name)))
			{
				printf("[ERROR] Invalid First name!\n");
				continue;
			}
			if (is_valid_name(last_name, strlen(last_name)))
			{
				printf("[ERROR] Invalid Last name!\n");
				continue;
			}
			if (GPA == 0)
			{
				printf("[ERROR] Invalid GPA!\n");
				continue;
			}
			if (number_of_courses == 0)
			{
				printf("[ERROR] Invalid course number!\n");
				continue;
			}
        }

        // for each line read, start doing the same steps of manual input but put data into a buffer student info struct
        STUDENT_t student_buffer;
        int position_in_string = 0;
        sscanf(&file_buffer[position_in_string], "%s", char_buffer);
        position_in_string += strlen(char_buffer) + 1;
        // check if user entered an invalid roll number(characters or symbols)
        if (is_valid_int(char_buffer, strlen(char_buffer)))
        {
            printf("[ERROR] invalid student roll number detected. ignoring student...\n");
            continue;
        }
        // convert roll number to int
        int_buffer = atoi(char_buffer);

        // check if roll number is taken
        int is_taken = 0;
        for (int i = 0; i < student_queue_buffer.count; i++)
        {
            if (int_buffer == student_info[i].roll_ID)
            {
                printf("[ERROR] roll number taken. ignoring student...\n");
                is_taken++;
            }
        }
        if (is_taken)
        {
            continue;
        }

        // so far roll number is valid, now we put it at the head of the database
        student_buffer.roll_ID = int_buffer;
        //--------------------------------------------------------------------------//

        // now we ask for first name
        sscanf(&file_buffer[position_in_string],"%s", char_buffer);
        position_in_string += strlen(char_buffer) + 1;
        // check if entered name is valid
        if (is_valid_name(char_buffer, strlen(char_buffer)))
        {
            printf("[ERROR] invalid student first name. ignoring student...\n");
            continue;
        }
        // now we know name is valid, so we copy the name to the head->first_name
        strcpy(student_buffer.first_name, char_buffer);
        //--------------------------------------------------------------------------//

        // now we ask for last name
        sscanf(&file_buffer[position_in_string], "%s", char_buffer);
        position_in_string += strlen(char_buffer) + 1;
        // check if entered name is valid
        if (is_valid_name(char_buffer, strlen(char_buffer)))
        {
            printf("[ERROR] invalid student last name. ignoring student...\n");
            continue;
        }
        // now we know name is valid, so we copy the name to the head->last_name
        strcpy(student_buffer.last_name, char_buffer);
        //----------------------------------------------------------------------------//
        // now we ask for GPA
        sscanf(&file_buffer[position_in_string], "%s", char_buffer);
        position_in_string += strlen(char_buffer) + 1;
        // check if entered GPA is valid
        if (is_valid_float(char_buffer, strlen(char_buffer)))
        {
            printf("[ERROR] invalid student GPA. ignoring student...\n");
            continue;
        }
        // now we know GPA is valid, so we copy the GPA to the head->GPA after converting it and checking if its within bounds
        float_buffer = (float) atof(char_buffer);
        if (float_buffer <= 0 || float_buffer > 4)
        {
            printf("[ERROR] invalid student GPA. ignoring student...\n");
            continue;
        }
        student_buffer.GPA = float_buffer;
        //--------------------------------------------------------------------------------//

        // ask for number of registered courses
        sscanf(&file_buffer[position_in_string], "%s", char_buffer);
        position_in_string += strlen(char_buffer) + 1;
        // check if input is valid
        if (is_valid_int(char_buffer, strlen(char_buffer)))
        {
            printf("[ERROR] invalid student course number. ignoring student...\n");
            continue;
        }
        // convert string to int before checking if it's less than 10
        int_buffer = atoi(char_buffer);
        if (int_buffer > 10)
        {
            printf("[ERROR] invalid student course number. ignoring student...\n");
            continue;
        }
        // save course count to student info struct
        student_buffer.course_count = int_buffer;
        for (int i = 0; i < student_buffer.course_count; i++)
        {
            sscanf(&file_buffer[position_in_string],"%s", char_buffer);
            position_in_string += strlen(char_buffer) + 1;
            if (is_valid_int(char_buffer, strlen(char_buffer)))
            {
                printf("[ERROR] invalid student course ID. please update course list manually\n");
                printf("[ERROR] student roll number: %d\n", student_buffer.roll_ID);
                continue;
            }
            student_buffer.course_ID[i] = atoi(char_buffer);
        }
        //------------------------------------------------------------------------------------------//
        // after copying data is done, we just copy the student buffer struct inside the head of the student database and increment count
        *student_queue_buffer.head = student_buffer;
        student_queue_buffer.head++;
        student_queue_buffer.count++;
        printf("[INFO] student: %s %s roll number: %d was added\n", student_buffer.first_name, student_buffer.last_name, student_buffer.roll_ID);
    }
    fclose(input_file);
    return no_error_or_all_errors_printed;
}

// add student manually function, it should ask for a roll number, loop through all students to check if roll number is available
DATABASE_STAT_t add_student_manually()
{
    printf("====================================================================================\n");
    // check if database is full
    if (student_queue_buffer.count == student_queue_buffer.size)
    {
        return database_full;
    }
    //------------------------initial text--------------------------------//
    printf("-------------------------------------------\n");
    printf("            Add student details\n");
    printf("-------------------------------------------\n");
    //--------------------------------------------------------------------//
    printf("Enter student Roll number:");
    scanf("%s", char_buffer);

    // check if user entered an invalid roll number(characters or symbols)
    if (is_valid_int(char_buffer, strlen(char_buffer)))
    {
        return invalid_rollnumber_input;
    }
    // convert roll number to int
    int_buffer = atoi(char_buffer);

    // check if roll number is taken
    for (int i = 0; i < student_queue_buffer.count; i++)
    {
        if (int_buffer == student_info[i].roll_ID)
        {
            return rollnumber_taken;
        }
    }

    // so far roll number is valid, now we put it at the head of the database
    student_queue_buffer.head->roll_ID = int_buffer;
    //--------------------------------------------------------------------------//

    // now we ask for first name
    printf("Enter the first name of student:");
    scanf("%s", char_buffer);
    // check if entered name is valid
    if (is_valid_name(char_buffer, strlen(char_buffer)))
    {
        return invalid_name;
    }
    // now we know name is valid, so we copy the name to the head->first_name
    strcpy(student_queue_buffer.head->first_name, char_buffer);
    //--------------------------------------------------------------------------//

    // now we ask for last name
    printf("Enter the last name of student:");
    scanf("%s", char_buffer);
    // check if entered name is valid
    if (is_valid_name(char_buffer, strlen(char_buffer)))
    {
        return invalid_name;
    }
    // now we know name is valid, so we copy the name to the head->last_name
    strcpy(student_queue_buffer.head->last_name, char_buffer);
    //----------------------------------------------------------------------------//

    // now we ask for GPA
    printf("Enter the GPA of student:");
    scanf("%s", char_buffer);
    // check if entered GPA is valid
    if (is_valid_float(char_buffer, strlen(char_buffer)))
    {
        return invalid_GPA;
    }
    // now we know GPA is valid, so we copy the GPA to the head->GPA after converting it and checking if its within bounds
    float_buffer = (float) atof(char_buffer);
    if (float_buffer <= 0 || float_buffer > 4)
    {
        return invalid_GPA;
    }
    student_queue_buffer.head->GPA = float_buffer;
    //--------------------------------------------------------------------------------//

    // ask for number of registered courses
    printf("enter number of registered courses:");
    scanf("%s", char_buffer);
    // check if input is valid
    if (is_valid_int(char_buffer, strlen(char_buffer)))
    {
        return invalid_course_number;
    }
    // convert string to int before checking if it's less than 10
    int_buffer = atoi(char_buffer);
    if (int_buffer > 10)
    {
        return invalid_course_number;
    }
    // save course count to student info struct
    student_queue_buffer.head->course_count = int_buffer;
    for (int i = 0; i < student_queue_buffer.head->course_count; i++)
    {
        printf("enter course number %d's ID:", i + 1);
        scanf("%s", char_buffer);
        if (is_valid_int(char_buffer, strlen(char_buffer)))
        {
            return invalid_course_ID;
        }
        student_queue_buffer.head->course_ID[i] = atoi(char_buffer);
    }
    //------------------------------------------------------------------------------------------//
    // student was added successfully, now we increment buffer
    student_queue_buffer.head++;
    student_queue_buffer.count++;
    return student_added_successfully;
}

// function to loop through database and find student with matching roll number
DATABASE_STAT_t find_student_ID()
{
    printf("====================================================================================\n");
    // ask for student ID to search
    printf("Enter student Roll number:");
    scanf("%s", char_buffer);
    // check if user input is valid
    if (is_valid_int(char_buffer, strlen(char_buffer)))
    {
        return invalid_rollnumber_input;
    }
    // convert user input, then loop through all students until matching ID is found
    // if id is found, student info is printed, if it's not found function returns error
    int_buffer = atoi(char_buffer);
    for (int i = 0; i < student_queue_buffer.count; i++)
    {
        if (student_info[i].roll_ID == int_buffer)
        {
            print_student(i);
            return student_found;
        }
    }
    return student_not_found;
}

// function to loop through database and find students with names that match input
DATABASE_STAT_t find_student_name()
{
    printf("====================================================================================\n");
    // ask user for name to search for
    printf("enter student name: ");
    scanf("%s", char_buffer);
    if (is_valid_name(char_buffer, strlen(char_buffer)))
    {
        return invalid_name;
    }

    // loop through all students, if input name matches a student name, print that student
    int students_found = 0;
    for (int i = 0; i < student_queue_buffer.count; i++)
    {
        if (!strcmp(char_buffer, student_info[i].first_name))
        {
            print_student(i);
            students_found++;
        }
    }
    // if students with matching names to input is more than 0, return student found, else return student not found
    if (students_found)
    {
        return student_found;
    }
    return student_not_found;
}

// this function loops through all students, and for each student loop through registered courses to find if that
// student is registered to the input course, if a match is found student name and roll number are printed
DATABASE_STAT_t registered_in_course()
{
    printf("====================================================================================\n");
    // ask user for course ID
    printf("Enter course ID:");
    scanf("%s", char_buffer);
    // check if input is a valid number
    if (is_valid_int(char_buffer, strlen(char_buffer)))
    {
        return invalid_course_ID;
    }
    // if it is valid, convert it to int, then loop through all courses for all students and find matches
    // if matches are found, students_found++, if students_found == 0 at the end, return student_not_found
    int students_found = 0;
    int_buffer = atoi(char_buffer);
    for (int i = 0; i < student_queue_buffer.count; i++)
    {
        for (int j = 0; j < student_info[i].course_count; j++)
        {
            if (int_buffer == student_info[i].course_ID[j])
            {
                printf("------------------------------------------------------------------------------------\n");
                printf("student name: %s %s\n", student_info[i].first_name, student_info[i].last_name);
                printf("student roll number: %d\n", student_info[i].roll_ID);
                printf("student GPA is: %.2f\n", student_info[i].GPA);
                students_found++;
            }
        }
    }
    if (students_found)
    {
        return student_found;
    }
    return student_not_found;
}

// delete student function, this function loops through database until it finds a student with a matching roll number,
// then deletes the student and shifts the rest of the database backwards

DATABASE_STAT_t delete_student()
{
    printf("====================================================================================\n");
    // ask user for roll number to find
    printf("enter student roll number: ");
    scanf("%s", char_buffer);
    // check if user input is valid
    if (is_valid_int(char_buffer, strlen(char_buffer)))
    {
        return invalid_rollnumber_input;
    }
    //if it is valid, convert it to int
    int_buffer = atoi(char_buffer);
    // loop through all students, once you find match, break
    int i = 0;
    for (i; i < student_queue_buffer.count; i++)
    {
        if (student_info[i].roll_ID == int_buffer)
        {
            break;
        }
    }
    // if i is equal to student count, that means there was no match, so we return student not found
    if (i == student_queue_buffer.count)
    {
        return student_not_found;
    }
    // shift all  next students backwards by one
    for (i; i < student_queue_buffer.count - 1; i++)
    {
        student_info[i] = student_info[i + 1];
    }
    student_queue_buffer.count--;
	student_queue_buffer.head--;
    return student_deleted_successfully;
}

// this function updates student info
DATABASE_STAT_t update_info()
{
    printf("====================================================================================\n");

    printf("Enter the roll number to update entry: ");
    scanf("%s", char_buffer);
    if(is_valid_int(char_buffer, strlen(char_buffer)))
    {
        return invalid_rollnumber_input;
    }
    int_buffer = atoi(char_buffer);
    // find index of student with matching roll number
    int i = 0;
    for (i; i < student_queue_buffer.count; i++)
    {
        if (student_info[i].roll_ID == int_buffer)
        {
            break;
        }
    }
    // if i is equal to student count, that means there was no match, so we return student not found
    if (i == student_queue_buffer.count)
    {
        return student_not_found;
    }
    // ask user for the value they want to change and check if it's a valid value
    printf("1. First name\n2. Last name\n3. Roll number\n4. GPA\n5. courses\n");
    scanf("%s", char_buffer);
    if(is_valid_int(char_buffer, strlen(char_buffer)))
    {
        return invalid_choice;
    }
    int_buffer = atoi(char_buffer);
    if (int_buffer > 5 || int_buffer < 1)
    {
        return invalid_choice;
    }
    // switch to the case of the value the user wants to change
    switch (int_buffer)
    {
        // case 1: edit first name
        case 1:
            printf("Enter first name:");
            scanf("%s", char_buffer);
            if (is_valid_name(char_buffer, strlen(char_buffer)))
            {
                return invalid_name;
            }
            strcpy(student_info[i].first_name, char_buffer);
            return student_updated_successfully;
        //case 2: edit last name
        case 2:
            printf("Enter last name:");
            scanf("%s", char_buffer);
            if (is_valid_name(char_buffer, strlen(char_buffer)))
            {
                return invalid_name;
            }
            strcpy(student_info[i].last_name, char_buffer);
            return student_updated_successfully;
        //case 3: edit roll number
        case 3:
            printf("Enter roll number:");
            scanf("%s", char_buffer);
            if (is_valid_int(char_buffer, strlen(char_buffer)))
            {
                return invalid_rollnumber_input;
            }
            int_buffer = atoi(char_buffer);
            student_info[i].roll_ID = int_buffer;
            return student_updated_successfully;
        // case 4: edit GPA
        case 4:
            printf("Enter GPA:");
            scanf("%s", char_buffer);
            if (is_valid_float(char_buffer, strlen(char_buffer)))
            {
                return invalid_GPA;
            }
            float_buffer = (float) atof(char_buffer);
            student_info[i].GPA = float_buffer;
            return student_updated_successfully;
        // case 5: edit registered courses
        case 5:
            printf("Enter number of courses:");
            scanf("%s", char_buffer);
            if (is_valid_int(char_buffer, strlen(char_buffer)))
            {
                return invalid_course_number;
            }
            int_buffer = atoi(char_buffer);
            if (int_buffer <= 0 || int_buffer > 10)
            {
                return invalid_course_number;
            }
            for (int j = 0; j < int_buffer; j++)
            {
                printf("course %d ID: ", j + 1);
                scanf("%s", char_buffer);
                if (is_valid_int(char_buffer, strlen(char_buffer)))
                {
                    return invalid_course_ID;
                }
                student_info[i].course_ID[j] = atoi(char_buffer);
            }
            student_info[i].course_count = int_buffer;
            return student_updated_successfully;
        default:
            return invalid_choice;
    }
}


// this function prints number of students in database, we already have a counter so that should be easy
DATABASE_STAT_t print_student_count()
{
    printf("====================================================================================\n");
    printf("[INFO] The total number of students is %d\n", student_queue_buffer.count);
    printf("[INFO] You can add up to %d students\n", student_queue_buffer.size);
    printf("[INFO] you can add %d more students\n", student_queue_buffer.size - student_queue_buffer.count);
    return no_error_or_all_errors_printed;
}

DATABASE_STAT_t print_all()
{
    for (int i = 0; i < student_queue_buffer.count; i++)
    {
        print_student(i);
    }
    return no_error_or_all_errors_printed;
}

DATABASE_STAT_t save_and_exit()
{
    // open output file and make sure its open
    remove("./students.dp");
    FILE * output = fopen("./students.dp", "w");
    if (!output)
    {
        return cant_open_output_file;
    }
    // start printing each student to file
    for (int i = 0; i < student_queue_buffer.count; i++)
    {
        fprintf(output, "%d %s %s %.2f %d", student_info[i].roll_ID, student_info[i].first_name, student_info[i].last_name, student_info[i].GPA, student_info[i].course_count);
        for (int j = 0; j < student_info[i].course_count; j++)
        {
            fprintf(output, " %d", student_info[i].course_ID[j]);
        }
        fprintf(output, "\n");
    }
    return data_saved;
}

// this function prints student info at index
void print_student(int index)
{
    printf("====================================================================================\n");
    printf("Student roll number: %d\n", student_info[index].roll_ID);
    printf("Student First name: %s\n", student_info[index].first_name);
    printf("Student Last name: %s\n", student_info[index].last_name);
    printf("Student GPA: %.2f\n", student_info[index].GPA);
    printf("Registered course count: %d\n", student_info[index].course_count);
    for (int i = 0; i < student_info[index].course_count; i++)
    {
        printf("course %d ID: %d\n", i + 1, student_info[index].course_ID[i]);
    }
}

// function to check the validity of a string as an int
// returns 0 if it is valid, and 1 if invalid
int is_valid_int(const char * buffer, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(buffer[i]))
        {
            return 1;
        }
    }
    return 0;
}

// function to check the validity of a string as a name
// returns 0 if it is valid, and 1 if invalid
int is_valid_name(char * buffer, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(buffer[i]))
        {
            return 1;
        }
        else
        {
            buffer[i] = tolower(buffer[i]);
        }
    }
    return 0;
}

// function to check the validity of a string as a float
// returns 0 if it is valid, and 1 if invalid
int is_valid_float(const char * buffer, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(buffer[i]) && buffer[i] != '.')
        {
            return 1;
        }
    }
    return 0;
}