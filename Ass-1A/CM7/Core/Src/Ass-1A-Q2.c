#include "Ass-1A.h"

#if DO_QUESTION == 2
volatile uint8_t start_loop = 0;

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3) {
		// this flag indicates that the timer is up
		// We are using tim3, since it's uses with CM7
		start_loop = 1;
	}
}

void Ass_1A_main(void)
{
	enum LED_States State = State_LED4;
	enum LED_States Next_State = State_LED4;
	uint16_t loop = 0;

	// Initialise the timer and start running
	HAL_TIM_Base_Start_IT(&htim3);

	// Ignore first interrupt
	while (start_loop == 0);
	start_loop = 0;

	// State machine
	// LEDs moving in a circle clockwise
	while (1) {
		// Make sure that the timer is not already up
		if (start_loop == 1) {
			printf("WARNING: Loop time exceeded\n");
		}
		while (start_loop == 0);
		start_loop = 0;

		// Update state
		switch (State) {
		case State_LED1:
			Next_State = State_LED2;
			break;
		case State_LED2:
			Next_State = State_LED3;
			break;
		case State_LED3:
			Next_State = State_LED4;
			break;
		case State_LED4:
			Next_State = State_LED1;
			break;
		}

		// Update state
		if (Next_State != State) {
			switch (Next_State) {
			case State_LED1:
				HAL_GPIO_TogglePin (GPIOI, LED1_Pin);
				break;
			case State_LED2:
				HAL_GPIO_TogglePin (GPIOI, LED2_Pin);
				break;
			case State_LED3:
				HAL_GPIO_TogglePin (GPIOI, LED3_Pin);
				break;
			case State_LED4:
				HAL_GPIO_TogglePin (GPIOI, LED4_Pin);
				break;
			}
			State = Next_State;
		}
		printf ("-> Q2-Loop = %d\n", ++loop);
	}
}
#endif
