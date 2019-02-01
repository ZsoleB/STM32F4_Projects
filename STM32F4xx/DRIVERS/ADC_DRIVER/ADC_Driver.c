/*
 * ADC_Driver.c
 *
 *  Created on: Jan 22, 2018
 *      Author: zsolt.balo
 */

#include "ADC_Driver_Cfg.h"

void ADC_Driver_Init()
{
	uint16 index = 0x00;
	uint16 index1 = 0x00;

	#if ADC_DRIVER_ADC1 == OK
		RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;
	#endif
	#if ADC_DRIVER_ADC2 == OK
		RCC->APB2ENR|=RCC_APB2ENR_ADC2EN;
	#endif

	for(index=0x00;index<ADC_DRIVER_INSTANCE_NUM;index++)
	{
		/*Select the frequency of the clock to the ADCs*/
		RCC->CFGR |= ADC_DRIVER_PRESCALE;

		if (ADC_SETUP[index].ADC_Single_Conversion == OK)
		{

			/*In Single conversion mode the ADC does one conversion. This mode is started either by
			setting the ADON bit in the ADC_CR2 register (for a regular channel only) or by external
			trigger (for a regular or injected channel), while the CONT bit is 0.*/

			ADC_SETUP[index].ADC_Instance->CR2|=ADC_DRIVER_EXTERNAL_TRIGGER_ENABLE|ADC_DRIVER_EXTERNAL_TRIGGER_SWSTART;

		}

		/*Set the alignment*/

		ADC_SETUP[index].ADC_Instance->CR2|=ADC_SETUP[index].ADC_Alignment;

		if (ADC_SETUP[index].ADC_Discontinuous_Mode == OK)
		{
			/*Discontinuous read for multiple channels, each channel will be read
	  		  sequentially one by one after the order given in SQRx.
	  		  Because DISCNUM=0x00 only one channel will be read at once,
	  		  otherwise (DISCNUM=n) n reads will be made.
			 */

			ADC_SETUP[index].ADC_Instance->CR1|=ADC_DRIVER_DISCONTINUOUS_MODE_ENABLE;

		}

		/*Select the chosen channel's sampling time*/
		/*The sampling is used for the calculation of the conversion time

		  Tconv = (12.5 + Sampling_time)
		  Sampling_Frequency = 1/Tconv

		 *Example:
			With an ADCCLK = 14 MHz and a sampling time of 1.5 cycles:
			Tconv = 1.5 + 12.5 = 14 cycles = 1 �s

			The default is 1.5 cycles
		 */

		/*Check the selected ADC instance channel numbers, assign the sampling times and the sequences according to the data sheet. */

		for(index1=0x00;index1<ADC_SETUP[index].ADC_Channel_nr;index1++)
		{
			if(ADC_SETUP[index].ADC_Channels[index1] < 0x0A)
			{
				ADC_SETUP[index].ADC_Instance->SMPR2|=((uint32_t)(ADC_SETUP[index].ADC_Channel_SampligTime[index1]<<(3*ADC_SETUP[index].ADC_Channels[index1])));
			}else
			{
				ADC_SETUP[index].ADC_Instance->SMPR1|=((uint32_t)(ADC_SETUP[index].ADC_Channel_SampligTime[index1]<<(3*(ADC_SETUP[index].ADC_Channels[index1]-0x0A))));
			}

			#if(ADC_DRIVER_SEQUENTIAL_READ == OK)

				if(ADC_SETUP[index].ADC_Channel_Position[index1]<=0x05)
				{
					ADC_SETUP[index].ADC_Instance->SQR3|=((ADC_SETUP[index].ADC_Channels[index1])<<(5*ADC_SETUP[index].ADC_Channel_Position[index1]));
				}
				else if((ADC_SETUP[index].ADC_Channel_Position[index1]>0x05) && (ADC_SETUP[index].ADC_Channel_Position[index1]<=0x0B))
				{
					ADC_SETUP[index].ADC_Instance->SQR2|=((ADC_SETUP[index].ADC_Channels[index1])<<(5*(ADC_SETUP[index].ADC_Channel_Position[index1]-0x06)));
				}
				else
				{
					ADC_SETUP[index].ADC_Instance->SQR1|=((ADC_SETUP[index].ADC_Channels[index1])<<(5*(ADC_SETUP[index].ADC_Channel_Position[index1]-0x0C)));
				}

			#endif
		}

		/*Set the regular channel sequence length*/
		ADC_SETUP[index].ADC_Instance->SQR1|=ADC_SETUP[index].ADC_Sequence_Length ;

		/*Start the ADC*/
		ADC_Driver_On(index);

		/*Reset calibration*/
		ADC_SETUP[index].ADC_Instance->CR2|=ADC_DRIVER_RESET_CALLIBRATION;
		while(((ADC_SETUP[index].ADC_Instance->CR2) & ADC_DRIVER_RESET_CALLIBRATION )!=0x00){}

		/*Calibration*/
		ADC_SETUP[index].ADC_Instance->CR2|=ADC_DRIVER_CALLIBRATION;
		while(((ADC_SETUP[index].ADC_Instance->CR2) & ADC_DRIVER_CALLIBRATION)!=0x00){}
	}

}

uint16 ADC_Driver_GetSample(uint8 ADC_Instance_Number)
{
	uint16 data=0x00;
	data = ((uint16)(ADC_SETUP[ADC_Instance_Number].ADC_Instance->DR));
	return data;
}

uint8 ADC_Driver_GetStatus(uint8 ADC_Instance_Number,uint8 Event)
{
	if((ADC_SETUP[ADC_Instance_Number].ADC_Instance->SR & Event)!=FALSE)
	{
		return SUCCES;
	}
	else
	{
		return FAILED;
	}
}

void ADC_Driver_ClearStatus(uint8 ADC_Instance_Number)
{
	ADC_SETUP[ADC_Instance_Number].ADC_Instance->SR = 0x00;
}

void ADC_Driver_Off(uint8 ADC_Instance_Number)
{
	ADC_SETUP[ADC_Instance_Number].ADC_Instance->CR2 &= ADC_DRIVER_OFF;
}

void ADC_Driver_On(uint8 ADC_Instance_Number)
{
	ADC_SETUP[ADC_Instance_Number].ADC_Instance->CR2|=ADC_DRIVER_ON;
}

void ADC_Driver_StartSampling(uint8 ADC_Instance_Number)
{
	ADC_SETUP[ADC_Instance_Number].ADC_Instance->CR2|=ADC_DRIVER_REGULAR_START;
}

#if(ADC_DRIVER_SEQUENTIAL_READ == OK)
	void ADC_Driver_SetChannel(uint8 ADC_Instance_Number,uint8 ChannelNumber)
	{
		/*If Sequnetial Read is used this function isn't needed*/
	}

#else

	void ADC_Driver_SetChannel(uint8 ADC_Instance_Number,uint8 ChannelNumber)
	{
		/*Set the desired channel to the sequence register (only the 1st sequence is used in this case)*/
		ADC_SETUP[ADC_Instance_Number].ADC_Instance->SQR3 |= ChannelNumber;
	}

#endif
