/** \addtogroup UART
 * \brief UART drivers for stm32l4xx devices.
 *  @{
 */

#ifndef RINGBUF_H
#define RINGBUF_H

#include "common.h"

/***
*
* Ringbuffer implementation.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
* STM32 Reference Manual: RM0432
*
***/

/****************************************************************************************************/
/*			                  TYPEDEFS                                                  */
/****************************************************************************************************/

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
	volatile uint8_t buffer_full;
	volatile uint8_t buffer_empty;
} RING_BUF_Typedef;


/****************************************************************************************************/
/*				        FUNCTION PROTOTYPES                                         */
/****************************************************************************************************/

/**@brief Initializes the ring buffer object.
* @param buffer_address Pointer to the buffer that is used internally for the ring buffer.
* @param max_size size of the buffer.
* @return Ring buffer object.
*/
RING_BUF_Typedef RING_BUF_init(void* buffer_address, uint32_t max_size);


/**@brief Write one byte to the head of the ring buffer.
* @param ring_buf pointer to the ring buffer object.
* @param byte byte to be written
* @retval RING_BUF_WRITE_ERROR The buffer is full and cannot be written to.
* @retval RING_BUF_OK OK
*/
RING_BUF_Status_State RING_BUF_writeByteToHead(RING_BUF_Typedef* ring_buf, uint8_t byte);


/**@brief Read one byte from the tail of the ring buffer.
* @param ring_buf pointer to the ring buffer object.
* @param byte byte to be written
* @retval RING_BUF_READ_ERROR The buffer is empty and cannot be read from.
* @retval RING_BUF_OK OK
*/
RING_BUF_Status_State RING_BUF_readByteFromTail(RING_BUF_Typedef* ring_buf, uint8_t* byte);


/**@brief Returns whether or not the ring buffer is empty.
* @param ring_buf pointer to the ring buffer object.
* @returns boolean describing if the ring buffer is empty.
*/
uint8_t RING_BUF_isEmpty(RING_BUF_Typedef* ring_buf);


uint32_t RING_BUF_size(RING_BUF_Typedef* ring_buf);

#endif