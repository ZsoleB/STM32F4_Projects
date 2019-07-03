/*
 * DAC_Driver.c
 *
 *  Created on: Apr 15, 2019
 *      Author: zsolt.balo
 */

#include "DAC_Driver_Cfg.h"

void DAC_Driver_Init()
{
	RCC->APB1ENR|=RCC_APB1ENR_DACEN;

	/*Stop DACs in case of initialization*/
	DAC->CR &= (DAC_DRIVER_CH1_OFF & DAC_DRIVER_CH1_OFF);

	switch (DAC_SETUP->DAC_Channel_Count)
	{
	case DAC_DRIVER_SINGLE_CHANNEL:
#if(DAC_DRIVER_SELECTED_SINGLE_CHANNEL == DAC_DRIVER_CHANNEL1)
		DAC->CR |= DAC_DRIVER_CH1_WAVE_SELECT(DAC_SETUP->DAC_Output_Signal_Type[DAC_DRIVER_CHANNEL1]);

		/*Select signal type for channel 1*/
		if (DAC_SETUP->DAC_Output_Signal_Type[DAC_DRIVER_CHANNEL1]>DAC_Driver_Output_DEFAULT)
		{
			DAC->CR |= DAC_DRIVER_CH1_SET_AMPLITUDE(DAC_SETUP->DAC_Output_Signal_Amplitude[DAC_DRIVER_CHANNEL1]);
		}
		else
		{
			/*Nothing to do*/
		}

		/*Select trigger source for channel 1, if triggers are enabled*/
		if ((DAC_SETUP->DAC_Trigger_Enable[DAC_DRIVER_CHANNEL1]) == OK )
		{
			/*If the TENx control bit is set, conversion can then be triggered by an external event (timer
			counter, external interrupt line).*/
			/*When a hardware trigger is selected (TENx bit in DAC_CR
			register is set) and a trigger occurs, the transfer is performed three APB1 clock cycles later.*/
			DAC->CR |= DAC_DRIVER_CH1_TRIGGER_ENABLE;
			DAC->CR |= DAC_DRIVER_CH1_TRIGGER_SELECT(DAC_SETUP->DAC_Trigger_Source[DAC_DRIVER_CHANNEL1]);
		}
		else
		{
			DAC->CR &= DAC_DRIVER_CH1_TRIGGER_DISABLE;
		}

		/*Set output buffer for channel 1*/
		if ((DAC_SETUP->DAC_Output_Buffer_Enable[DAC_DRIVER_CHANNEL1]) == OK )
		{
			DAC->CR &= DAC_DRIVER_OUTPUT_BUFFER1_ON;
		}
		else
		{
			DAC->CR |= DAC_DRIVER_OUTPUT_BUFFER1_OFF;
		}

		/*Enable DAC channel 1*/
		DAC->CR |= DAC_DRIVER_CH1_ON;

#elif (DAC_DRIVER_SELECTED_SINGLE_CHANNEL == DAC_DRIVER_CHANNEL2)
		DAC->CR |= DAC_DRIVER_CH2_WAVE_SELECT(DAC_SETUP->DAC_Output_Signal_Type[DAC_DRIVER_CHANNEL1]);

		/*Select signal type for channel 1*/
		if (DAC_SETUP->DAC_Output_Signal_Type[DAC_DRIVER_CHANNEL1]>DAC_Driver_Output_DEFAULT)
		{
			DAC->CR |= DAC_DRIVER_CH2_SET_AMPLITUDE(DAC_SETUP->DAC_Output_Signal_Amplitude[DAC_DRIVER_CHANNEL1]);
		}
		else
		{
			/*Nothing to do*/
		}

		/*Select trigger source for channel 1, if triggers are enabled*/
		if ((DAC_SETUP->DAC_Trigger_Enable[DAC_DRIVER_CHANNEL1]) == OK )
		{
			/*If the TENx control bit is set, conversion can then be triggered by an external event (timer
			counter, external interrupt line).*/
			/*When a hardware trigger is selected (TENx bit in DAC_CR
			register is set) and a trigger occurs, the transfer is performed three APB1 clock cycles later.*/
			DAC->CR |= DAC_DRIVER_CH2_TRIGGER_ENABLE;
			DAC->CR |= DAC_DRIVER_CH2_TRIGGER_SELECT(DAC_SETUP->DAC_Trigger_Source[DAC_DRIVER_CHANNEL1]);
		}
		else
		{
			DAC->CR &= DAC_DRIVER_CH2_TRIGGER_DISABLE;
		}

		/*Set output buffer for channel 1*/
		if ((DAC_SETUP->DAC_Output_Buffer_Enable[DAC_DRIVER_CHANNEL1]) == OK )
		{
			DAC->CR &= DAC_DRIVER_OUTPUT_BUFFER2_ON;
		}
		else
		{
			DAC->CR |= DAC_DRIVER_OUTPUT_BUFFER2_OFF;
		}

		/*Enable DAC channel 1*/
		DAC->CR |= DAC_DRIVER_CH2_ON;
#else
		#error "Wrong single channel selection ! Please choose DAC_DRIVER_CHANNEL1 or DAC_DRIVER_CHANNEL2"
#endif
		break;
	case DAC_DRIVER_TWO_CHANNELS:
		DAC->CR |= DAC_DRIVER_CH1_WAVE_SELECT(DAC_SETUP->DAC_Output_Signal_Type[DAC_DRIVER_CHANNEL1]);
		DAC->CR |= DAC_DRIVER_CH2_WAVE_SELECT(DAC_SETUP->DAC_Output_Signal_Type[DAC_DRIVER_CHANNEL2]);

		/*Select signal type for channel 1*/
		if (DAC_SETUP->DAC_Output_Signal_Type[DAC_DRIVER_CHANNEL1]>DAC_Driver_Output_DEFAULT)
		{
			DAC->CR |= DAC_DRIVER_CH1_SET_AMPLITUDE(DAC_SETUP->DAC_Output_Signal_Amplitude[DAC_DRIVER_CHANNEL1]);
		}
		else
		{
			/*Nothing to do*/
		}

		/*Select signal type for channel 2*/
		if (DAC_SETUP->DAC_Output_Signal_Type[DAC_DRIVER_CHANNEL2]>DAC_Driver_Output_DEFAULT)
		{
			DAC->CR |= DAC_DRIVER_CH2_SET_AMPLITUDE(DAC_SETUP->DAC_Output_Signal_Amplitude[DAC_DRIVER_CHANNEL2]);
		}
		else
		{
			/*Nothing to do*/
		}

		/*Select trigger source for channel 1, if triggers are enabled*/
		if ((DAC_SETUP->DAC_Trigger_Enable[DAC_DRIVER_CHANNEL1]) == OK )
		{
			DAC->CR |= DAC_DRIVER_CH1_TRIGGER_ENABLE;
			DAC->CR |= DAC_DRIVER_CH1_TRIGGER_SELECT(DAC_SETUP->DAC_Trigger_Source[DAC_DRIVER_CHANNEL1]);
		}
		else
		{
			DAC->CR &= DAC_DRIVER_CH1_TRIGGER_DISABLE;
		}

		/*Select trigger source for channel 2, if triggers are enabled*/
		if ((DAC_SETUP->DAC_Trigger_Enable[DAC_DRIVER_CHANNEL2]) == OK )
		{
			DAC->CR |= DAC_DRIVER_CH2_TRIGGER_ENABLE;
			DAC->CR |= DAC_DRIVER_CH2_TRIGGER_SELECT(DAC_SETUP->DAC_Trigger_Source[DAC_DRIVER_CHANNEL2]);
		}
		else
		{
			DAC->CR &= DAC_DRIVER_CH2_TRIGGER_DISABLE;
		}

		/*Set output buffer for channel 1*/
		if ((DAC_SETUP->DAC_Output_Buffer_Enable[DAC_DRIVER_CHANNEL1]) == OK )
		{
			DAC->CR &= DAC_DRIVER_OUTPUT_BUFFER1_ON;
		}
		else
		{
			DAC->CR |= DAC_DRIVER_OUTPUT_BUFFER1_OFF;
		}

		/*Set output buffer for channel 2*/
		if ((DAC_SETUP->DAC_Output_Buffer_Enable[DAC_DRIVER_CHANNEL2]) == OK )
		{
			DAC->CR &= DAC_DRIVER_OUTPUT_BUFFER2_ON;
		}
		else
		{
			DAC->CR |= DAC_DRIVER_OUTPUT_BUFFER2_OFF;
		}

		/*Enable DAC channel 1 and 2*/
		DAC->CR |= (DAC_DRIVER_CH1_ON|DAC_DRIVER_CH2_ON);
		break;
	};
/*	Once the DAC channelx is enabled, the corresponding GPIO pin (PA4 or PA5) is
	automatically connected to the analog converter output (DAC_OUTx). In order to avoid
	parasitic consumption, the PA4 or PA5 pin should first be configured to analog (AIN).*/
}

