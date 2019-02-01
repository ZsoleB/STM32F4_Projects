/*
 * TWI_Driver.c
 *
 *  Created on: Jul 17, 2018
 *      Author: zsolt.balo
 */

#include "TWI_Driver_Cfg.h"

/*
 By default, I2c operates in slave mode. The interface automatically switches from slave to
master, after it generates a START condition and from master to slave, if an arbitration
loss or a Stop generation occurs, allowing multimaster capability.
 */

uint32 TWI_Driver_Get_Status(I2C_TypeDef* TWIx,uint32 StatusCode)
{
	uint32 CompleteStatus = 0x00, flag1 = 0x00, flag2 = 0x00;

	flag1 = TWIx->SR1;
	flag2 = TWIx->SR2;
	CompleteStatus = ((flag2<<16)|flag1);

	if(CompleteStatus == StatusCode)
	{
		return SUCCES;
	}else
	{

	}	return FAILED;
}

void TWI_Driver_Init(I2C_TypeDef* TWIx)
{
	/*Enable the clock in the peripheral bus*/
	#if (TWI_DRIVER_TWI1 == OK)
		RCC->APB1ENR|=RCC_APB1ENR_I2C1EN;
	#endif

	#if (TWI_DRIVER_TWI2 == OK)
		RCC->APB1ENR|=RCC_APB1ENR_I2C2EN;
	#endif

	TWI_Driver_Reset(TWIx);

	#if (TWI_DRIVER_FUNCTIONALITY == TWI_DRIVER_INTERRUPT_FUNCTIONALITY)
		I2C1->CR2|= I2C_CR2_ITEVTEN;
	#endif

	/*Peripheral clock frequency*/
	TWI_Driver_SetClock(TWIx);

	/*Enable peripheral*/
	TWI_Driver_Start(TWIx);

	/* Acknowledge enable*/
	#if (TWI_DRIVER_ACKNOWLEDGE_ENABLE == OK)
		TWIx->CR1 |=(1<<0x0A);
	#endif

	/*Clock stretching disable*/
	#if (TWI_DRIVER_CLOCK_STRETCHING_DISABLE == OK)
		TWIx->CR1 |=(1<<0x07);
	#elif (TWI_DRIVER_CLOCK_STRETCHING_DISABLE  == NOK)
		TWIx->CR1 &=(~(1<<0x07));
	#endif

	/*General call enable*/
	#if (TWI_DRIVER_GENERAL_CALL_ENABLE)
		TWIx->CR1 |=(1<<0x06);
	#endif

	/*SMB Bus mode*/
	#if (TWI_DRIVER_SMB_BUS_MODE)
		TWIx->CR1 |=(1<<0x01);
	#endif

	#if (TWI_DRIVER_DUALADDRESSING == NOK)
	/*Own address register 1*/
		TWIx->OAR1 = TWI_DRIVER_OWNADDRESS2;
	#elif(TWI_DRIVER_DUALADDRESSING == OK)
	/*Own address register 2*/
		TWIx->OAR2 = TWI_DRIVER_OWNADDRESS2;
	#endif
}

uint8 TWI_Driver_ReceiveData(I2C_TypeDef* TWIx)
{
	return (uint8)TWIx->DR;
}

void TWI_Driver_Reset(I2C_TypeDef* TWIx)
{
	/*This can be used to reinitialize the peripheral after an error or
	  a locked state. As an example, if the BUSY bit is set and remains locked
	  due to a glitch on the bus, the SWRST bit can be used to exit from this state.*/

	/*Software reset*/
	TWIx->CR1 |= (1<<0x0F);
	TWIx->CR1 &= (~(1<<0x0F));
}

