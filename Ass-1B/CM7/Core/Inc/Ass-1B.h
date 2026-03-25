#ifndef SRC_ASS_1B_H_
#define SRC_ASS_1B_H_

#include "main.h"
// for printf
#include <stdio.h>
#include <math.h>
// Question to be completed
#define DO_QUESTION 2

// Defining the state machines for the LEDs
enum CurrentStates {ON, OFF, PAUSE};

// Timers Defined
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

// Defining ADC
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

// Defining DAC
extern DAC_HandleTypeDef hdac1;
extern DMA_HandleTypeDef hdma_dac1_ch1;

// Defining PWM (PA11)
extern DMA_HandleTypeDef hdma_tim1_ch4;


// Assignment functions
void Ass_1B_main (void);


#endif /*SRC_ASS_1ABH_ */