uint8 DAC_Driver_GetStatus(uint8 DAC_Channel_Number)
{
	uint8 ResultCode = 0x00;

	if(DAC_Channel_Number == DAC_DRIVER_CHANNEL1)
	{
		if ((DAC->SR & DAC_DRIVER_CH1_DMA_UNDERRUN_FLAG)!= 0x00)
		{
			ResultCode = SUCCES;
		}
		else if ((DAC->SR & DAC_DRIVER_CH1_DMA_UNDERRUN_FLAG) == 0x00)
		{
			ResultCode = FAILED;
		}
		else
		{
			ResultCode = FAILED;
		}
	}
	else if(DAC_Channel_Number == DAC_DRIVER_CHANNEL2)
	{
		if ((DAC->SR & DAC_DRIVER_CH2_DMA_UNDERRUN_FLAG) != 0x00)
		{
			ResultCode = SUCCES;
		}
		else if ((DAC->SR & DAC_DRIVER_CH2_DMA_UNDERRUN_FLAG) == 0x00)
		{
			ResultCode = FAILED;
		}
		else
		{
			ResultCode = FAILED;
		}
	}
	else
	{
		/*Nothing to do*/
	}

	return ResultCode;

}

uint16 DAC_Driver_Read_Data_Output(uint8 DAC_Channel_Number)
{
	uint16 result = 0x00;
	/*Get the value stored in the data output buffer*/

	if(	DAC_Channel_Number == DAC_DRIVER_CHANNEL1 )
	{
		result = (uint16)(DAC->DOR1);
	}
	else if( DAC_Channel_Number == DAC_DRIVER_CHANNEL2 )
	{
		result = (uint16)(DAC->DOR2);
	}else
	{
		/*Nothing to do*/
	}

	return result;
}

