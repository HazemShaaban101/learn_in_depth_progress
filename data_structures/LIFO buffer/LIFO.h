// this is a stack buffer
// last in, first out
// made by: hazem shaaban bakry

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>




#ifndef LIFO_H_
#define LIFO_H_
#define DATA_TYPE int

typedef struct
{
	uint32_t UINT32_buffer_size;
	uint32_t UINT32_element_count;
	DATA_TYPE * p_buffer_base;
	DATA_TYPE * p_stack_head;
}LIFO_t;


typedef enum{
	no_error,
	element_added,
	element_removed,
	LIFO_NULL,
	buffer_invalid_size,
	STACK_FULL,
	STACK_EMPTY
}LIFO_STATUS_t;


LIFO_STATUS_t LIFO_INIT(LIFO_t * stack, DATA_TYPE * buffer, uint32_t size);

LIFO_STATUS_t LIFO_PUSH(LIFO_t * stack, DATA_TYPE element);

LIFO_STATUS_t LIFO_POP(LIFO_t * stack, DATA_TYPE * element);

#endif