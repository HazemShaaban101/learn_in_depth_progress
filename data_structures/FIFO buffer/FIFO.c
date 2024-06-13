// this is a circular FIFO buffer
// made by hazem shaaban


#include "FIFO.h"

FIFO_STATUS_t FIFO_INIT(FIFO_t * queue, DATA_TYPE * buffer, uint32_t size)
{
	if (!buffer)
		return FIFO_NULL;
	if (size <= 0)
		return buffer_invalid_size;
	
	queue->size = size;
	queue->element_count = 0;
	queue->HEAD = buffer;
	queue->TAIL = buffer;
	queue->BASE = buffer;
	return no_error;
}

FIFO_STATUS_t FIFO_ADD(FIFO_t * queue, DATA_TYPE element)
{
	if (!queue)
		return FIFO_NULL;
	
	if (queue->element_count == queue->size)
		return QUEUE_FULL;
	
	*(queue->HEAD) = element;
	queue->element_count++;
	if (queue->HEAD == queue->BASE + (queue->size - 1))
		queue->HEAD = queue->BASE;
	else
		queue->HEAD++;
	
	return no_error;
}

FIFO_STATUS_t FIFO_REMOVE(FIFO_t * queue, DATA_TYPE * element)
{
	if (!queue)
		return FIFO_NULL;
	
	if (queue->element_count == 0)
		return QUEUE_EMPTY;
	
	*element = *(queue->TAIL);
	queue->element_count--;
	if (queue->TAIL == queue->BASE + (queue->size - 1))
		queue->TAIL = queue->BASE;
	else
		queue->TAIL++;
	
	return no_error;
}