// this is a circular FIFO buffer
// made by hazem shaaban

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#ifndef FIFO_H_
#define FIFO_H_

// for portability
#define DATA_TYPE int

typedef struct
{
    uint32_t size;
    uint32_t element_count;
    DATA_TYPE * HEAD;
    DATA_TYPE * TAIL;
    DATA_TYPE * BASE;
}FIFO_t;

typedef enum{
	no_error,
	element_added,
	element_removed,
	FIFO_NULL,
	buffer_invalid_size,
	QUEUE_FULL,
	QUEUE_EMPTY
}FIFO_STATUS_t;


FIFO_STATUS_t FIFO_INIT(FIFO_t * queue, DATA_TYPE * buffer, uint32_t size);
FIFO_STATUS_t FIFO_ADD(FIFO_t * queue, DATA_TYPE element);
FIFO_STATUS_t FIFO_REMOVE(FIFO_t * queue, DATA_TYPE * element);




#endif
