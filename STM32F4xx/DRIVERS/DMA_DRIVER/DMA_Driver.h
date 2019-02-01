/*
 * DMA_Driver.h
 *
 *  Created on: Aug 14, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_DMA_DRIVER_DMA_DRIVER_H_
#define DRIVERS_DMA_DRIVER_DMA_DRIVER_H_

#include "stm32f4xx.h"
#include "StdTypes.h"

#define DMA_DRIVER_NORMAL_MODE									(0x00<<0x08)
#define DMA_DRIVER_CIRCULAR_MODE								(0x01<<0x08)
#define DMA_DRIVER_CHANNEL_PRIORITY_LOW							(0x00<<0x10)
#define DMA_DRIVER_CHANNEL_PRIORITY_MEDIUM						(0x01<<0x10)
#define DMA_DRIVER_CHANNEL_PRIORITY_HIGH						(0x02<<0x10)
#define DMA_DRIVER_CHANNEL_PRIORITY_VERY_HIGH					(0x03<<0x10)
#define DMA_DRIVER_MEMMORY_SIZE_8_BITS							(0x00<<0x0D)
#define DMA_DRIVER_MEMMORY_SIZE_16_BITS                         (0x01<<0x0D)
#define DMA_DRIVER_MEMMORY_SIZE_32_BITS                         (0x02<<0x0D)
#define DMA_DRIVER_PERIPHERAL_SIZE_8_BITS                       (0x00<<0x0B)
#define DMA_DRIVER_PERIPHERAL_SIZE_16_BITS                      (0x01<<0x0B)
#define DMA_DRIVER_PERIPHERAL_SIZE_32_BITS                      (0x02<<0x0B)
#define DMA_DRIVER_FIFO_THRESHOLD_1DIV4                         (0x00)
#define DMA_DRIVER_FIFO_THRESHOLD_1DIV2                         (0x01)
#define DMA_DRIVER_FIFO_THRESHOLD_3DIV4                         (0x02)
#define DMA_DRIVER_FIFO_THRESHOLD_FULL                          (0x03)
#define DMA_DRIVER_DIRECTION_FROM_PERIPHERAL					(0x00<<0x06)
#define DMA_DRIVER_DIRECTION_FROM_MEMORY                        (0x01<<0x06)
#define DMA_DRIVER_DIRECTION_MEMORY_TO_MEMORY                   (0x02<<0x06)
#define DMA_DRIVER_PERIPHERAL_BURST_SINGLE_TRANSFER				(0x00<<0x15)
#define DMA_DRIVER_PERIPHERAL_BURST_TRANSFER_INCR4				(0x01<<0x15)
#define DMA_DRIVER_PERIPHERAL_BURST_TRANSFER_INCR8				(0x02<<0x15)
#define DMA_DRIVER_PERIPHERAL_BURST_TRANSFER_INCR16				(0x03<<0x15)
#define DMA_DRIVER_MEMORY_BURST_SINGLE_TRANSFER					(0x00<<0x17)
#define DMA_DRIVER_MEMORY_BURST_TRANSFER_INCR4					(0x01<<0x17)
#define DMA_DRIVER_MEMORY_BURST_TRANSFER_INCR8					(0x02<<0x17)
#define DMA_DRIVER_MEMORY_BURST_TRANSFER_INCR16					(0x03<<0x17)
#define DMA_DRIVER_DUBLE_BUFFERING_DISABLE						(0x00<<0x12)
#define DMA_DRIVER_DUBLE_BUFFERING_ENABLE						(0x01<<0x12)
#define DMA_DRIVER_MEMMORY_INCREMENT_ENABLE						(0x01<<0x0A)
#define DMA_DRIVER_MEMMORY_INCREMENT_DISABLE					(0x00<<0x0A)
#define DMA_DRIVER_PERIPHERAL_INCREMENT_ENABLE					(0x01<<0x09)
#define DMA_DRIVER_PERIPHERAL_INCREMENT_DISABLE					(0x00<<0x09)
#define DMA_DRIVER_REQ_CHANNEL_0								(0x00<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_1								(0x01<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_2								(0x02<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_3								(0x03<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_4								(0x04<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_5								(0x05<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_6								(0x06<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_7								(0x07<<0x19)
#define DMA_DRIVER_DIRECT_MODE_DISABLE							(0x01<<0x02)
#define DMA_DRIVER_DIRECT_MODE_ENABLE							(0x00<<0x02)
#define DMA1_DRIVER_STREAM_0									DMA1_Stream0
#define DMA1_DRIVER_STREAM_1									DMA1_Stream1
#define DMA1_DRIVER_STREAM_2									DMA1_Stream2
#define DMA1_DRIVER_STREAM_3									DMA1_Stream3
#define DMA1_DRIVER_STREAM_4									DMA1_Stream4
#define DMA1_DRIVER_STREAM_5									DMA1_Stream5
#define DMA1_DRIVER_STREAM_6									DMA1_Stream6
#define DMA1_DRIVER_STREAM_7									DMA1_Stream7
#define DMA2_DRIVER_STREAM_0									DMA2_Stream0
#define DMA2_DRIVER_STREAM_1									DMA2_Stream1
#define DMA2_DRIVER_STREAM_2									DMA2_Stream2
#define DMA2_DRIVER_STREAM_3									DMA2_Stream3
#define DMA2_DRIVER_STREAM_4									DMA2_Stream4
#define DMA2_DRIVER_STREAM_5									DMA2_Stream5
#define DMA2_DRIVER_STREAM_6									DMA2_Stream6
#define DMA2_DRIVER_STREAM_7									DMA2_Stream7


typedef struct
{
	DMA_TypeDef* DMA_Driver_Instance;
	uint8 DMA_Driver_Stream_Nr;
	DMA_Stream_TypeDef* DMA_Stream[8];
	uint32 DMA_Stream_selected_channel[8];
	uint32 DMA_Stream_channel_priority[8];
	uint32 DMA_Stream_duble_buffering[8];
	uint32 DMA_Stream_memory_burst[8];
	uint32 DMA_Stream_peripheral_burst[8];
	uint16 DMA_Stream_running_mode[8];
	uint16 DMA_Stream_direct_mode[8];
	uint16 DMA_Stream_fifo_threshold[8];
	uint16 DMA_Stream_memmory_size[8];
	uint16 DMA_Stream_peripheral_size[8];
	uint16 DMA_Stream_memmory_increment[8];
	uint16 DMA_Stream_peripheral_increment[8];
	uint16 DMA_Stream_direction[8];
	uint16 DMA_Stream_tx_count[8];
}DMA_Driver_Setup_Type;

extern DMA_Driver_Setup_Type* DMA_SETUP;

void DMA_Driver_Init();
void DMA_Driver_SetBuffers(uint8 DMA_instance_number,uint8 DMA_Channel_number,uint32* Tx_Buffer,uint32* Rx_Buffer);
void DMA_Driver_Start(uint8 DMA_instance_number,uint8 DMA_Channel_number);
void DMA_Driver_Stop(uint8 DMA_instance_number,uint8 DMA_Channel_number);


#endif /* DRIVERS_DMA_DRIVER_DMA_DRIVER_H_ */