void DAC_Driver_Write_Buffer(uint8 DAC_Channel_Number)
{
	/*Write multiple values to the data hold register*/
	static uint16 DAC_Driver_Total_Cntr1 = DAC_DRIVER_SAMPLE_SIZE_CH1;
	static uint16 DAC_Driver_Total_Cntr2 = DAC_DRIVER_SAMPLE_SIZE_CH2;
	static uint16 DAC_Driver_Send_Cntr1 = 0x00;
	static uint16 DAC_Driver_Send_Cntr2 = 0x00;

	if((DAC_Channel_Number == DAC_DRIVER_CHANNEL1)&&(DAC_SETUP->DAC_Simultaneous_Write == NOK))
	{
		DAC_Driver_Write_Data(DAC_Channel_Number,DAC_Driver_Data_Buffer_CH1[DAC_Driver_Send_Cntr1]);
		DAC_Driver_Total_Cntr1--;
		DAC_Driver_Send_Cntr1++;

		if(DAC_Driver_Total_Cntr1==0x00)
		{
			DAC_Driver_Total_Cntr1 = DAC_DRIVER_SAMPLE_SIZE_CH1;
			DAC_Driver_Send_Cntr1 = 0x00;
		}
		else
		{
			/*Nothing to do*/
		}
	}
	else if((DAC_Channel_Number == DAC_DRIVER_CHANNEL2)&&(DAC_SETUP->DAC_Simultaneous_Write == NOK))
	{
		DAC_Driver_Write_Data(DAC_Channel_Number,DAC_Driver_Data_Buffer_CH2[DAC_Driver_Send_Cntr2]);
		DAC_Driver_Total_Cntr2--;
		DAC_Driver_Send_Cntr2++;

		if(DAC_Driver_Total_Cntr2==0x00)
		{
			DAC_Driver_Total_Cntr2 = DAC_DRIVER_SAMPLE_SIZE_CH2;
			DAC_Driver_Send_Cntr2 = 0x00;
		}
		else
		{
			/*Nothing to do*/
		}
	}
	else if(DAC_SETUP->DAC_Simultaneous_Write == OK)
	{
		DAC_Driver_Simultaneous_Write_Data(DAC_Channel_Number,DAC_Driver_Data_Buffer_CH1[DAC_Driver_Send_Cntr1],DAC_Driver_Data_Buffer_CH2[DAC_Driver_Send_Cntr2]);
		DAC_Driver_Total_Cntr1--;
		DAC_Driver_Total_Cntr2--;
		DAC_Driver_Send_Cntr1++;
		DAC_Driver_Send_Cntr2++;

		if((DAC_Driver_Total_Cntr1==0x00) && (DAC_Driver_Total_Cntr2!=0x00))
		{
			DAC_Driver_Total_Cntr1 = DAC_DRIVER_SAMPLE_SIZE_CH1;
			DAC_Driver_Send_Cntr1 = 0x00;
		}
		else if((DAC_Driver_Total_Cntr1!=0x00) && (DAC_Driver_Total_Cntr2==0x00))
		{
			DAC_Driver_Total_Cntr2 = DAC_DRIVER_SAMPLE_SIZE_CH2;
			DAC_Driver_Send_Cntr2 = 0x00;
		}
		else if((DAC_Driver_Total_Cntr1==0x00) && (DAC_Driver_Total_Cntr2==0x00))
		{
			DAC_Driver_Total_Cntr1 = DAC_DRIVER_SAMPLE_SIZE_CH1;
			DAC_Driver_Total_Cntr2 = DAC_DRIVER_SAMPLE_SIZE_CH2;
			DAC_Driver_Send_Cntr1 = 0x00;
			DAC_Driver_Send_Cntr2 = 0x00;
		}
		else
		{
			/*Nothing to do*/
		}
	}
	else
	{
		/*Nothing to do*/
	}
}

