// this is a stack buffer
// last in, first out
// made by: hazem shaaban bakry

#include "LIFO.h"


LIFO_STATUS_t LIFO_INIT(LIFO_t * stack, DATA_TYPE * buffer, uint32_t size)
{
	if (!buffer)
		return LIFO_NULL;
	if (size <= 0)
		return buffer_invalid_size;
	
	stack->UINT32_element_count = 0;
	stack->UINT32_buffer_size = size;
	stack->p_buffer_base = buffer;
	stack->p_stack_head = buffer;
	return no_error;
}

LIFO_STATUS_t LIFO_PUSH(LIFO_t * stack, DATA_TYPE element)
{
	if (!stack)
		return LIFO_NULL;
	if (stack->UINT32_element_count == stack->UINT32_buffer_size)
		return STACK_FULL;
	
	*(stack->p_stack_head) = element;
	stack->UINT32_element_count++;
	stack->p_stack_head++;
	return no_error;
	
	
}

LIFO_STATUS_t LIFO_POP(LIFO_t * stack, DATA_TYPE * element)
{
	if (!stack)
		return LIFO_NULL;
	if (stack->UINT32_element_count == 0)
		return STACK_EMPTY;
	
	
	stack->p_stack_head--;
	*element = *(stack->p_stack_head);
	stack->UINT32_element_count--;
	return no_error;
	
}