#include "LIFO.h"

void main (void)
{
	int array_of_integers[5];
	LIFO_t stack_buffer_for_Array_of_ints;
	
	LIFO_INIT(&stack_buffer_for_Array_of_ints, array_of_integers, 5);
	
	for (int i = 0; i < 4; i++)
	{
		printf("PUSHING: %d\n", i);
		LIFO_PUSH(&stack_buffer_for_Array_of_ints, i);
	}
	
	for (int i = 0; i < 2; i++)
	{
		int element = 20;
		LIFO_POP(&stack_buffer_for_Array_of_ints, &element);
		printf("POPPED: %d\n", element);
	}
	
	for (int i = 0; i < 3; i++)
	{
		printf("PUSHING: %d\n", i);
		LIFO_PUSH(&stack_buffer_for_Array_of_ints, i);
	}
	
	for (int i = 0; i < 5; i++)
	{
		int element = 20;
		LIFO_POP(&stack_buffer_for_Array_of_ints, &element);
		printf("POPPED: %d\n", element);
	}
}