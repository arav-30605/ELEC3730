#include "Ass-1A.h"
#if DO_QUESTION == 1

void Ass_1A_main (void) {
	uint16_t LED_Pins[] =
	{LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin};
	uint16_t i;
	uint16_t loop = 0;
	// LEDs moving in a circle clockwise
	while (1)
	{
		// LEDs moving in a circle clockwise (simple code)
		// By Aravind Gowrinathan
		for (i = 0; i < 4; i++)
		{
			HAL_GPIO_TogglePin (GPIOI, LED_Pins[i]);
			HAL_Delay (250);
		}
		printf ("-> Loop = %d\n", ++loop);
	}
}

#endif
