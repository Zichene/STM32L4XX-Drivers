#include "ringbuffer.h"

/***
*
* Ringbuffer implementation.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
* STM32 Reference Manual: RM0432
*
***/


RING_BUF_Typedef RING_BUF_init(void* buffer_address, uint32_t max_size) {
	RING_BUF_Typedef ring_buf = {
		.buffer_address = buffer_address,
		.max_size = max_size,
		.head_index = 0,
		.tail_index = 0,
	};

	return ring_buf;
}


RING_BUF_Status_State RING_BUF_writeByteToHead(RING_BUF_Typedef* ring_buf, uint8_t byte) {
	uint8_t* buffer = (uint8_t*) ring_buf->buffer_address;
	uint32_t head = ring_buf->head_index;
	uint32_t tail = ring_buf->tail_index;
	uint32_t size = ring_buf->max_size;
	
	/* check if buffer is full */
	uint32_t next_head_index = (head + 1) % (size);
	if (next_head_index == tail) return RING_BUF_WRITE_ERROR;
	
	/* write to ring buffer and increment head index with modulo */
	buffer[head] = byte;
	ring_buf->head_index = next_head_index;
	return RING_BUF_OK;
}

RING_BUF_Status_State RING_BUF_readByteFromTail(RING_BUF_Typedef* ring_buf, uint8_t* byte) {
	uint8_t* buffer = (uint8_t*) ring_buf->buffer_address;
	uint32_t tail = ring_buf->tail_index;
	uint32_t size = ring_buf->max_size;
	
	/* check if buffer is empty */
	if (RING_BUF_isEmpty(ring_buf)) return RING_BUF_READ_ERROR;
	
	/* read from ring buffer and increment tail index with modulo */
	*byte = buffer[tail];
	ring_buf->tail_index = (tail + 1) % size;
	return RING_BUF_OK;
}


uint8_t RING_BUF_isEmpty(RING_BUF_Typedef* ring_buf) {
	return ring_buf->head_index == ring_buf->tail_index;
}


uint32_t RING_BUF_size(RING_BUF_Typedef* ring_buf) {
	uint32_t head = ring_buf->head_index;
	uint32_t tail = ring_buf->tail_index;
	
	if (head >= tail) return head-tail;
	else return (ring_buf->max_size - (tail-head));
}