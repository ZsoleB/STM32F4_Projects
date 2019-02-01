/*
 * TCNT_Driver.c
 *
 *  Created on: Apr 19, 2018
 *      Author: zsolt.balo
 */

#include "TCNT_Driver_Cfg.h"

#if(TCNT_DRIVER_INTERRUPT_ENABLE != NOK)

#if(TCNT_DRIVER_TIMER_2 == OK)

void TIM2_IRQHandler() {
	TCNT_Driver_ClearStatus(TCNT_DRIVER_TIM2);
	TCNT_Driver_Interrupt_Callbacks[TCNT_DRIVER_TIM2_CALLBACK]();
}

#endif

#if(TCNT_DRIVER_TIMER_3 == OK)

void TIM3_IRQHandler()
{

}

#endif

#if(TCNT_DRIVER_TIMER_4 == OK)

void TIM4_IRQHandler()
{

}

#endif

#if(TCNT_DRIVER_TIMER_5 == OK)

void TIM5_IRQHandler()
{

}

#endif

#if(TCNT_DRIVER_TIMER_9 == OK)

void TIM1_BRK_TIM9_IRQHandler()
{

}

#endif

#if(TCNT_DRIVER_TIMER_10 == OK)

void TIM1_UP_TIM10_IRQHandler()
{

}

#endif

#if(TCNT_DRIVER_TIMER_11 == OK)

void TIM1_TRG_COM_TIM11_IRQHandler()
{

}

#endif

#if(TCNT_DRIVER_TIMER_12 == OK)

void TIM8_BRK_TIM12_IRQHandler()
{

}

#endif

#if(TCNT_DRIVER_TIMER_13 == OK)

void TIM8_UP_TIM13_IRQHandler()
{

}

#endif

#if(TCNT_DRIVER_TIMER_14 == OK)

void TIM8_TRG_COM_TIM14_IRQHandler()
{

}

#endif

#endif

void TCNT_Driver_Init() {
	uint16 index = 0x00;

#if ((TCNT_DRIVER_TIMER_4)==OK)
	RCC->APB1ENR|=RCC_APB1ENR_TIM4EN;
#endif

#if ((TCNT_DRIVER_TIMER_3)==OK)
	RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;
#endif

#if ((TCNT_DRIVER_TIMER_2)==OK)
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
#endif

#if ((TCNT_DRIVER_TIMER_5)==OK)
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
#endif

#if ((TCNT_DRIVER_TIMER_9)==OK)
	RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
#endif

#if ((TCNT_DRIVER_TIMER_10)==OK)
	RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
#endif

#if ((TCNT_DRIVER_TIMER_11)==OK)
	RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
#endif

#if ((TCNT_DRIVER_TIMER_12)==OK)
	RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;
#endif

#if ((TCNT_DRIVER_TIMER_13)==OK)
	RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;
#endif

#if ((TCNT_DRIVER_TIMER_14)==OK)
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
#endif

#if(TCNT_DRIVER_INTERRUPT_ENABLE == OK)
	TCNT_Setup_Callbacks();
	NVIC_Driver_PriorityGroupConfig(TCNT_DRIVER_SELECTED_PRIORITY_GRUP);
	NVIC_Driver_SetTimer_Update_Interrupt(TCNT_DRIVER_SELECTED_PREEMPTION_PRIORITY,
			TCNT_DRIVER_SELECTED_SUB_PRIORITY);
#endif

	for (index = 0x00; index < TCNT_DRIVER_INSTANCE_NUM; index++) {
		TCNT_SETUP[index].Timer->CR1 |= TCNT_DRIVER_DIRECTION;
		TCNT_SETUP[index].Timer->EGR |= TCNT_DRIVER_UPDATE_GENERATION;
		TCNT_Driver_SetPrescale(index, TCNT_SETUP[index].TimerPrescaler);
		TCNT_Driver_SetPeriod(index, TCNT_SETUP[index].TimerPeriod);
	}
}

void TCNT_Driver_SetPeriod(uint8 TCNT_setup_nr, uint32 PeriodValue) {
	TCNT_SETUP[TCNT_setup_nr].Timer->ARR = PeriodValue;
}

void TCNT_Driver_SetPrescale(uint8 TCNT_setup_nr, uint32 PrescaleValue) {
	TCNT_SETUP[TCNT_setup_nr].Timer->PSC = PrescaleValue;
}

void TCNT_Driver_Start(uint8 TCNT_setup_nr) {
	TCNT_SETUP[TCNT_setup_nr].Timer->CR1 |= TCNT_DRIVER_COUNTER_ENABLE;
}

void TCNT_Driver_ClearStatus(uint8 TCNT_setup_nr) {
	TCNT_SETUP[TCNT_setup_nr].Timer->SR = ((uint16) (0x00));
}

uint8 TCNT_Driver_GetStatus(uint8 TCNT_setup_nr, uint8 Event) {
	if (((TCNT_SETUP[TCNT_setup_nr].Timer->SR) & Event) == TRUE) {
		return SUCCES;
	} else {
		return FAILED;
	}
}