void DAC_Driver_Write_Data(uint8 DAC_Channel_Number,uint16 DAC_Output_value)
{
	/*
	 - DACout = Vref X (DOR/4096)
	 - Fout = TIMx_TRGO/sample_number(If the TIMx_TRGO output frequency is 1 MHz and there are 10 samples to be used,
	  the frequency of the sine wave generated by the DAC is 100 kHz.)
	 */

	if (DAC_Channel_Number == DAC_DRIVER_CHANNEL1)
	{
		switch (DAC_SETUP->DAC_Data_Alignment[DAC_Channel_Number])
		{
		case DAC_Driver_8Bit_Right_Alignment:
			DAC->DHR8R1 = ((uint8)DAC_Output_value & 0xFF);
			break;
		case DAC_Driver_12Bit_Left_Alignment:
			DAC->DHR12L1 = ((DAC_Output_value & 0xFFF)<<0x04);
			break;
		case DAC_Driver_12Bit_Right_Alignment:
			DAC->DHR12R1 = (DAC_Output_value & 0xFFF);
			break;
		};
	}
	else if (DAC_Channel_Number == DAC_DRIVER_CHANNEL2)
	{
		switch (DAC_SETUP->DAC_Data_Alignment[DAC_Channel_Number])
		{
		case DAC_Driver_8Bit_Right_Alignment:
			DAC->DHR8R2 = ((uint8)DAC_Output_value & 0xFF);
			break;
		case DAC_Driver_12Bit_Left_Alignment:
			DAC->DHR12L2 = ((DAC_Output_value & 0xFFF)<<0x04);
			break;
		case DAC_Driver_12Bit_Right_Alignment:
			DAC->DHR12R2 = (DAC_Output_value & 0xFFF);
			break;
		};
	}
	else
	{
		/*Nothing to do*/
	}
}

void DAC_Driver_Simultaneous_Write_Data(uint8 DAC_Channel_Number,uint16 DAC_Output_value1,uint16 DAC_Output_value2)
{
	/*The Alignment should be the same for both channels !*/
	switch(DAC_SETUP->DAC_Data_Alignment[DAC_DRIVER_CHANNEL1])
	{
		case DAC_Driver_8Bit_Right_Alignment:
			DAC->DHR8RD = (((uint8)DAC_Output_value1 & 0xFF)|(((uint8)(DAC_Output_value2 & 0xFF))<<0x08));
			break;
		case DAC_Driver_12Bit_Left_Alignment:
			DAC->DHR12LD = (((DAC_Output_value1 & 0xFFF)<<0x04)|((DAC_Output_value2 & 0xFFF)<<0x14));
			break;
		case DAC_Driver_12Bit_Right_Alignment:
			DAC->DHR12RD = ((DAC_Output_value1 & 0xFFF)|((DAC_Output_value2 & 0xFFF)<<0x10));
			break;
	};
}

void DAC_Driver_SW_Start(uint8 DAC_Channel_Number)
{
	/*When software trigger is selected, the transfer from the DAC_DHRx register to the
	DAC_DORx register takes only one APB1 clock cycle.*/

	if(DAC_Channel_Number == DAC_DRIVER_CHANNEL1)
	{
		DAC->SWTRIGR|=DAC_DRIVER_SW_TRIGGER_CH1;
	}
	else if(DAC_Channel_Number == DAC_DRIVER_CHANNEL2)
	{
		DAC->SWTRIGR|=DAC_DRIVER_SW_TRIGGER_CH2;
	}
	else
	{
		/*Nothing to do*/
	}
}
