#include "GPIO_Driver_Cfg.h"
#include "SYSTICK_Driver_Cfg.h"
#include "EXTI_Driver_Cfg.h"

int main()
{
	GPIO_Driver_Init();
	SYSTICK_Driver_Init();
	SYSTICK_Driver_Start();

	EXTI_Driver_Init(EXTI_DRIVER_INTERRUPT_PIN_0, EXTI_DRIVER_INTERRUPT_PORT_A);
	EXTI_Driver_Falling_Trigger_Select(EXTI_DRIVER_INTERRUPT_PIN_0);


	while(1)
	{
		GPIO_Driver_SetPin(GPIO_DRIVER_PORTG,GPIO_DRIVER_PORTG_PIN13);
		SYSTICK_Driver_Delay_ms(500);
		GPIO_Driver_ClearPin(GPIO_DRIVER_PORTG,GPIO_DRIVER_PORTG_PIN13);
		SYSTICK_Driver_Delay_ms(500);
	}
	return 0;
}
