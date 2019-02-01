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

#define DMA_DRIVER_NORMAL_MODE									(0x00)
#define DMA_DRIVER_CIRCULAR_MODE								(0x01)
#define DMA_DRIVER_CHANNEL_PRIORITY_LOW							(0x00<<0x0C)
#define DMA_DRIVER_CHANNEL_PRIORITY_MEDIUM						(0x01<<0x0C)
#define DMA_DRIVER_CHANNEL_PRIORITY_HIGH						(0x02<<0x0C)
#define DMA_DRIVER_CHANNEL_PRIORITY_VERY_HIGH					(0x03<<0x0C)
#define DMA_DRIVER_MEMMORY_SIZE_8_BITS							(0x00<<0x0A)
#define DMA_DRIVER_MEMMORY_SIZE_16_BITS                         (0x01<<0x0A)
#define DMA_DRIVER_MEMMORY_SIZE_32_BITS                         (0x02<<0x0A)
#define DMA_PERIPHERAL_SIZE_8_bits                              (0x00<<0x08)
#define DMA_PERIPHERAL_SIZE_16_bits                             (0x01<<0x08)
#define DMA_PERIPHERAL_SIZE_32_bits                             (0x02<<0x08)
#define DMA_DRIVER_DIRECTION_FROM_PERIPHERAL					(0x00)
#define DMA_DRIVER_DIRECTION_FROM_MEMORY                        (0x01)
#define DMA_DRIVER_TX_COUNT 									(uint16)(0x0A)

void DMA_Driver_Init(DMA_Channel_TypeDef * DMA_Channelx);
void DMA_Driver_SetBuffers(DMA_Channel_TypeDef * DMA_Channelx,uint32* Tx_Buffer,uint32* Rx_Buffer);
void DMA_Driver_Start(DMA_Channel_TypeDef * DMA_Channelx);
void DMA_Driver_Stop(DMA_Channel_TypeDef * DMA_Channelx);

#endif /* DRIVERS_DMA_DRIVER_DMA_DRIVER_H_ */
