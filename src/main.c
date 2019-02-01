#include "GPIO_Driver_Cfg.h"
#include "SYSTICK_Driver_Cfg.h"

int main()
{
	GPIO_Driver_Init();
	SYSTICK_Driver_Init();
	SYSTICK_Driver_Start();

	while(1)
	{
		GPIO_Driver_SetPin(GPIO_DRIVER_PORTG,GPIO_DRIVER_PORTG_PIN13);
		SYSTICK_Driver_Delay_ms(500);
		GPIO_Driver_ClearPin(GPIO_DRIVER_PORTG,GPIO_DRIVER_PORTG_PIN13);
		SYSTICK_Driver_Delay_ms(500);
	}
	return 0;
}
