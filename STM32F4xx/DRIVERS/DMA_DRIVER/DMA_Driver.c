/*
 * DMA_Driver_Cfg.c
 *
 *  Created on: Aug 14, 2018
 *      Author: zsolt.balo
 */

#include "DMA_Driver_Cfg.h"

void DMA_Driver_Init()
{
	uint16 index = 0x00;
	uint16 index1 = 0x00;

	/*	Initialization of the selected DMA*/
	/*	Enable the DMA in the AHB bus*/
	#if (DMA_DRIVER_DMA1 == OK)
		RCC->AHB1ENR|=RCC_AHB1ENR_DMA1EN;
	#endif

	#if (DMA_DRIVER_DMA2 == OK)
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	#endif

	for (index = 0x00; index < DMA_DRIVER_CHANNEL_INSTANCE_NUM; index++)
	{
		for (index1 = 0x00; index1 < DMA_SETUP[index].DMA_Driver_Stream_Nr;
				index1++)
		{
			/*	Shut down the DMA before setup*/
			DMA_Driver_Stop(index, index1);

			/* 	Wait for the EN bit to be cleared before starting any stream configuration*/
			while ((DMA_SETUP[index].DMA_Stream[index1]->CR & 0x01) != 0x00);

			/*	Select the request channel*/
			DMA_SETUP[index].DMA_Stream[index1]->CR |=
					DMA_SETUP[index].DMA_Stream_selected_channel[index1];

			/*	Memory burst mode configuration*/
			/*	In direct mode, these bits are forced to 0x0 by hardware as soon as bit EN= '1'*/
			DMA_SETUP[index].DMA_Stream[index1]->CR |=
					DMA_SETUP[index].DMA_Stream_memory_burst[index1];

			/*	Peripheral burst mode configuration*/
			/*	In direct mode, these bits are forced to 0x0 by hardware as soon as bit EN= '1'*/
			DMA_SETUP[index].DMA_Stream[index1]->CR |=
					DMA_SETUP[index].DMA_Stream_peripheral_burst[index1];

			/*	Double buffer mode configuration*/
			DMA_SETUP[index].DMA_Stream[index1]->CR |=
					DMA_SETUP[index].DMA_Stream_duble_buffering[index1];

			/*	DMA direction*/
			/*	When memory-to-memory mode is used, the Circular and direct modes are not allowed.
			 Only the DMA2 controller is able to perform memory-to-memory transfers.*/
			DMA_SETUP[index].DMA_Stream[index1]->CR |=
					DMA_SETUP[index].DMA_Stream_direction[index1];

			/*	DMA running Mode*/
			DMA_SETUP[index].DMA_Stream[index1]->CR |=
					DMA_SETUP[index].DMA_Stream_running_mode[index1];

			/*	DMA Channel priority*/
			DMA_SETUP[index].DMA_Stream[index1]->CR |=
					DMA_SETUP[index].DMA_Stream_channel_priority[index1];

			/*	DMA Memory size*/
			DMA_SETUP[index].DMA_Stream[index1]->CR |=
					DMA_SETUP[index].DMA_Stream_memmory_size[index1];

			/*	DMA Peripheral size*/
			DMA_SETUP[index].DMA_Stream[index1]->CR |=
					DMA_SETUP[index].DMA_Stream_peripheral_size[index1];

			/*	DMA Memory increment mode*/

			DMA_SETUP[index].DMA_Stream[index1]->CR |=
					DMA_SETUP[index].DMA_Stream_memmory_increment[index1];

			/*	DMA Peripheral increment mode*/
			DMA_SETUP[index].DMA_Stream[index1]->CR |=
					DMA_SETUP[index].DMA_Stream_peripheral_increment[index1];

			/*	DMA Tx count*/
			DMA_SETUP[index].DMA_Stream[index1]->NDTR =
					DMA_SETUP[index].DMA_Stream_tx_count[index1];

			/*	Set Direct mode*/
			/*	This bit is set by hardware if the memory-to-memory mode is selected (DIR bit in
			 DMA_SxCR are "10") and the EN bit in the DMA_SxCR register is '1' because the direct
			 mode is not allowed in the memory-to-memory configuration.*/
			DMA_SETUP[index].DMA_Stream[index1]->FCR |=
					DMA_SETUP[index].DMA_Stream_direct_mode[index1];

			/*	Set FIFO threshold*/
			DMA_SETUP[index].DMA_Stream[index1]->FCR |=
					DMA_SETUP[index].DMA_Stream_fifo_threshold[index1];
		}
	}
}
void DMA_Driver_SetBuffers(uint8 DMA_instance_number, uint8 DMA_Channel_number,
uint32* Tx_Buffer,
uint32* Rx_Buffer)
{
	if (DMA_SETUP[DMA_instance_number].DMA_Stream_direction[DMA_Channel_number]
			== DMA_DRIVER_DIRECTION_FROM_PERIPHERAL)
	{

		/*	DMA Peripheral address*/
		DMA_SETUP[DMA_instance_number].DMA_Stream[DMA_Channel_number]->PAR =
				(uint32_t) (Tx_Buffer);

		/*	DMA Memory address*/
		DMA_SETUP[DMA_instance_number].DMA_Stream[DMA_Channel_number]->M0AR =
				(uint32_t) (Rx_Buffer);
	}
	else if (DMA_SETUP[DMA_instance_number].DMA_Stream_direction[DMA_Channel_number]
			== DMA_DRIVER_DIRECTION_FROM_MEMORY)
	{

		/*	DMA Peripheral address*/
		DMA_SETUP[DMA_instance_number].DMA_Stream[DMA_Channel_number]->PAR =
				(uint32_t) (Rx_Buffer);

		/*	DMA Memory address*/
		DMA_SETUP[DMA_instance_number].DMA_Stream[DMA_Channel_number]->M0AR =
				(uint32_t) (Tx_Buffer);
	}
	else
	{

		/*	DMA Peripheral address*/
		DMA_SETUP[DMA_instance_number].DMA_Stream[DMA_Channel_number]->PAR =
				(uint32_t) (Tx_Buffer);

		/*	DMA Memory address*/
		DMA_SETUP[DMA_instance_number].DMA_Stream[DMA_Channel_number]->M0AR =
				(uint32_t) (Rx_Buffer);
	}
}

void DMA_Driver_Start(uint8 DMA_instance_number, uint8 DMA_Channel_number)
{
	/*	DMA Mode -> Enable*/
	DMA_SETUP[DMA_instance_number].DMA_Stream[DMA_Channel_number]->CR |= (0x01);
}

void DMA_Driver_Stop(uint8 DMA_instance_number, uint8 DMA_Channel_number)
{
	/*	Shut down the DMA 	*/
	DMA_SETUP[DMA_instance_number].DMA_Stream[DMA_Channel_number]->CR &=
			(~(0x01));
}
