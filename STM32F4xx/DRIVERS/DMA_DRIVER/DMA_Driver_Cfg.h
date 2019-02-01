/*
 * DMA_Driver_Cfg.h
 *
 *  Created on: Aug 14, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_DMA_DRIVER_DMA_DRIVER_CFG_H_
#define DRIVERS_DMA_DRIVER_DMA_DRIVER_CFG_H_

#include "DMA_Driver.h"

#define DMA_DRIVER_DMA1								NOK
#define DMA_DRIVER_DMA2								OK
#define DMA_DRIVER_CHANNEL_INSTANCE_NUM 			((uint32)0x01)

typedef enum
{
	DMA_DRIVER_1
}DMA_Driver_Instances;

typedef enum
{
	DMA_DRIVER_STREAM_1
}DMA_Driver_Stream_Instances;

#endif /* DRIVERS_DMA_DRIVER_DMA_DRIVER_CFG_H_ */
