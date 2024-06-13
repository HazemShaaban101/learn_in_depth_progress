#include "FIFO.h"

void main (void)
{
	int array_of_integers[5];
	FIFO_t queue_buffer_for_Array_of_ints;
	
	FIFO_INIT(&queue_buffer_for_Array_of_ints, array_of_integers, 5);
	
	for (int i = 0; i < 7; i++)
	{
		printf("ADDING: %d", i);
		int status = FIFO_ADD(&queue_buffer_for_Array_of_ints, i);
		if (status == QUEUE_FULL)
			printf("\t\tinvalid add, queue is full\n");
		else
			printf("\n");
	}
	
	for (int i = 0; i < 2; i++)
	{
		int element = 20;
		int status = FIFO_REMOVE(&queue_buffer_for_Array_of_ints, &element);
		printf("REMOVED: %d", element);
		if (status == QUEUE_FULL)
			printf("\t\tinvalid remove, queue is empty\n");
		else
			printf("\n");
	}
	
	for (int i = 0; i < 5; i++)
	{
		printf("ADDING: %d", i);
		int status = FIFO_ADD(&queue_buffer_for_Array_of_ints, i);
		if (status == QUEUE_FULL)
			printf("\t\tinvalid add, queue is full\n");
		else
			printf("\n");
	}
	
	for (int i = 0; i < 5; i++)
	{
		int element = 20;
		int status = FIFO_REMOVE(&queue_buffer_for_Array_of_ints, &element);
		printf("REMOVED: %d", element);
		if (status == QUEUE_FULL)
			printf("\t\tinvalid remove, queue is empty\n");
		else
			printf("\n");
	}
}