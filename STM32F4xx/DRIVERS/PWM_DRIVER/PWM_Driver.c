/*
 * PWM_Driver.c
 *
 *  Created on: 29 ian. 2018
 *      Author: Zsole
 */
#include "PWM_Driver_Cfg.h"

void PWM_Driver_Init(TIM_TypeDef *TIMx)
{
	#if (PWM_DRIVER_CAPTURE_COMPARE_REGISTER_1==OK)
		TIMx->CCMR1|=((PWM_DRIVER_OUTPUT_COMPARE_1_PRELOAD_ENABLE<<0x03)
				   |  (PWM_DRIVER_OUTPUT_COMPARE_1_MODE<<0x04));
		TIMx->CCER |=((PWM_DRIVER_CAPTURE_COMPARE_1_POLARITY<<0x01)
				   |  (PWM_DRIVER_CAPTURE_COMPARE_1_ENABLE));
	#endif

	#if (PWM_DRIVER_CAPTURE_COMPARE_REGISTER_2==OK)
		TIMx->CCMR1|=((PWM_DRIVER_OUTPUT_COMPARE_2_PRELOAD_ENABLE<<0x0B)
				   |  (PWM_DRIVER_OUTPUT_COMPARE_2_MODE<<0x0C));
		TIMx->CCER |=((PWM_DRIVER_CAPTURE_COMPARE_2_POLARITY<<0x05)
				   |  (PWM_DRIVER_CAPTURE_COMPARE_2_ENABLE<<0x04));
	#endif

	#if (PWM_DRIVER_CAPTURE_COMPARE_REGISTER_3==OK)
		TIMx->CCMR2|=((PWM_DRIVER_OUTPUT_COMPARE_3_PRELOAD_ENABLE<<0x03)
				   |  (PWM_DRIVER_OUTPUT_COMPARE_3_MODE<<0x04));
		TIMx->CCER |=((PWM_DRIVER_CAPTURE_COMPARE_3_POLARITY<<0x09)
				   |  (PWM_DRIVER_CAPTURE_COMPARE_3_ENABLE<<0x08));
	#endif

	#if (PWM_DRIVER_CAPTURE_COMPARE_REGISTER_4==OK)
		TIMx->CCMR2|=((PWM_DRIVER_OUTPUT_COMPARE_4_PRELOAD_ENABLE<<0x0B)
				   |  (PWM_DRIVER_OUTPUT_COMPARE_4_MODE<<0x0C));
		TIMx->CCER |=((PWM_DRIVER_CAPTURE_COMPARE_4_POLARITY<<0x0D)
				   |  (PWM_DRIVER_CAPTURE_COMPARE_4_ENABLE<<0x0C));
	#endif
}

void PWM_Driver_SetDutyCylce(TIM_TypeDef *TIMx, uint32 DutyCycle)
{
	DutyCycle = (uint16)DutyCycle;
	if(DutyCycle<0)
	{
		DutyCycle = 0;
	}
	else if(DutyCycle>100)
	{
		DutyCycle = 100;
	}

	#if PWM_DRIVER_CAPTURE_COMPARE_REGISTER_1 == OK
		TIMx->CCR1 = ((uint16)(((TIMx->ARR)*DutyCycle)/100));
	#endif

	#if PWM_DRIVER_CAPTURE_COMPARE_REGISTER_2 == OK
		TIMx->CCR2 = ((uint16)(((TIMx->ARR)*DutyCycle)/100));
	#endif

	#if PWM_DRIVER_CAPTURE_COMPARE_REGISTER_3 == OK
		TIMx->CCR3 = ((uint16)(((TIMx->ARR)*DutyCycle)/100));
	#endif

	#if PWM_DRIVER_CAPTURE_COMPARE_REGISTER_4 == OK
		TIMx->CCR4 = ((uint16)(((TIMx->ARR)*DutyCycle)/100));
	#endif
}

void PWM_Driver_SetPeriod(TIM_TypeDef *TIMx,uint32 Period)
{
	/*TCNT_Driver_SetPeriod(TIMx,((uint16)Period));*/
}
