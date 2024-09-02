#include "common.h"

/**@brief Enum representing various statuses associated with the ring buffer functions.
*/
typedef enum {
	RING_BUF_OK = 0, ///< Indicates that a function has returned successfully.
	RING_BUF_READ_ERROR = 1, ///< Indicates that there has been a read error (e.g. the buffer contains nothing to be read).
	RING_BUF_WRITE_ERROR = 2, ///< Indicates that there has been a write error (e.g. the buffer is full).
} RING_BUF_Status_State;

/**@brief Struct representing a ring buffer object.
*/
typedef struct {
	void* buffer_address;
	uint32_t max_size;
	uint32_t head_index;
	uint32_t tail_index;
} RING_BUF_Typedef;



RING_BUF_Typedef RING_BUF_init(void* buffer_address, uint32_t max_size);

RING_BUF_Status_State RING_BUF_writeByteToHead(RING_BUF_Typedef* ring_buf, uint8_t byte);

RING_BUF_Status_State RING_BUF_readByteFromTail(RING_BUF_Typedef* ring_buf, uint8_t* byte);