void TWI_Driver_SetClock(I2C_TypeDef* TWIx)
{
	uint16 result  = 0x04;

	/*Stop the peripheral before setting the clock*/
	TWI_Driver_Stop(TWIx);

	/*Set peripheral clock frequency in CR2*/
	TWIx->CR2 |= TWI_DRIVER_PCLOCK_MHZ;

	/*Speed mode selection*/
	#if(TWI_DRIVER_CLOCK_MODE == TWI_DRIVER_STANDARD_SPEED_100KHz)
		/*Standard mode selected*/
		TWIx->CCR &= (~(1<<0x0F));

		/*Clock control*/
		result = (uint16)((TWI_DRIVER_PCLK_VALUE)/(TWI_DRIVER_CLOCK_FREQUENCY<<1));

		if (result<0x04)
		{
			result = 0x04;
		}

		TWIx->CCR |= result;

		/* Maximum rise time in Fm/Sm mode (values can be looked up in the datasheet)*/
		TWIx->TRISE = (uint16)(TWI_DRIVER_PCLOCK_MHZ+1);

	#elif(TWI_DRIVER_CLOCK_MODE == TWI_DRIVER_FAST_SPEED_400KHZ)
		/*Fast mode selected*/
		TWIx->CCR |= (1<<0x0F);

		/*Duty cycle*/
		#if(TWI_DRIVER_FAST_MODE_DUTY_CYCLE == TWI_DRIVER_FAST_SPEED_DUTY_CYCLE_2)

			TWIx->CCR &= (~(0x01<<0x0E));

			/*Clock control*/
			result = (uint16)((TWI_DRIVER_PCLK_VALUE)/(TWI_DRIVER_CLOCK_FREQUENCY*3));

		#elif(TWI_DRIVER_FAST_MODE_DUTY_CYCLE == TWI_DRIVER_FAST_SPEED_DUTY_CYCLE_16_9)

			TWIx->CCR |= (0x01<<0x0E);

			/*Clock control*/
			result = (uint16)((TWI_DRIVER_PCLK_VALUE)/(TWI_DRIVER_CLOCK_FREQUENCY*25));

		#endif

		if (result<0x01)
		{
			result = 0x01;
		}

		TWIx->CCR |= result;

		/* Maximum rise time in Fm/Sm mode (values can be looked up in the datasheet)*/
		TWIx->TRISE = (uint16)((TWI_DRIVER_PCLOCK_MHZ*((uint16_t)300/(uint16_t)1000))+1);
	#endif


}

void TWI_Driver_SendData(I2C_TypeDef* TWIx,uint8 Payload)
{
	TWIx->DR = Payload;
}

void TWI_Driver_SendAddress(I2C_TypeDef* TWIx,uint8 Address)
{
	TWIx->DR = Address;
}

void TWI_Driver_SendStart(I2C_TypeDef* TWIx)
{
	TWIx->CR1 |= (1<<0x08);
}

void TWI_Driver_SendStop(I2C_TypeDef* TWIx)
{
	TWIx->CR1 |= (1<<0x09);
}

void TWI_Driver_Start(I2C_TypeDef* TWIx)
{
	/*Start I2C peripheral*/
	TWIx->CR1 |= 0x01;
}

void TWI_Driver_Stop(I2C_TypeDef* TWIx)
{
	/*Start I2C peripheral*/
	TWIx->CR1 &= (~(0x01));
}

#if(TWI_DRIVER_FUNCTIONALITY == TWI_DRIVER_POLLING_FUNCTIONALITY)

	void TWI_Driver_PollingOneByteTx(I2C_TypeDef* TWIx,uint8 message, uint8 Address)
	{
		TWI_Driver_SendStart(I2C1);

		while(TWI_Driver_Get_Status(I2C1,TWI_DRIVER_EV5)!=SUCCES){/*Wait until the flags are set*/}
		TWI_Driver_SendAddress(I2C1,Address);

		while(TWI_Driver_Get_Status(I2C1,TWI_DRIVER_EV6)!=SUCCES){/*Wait until the flags are set*/}
		TWI_Driver_SendData(I2C1,message);

		while(TWI_Driver_Get_Status(I2C1,TWI_DRIVER_EV8_2)!=SUCCES){/*Wait until the flags are set*/}
		TWI_Driver_SendStop(I2C1);
	}
	void TWI_Driver_PollingTx(I2C_TypeDef* TWIx,TWI_DRIVER_Messagebuffer_Type* payload){}
	void TWI_Driver_PollingOneByteRx(I2C_TypeDef* TWIx,uint8 message, uint8 Address){}
	void TWI_Driver_PollingRx(I2C_TypeDef* TWIx,TWI_DRIVER_Messagebuffer_Type* payload){}

#elif(TWI_DRIVER_FUNCTIONALITY == TWI_DRIVER_INTERRUPT_FUNCTIONALITY)

	void TWI_Driver_InterruptOneByteTx(I2C_TypeDef* TWIx,uint8 message, uint8 Address){}
	void TWI_Driver_InterruptTx(I2C_TypeDef* TWIx,TWI_DRIVER_Messagebuffer_Type* payload){}
	void TWI_Driver_InterruptOneByteRx(I2C_TypeDef* TWIx,uint8 message, uint8 Address){}
	void TWI_Driver_InterruptRx(I2C_TypeDef* TWIx,TWI_DRIVER_Messagebuffer_Type* payload){}

#endif
