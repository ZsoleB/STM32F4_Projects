///*
// * HWENCODER_Driver.c
// *
// *  Created on: 19 feb. 2018
// *      Author: Zsole
// */
//#include "HWENCODER_Driver.h"
//#include "HWENCODER_Driver_Cfg.h"
//
//void HWENCODER_Driver_Init(TIM_TypeDef* TIMx)
//{
//	#if (HWENCODER_DRIVER_SELECTED_TIMER_INPUT==HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_1)
//
//		TIMx->SMCR|=HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_1;
//
//	#elif(HWENCODER_DRIVER_SELECTED_TIMER_INPUT==HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_2)
//
//		TIMx->SMCR|=HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_2;
//
//	#elif(HWENCODER_DRIVER_SELECTED_TIMER_INPUT==HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_1_AND_2)
//
//		TIMx->SMCR|=HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_1_AND_2;
//
//	#endif
//
//		TIMx->CCMR1|=(0x01<<8)|(0x01);
//		TIMx->CCER|=(uint16)( 0x01|
//					(uint16)((0x01)<<4));
//		TIMx->CNT =(MAX16-1);
//
//}
//uint32 HWENCODER_Driver_Get_Count_Value(TIM_TypeDef* TIMx)
//{
//	return (uint32)(TIMx->CNT);
//}
//
//
