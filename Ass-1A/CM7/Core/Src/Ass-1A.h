#ifndef SRC_ASS_1A_H_
#define SRC_ASS_1A_H_

#include "main.h"
// for printf
#include <stdio.h>
#include <math.h>
// Question to be completed
#define DO_QUESTION 4
// Define a state machine for the LEDs
enum LED_States {State_LED1, State_LED2, State_LED3, State_LED4};
// To use variables declared in main.c
extern TIM_HandleTypeDef htim3;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

// Assignment functions
void Ass_1A_main (void);


#endif /*SRC_ASS_1A_H_ */
