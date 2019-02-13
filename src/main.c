#include "GPIO_Driver_Cfg.h"
#include "EXTI_Driver_Cfg.h"

uint8 dummy_counter = 0x00;

void EXTI0_IRQHandler()
{
	static uint8 state = 0x00;
	if (state == 0x00)
	{
		GPIO_Driver_SetPin(GPIO_DRIVER_PORTG,GPIO_DRIVER_PORTG_PIN14);
		state = !state;
	}
	else
	{
		GPIO_Driver_ClearPin(GPIO_DRIVER_PORTG,GPIO_DRIVER_PORTG_PIN14);
		state = !state;
	}
	EXTI_Driver_Clear_PendingInterrupt(EXTI_DRIVER_INTERRUPT_PIN_0);
}

int main()
{
	GPIO_Driver_Init();

	EXTI_Driver_Init(EXTI_DRIVER_INTERRUPT_PIN_0,EXTI_DRIVER_INTERRUPT_PORT_A);
	EXTI_Driver_Rising_Trigger_Select(EXTI_DRIVER_INTERRUPT_PIN_0);

	while (1)
	{
		dummy_counter++;
	}
}
