/*

 * DMA_Driver_Cfg.c
 *
 *  Created on: Aug 14, 2018
 *      Author: zsolt.balo


#include "DMA_Driver_Cfg.h"

void DMA_Driver_Init(DMA_Channel_TypeDef * DMA_Channelx)
{
		Initialization of the selected DMA
		Enable the DMA in the AHB bus
		RCC->AHBENR|=RCC_AHBPeriph_DMA1;

		Shut down the DMA before setup
		DMA_Driver_Stop(DMA_Channelx);

		DMA running Mode
		#if(DMA_DRIVER_RUNNING_MODE == DMA_DRIVER_NORMAL_MODE)
			DMA1_Channel1->CCR &= (~(0x01<<5));
		#elif(DMA_DRIVER_RUNNING_MODE == DMA_DRIVER_CIRCULAR_MODE)
			DMA1_Channel1->CCR |= (0x01<<5);
		#endif

		DMA memory 2 memory mode functionality
		#if(DMA_DRIVER_MEMMORY_TO_MEMMORY_FUNCTIONALITY == OK)
			DMA1_Channel1->CCR |= (0x01<<0x0E);
		#else
			DMA1_Channel1->CCR &= (~(0x01<<0x0E));
		#endif

		DMA Channel priority
		DMA1_Channel1->CCR |= DMA_DRIVER_CHANNEL_PRIORITY_MEDIUM;

		DMA Memory size
		DMA1_Channel1->CCR |= DMA_DRIVER_MEMMORY_SIZE_32_BITS;

		DMA Peripheral size
		DMA1_Channel1->CCR |= DMA_PERIPHERAL_SIZE_8_bits;

		DMA Memory increment mode
		#if(DMA_DRIVER_MEMMORY_INCREMENT == OK)
			DMA1_Channel1->CCR |= (0x01<<0x07);
		#else
			DMA1_Channel1->CCR &= (~(0x01<<0x07));
		#endif

		DMA Peripheral increment mode
		#if(DMA_DRIVER_PERIPHERAL_INCREMENT == OK)
			DMA1_Channel1->CCR |= (0x01<<0x06);
		#else
			DMA1_Channel1->CCR &= (~(0x01<<0x06));
		#endif

		DMA direction
		#if(DMA_DRIVER_DIRECTION == DMA_DRIVER_DIRECTION_FROM_MEMORY)
			DMA1_Channel1->CCR |= (0x01<<4);
		#elif(DMA_DRIVER_DIRECTION == DMA_DRIVER_DIRECTION_FROM_PERIPHERAL)
			DMA1_Channel1->CCR &= (~(0x01<<4));
		#endif

		DMA Tx count
		DMA1_Channel1->CNDTR = (uint16_t)DMA_DRIVER_TX_COUNT;
}
void DMA_Driver_SetBuffers(DMA_Channel_TypeDef * DMA_Channelx,uint32* Tx_Buffer,uint32* Rx_Buffer)
{
	#if(DMA_DRIVER_DIRECTION == DMA_DRIVER_DIRECTION_FROM_PERIPHERAL)

		DMA Peripheral address
		DMA1_Channel1->CPAR = (uint32_t)(Tx_Buffer);

		DMA Memory address
		DMA1_Channel1->CMAR = (uint32_t)(Rx_Buffer);

	#elif(DMA_DRIVER_DIRECTION == DMA_DRIVER_DIRECTION_FROM_MEMORY)

		DMA Peripheral address
		DMA1_Channel1->CPAR = (uint32_t)(Rx_Buffer);

		DMA Memory address
		DMA1_Channel1->CMAR = (uint32_t)(Tx_Buffer);
	#endif
}

void DMA_Driver_Start(DMA_Channel_TypeDef * DMA_Channelx)
{
		DMA Mode -> Enable
		DMA1_Channel1->CCR |= (0x01);
}

void DMA_Driver_Stop(DMA_Channel_TypeDef * DMA_Channelx)
{
		Shut down the DMA
		DMA1_Channel1->CCR &= (~(0x01));
}
*/
