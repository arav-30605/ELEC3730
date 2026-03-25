// Code written by: Aravind Gowrinathan
#include "Ass-1B.h"
// Replace X with a question number
#if DO_QUESTION == 2

// Start in OFF state (refer to the flowchart)
enum CurrentStates CurrentState = OFF;

// Declaring ADC and storing the float value in ADCValue_Float
uint32_t ADCValue;
float ADCValue_Float;

// To measure the time
// To measure the remaining grinding time in seconds
float On_duration_left;
float PauseTimeCount;

// For the PWM (PA11)
uint32_t LEDdataON[200] = {0};
uint32_t LEDdata[800] = {0};

// Blue Button Flag (PC13)
uint16_t BlueButton = 0;

// Defining DAC
// Aim for around 100 samples per period, meaning that my array should have around 100 elements
// The period of the timer should be 1 second for DAC+DMA
int data[100];
#define SAMPLES 100

// Debouncing (just for safety)
// Doc refers to you may or may not need to add software debouncing in my code
#define DEBOUNCE_INTERVAL 100

// Flag to indicate start of loop
volatile uint8_t start_loop = 0;

// Performance information
uint32_t loop_count = 0;
uint32_t wait_count;
uint32_t wait_count_min = 1 << 31;
uint32_t wait_count_max = 0;
uint32_t wait_count_avg = 0;

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim) // Timer overflow callback function
{
	if (htim->Instance == htim3.Instance)
	{
		start_loop = 1;
	}
}

// Using interrupts to make the code efficient and to print the stats after 1 minute of running
// Interrupt callback function (from ELEC2720)
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	static uint32_t lastpresstime = 0;

	if ((GPIO_Pin == BlueButton_Pin) && (uwTick - lastpresstime > DEBOUNCE_INTERVAL)) {
		BlueButton = 1;
		lastpresstime = uwTick;
	}
}

// ADC callback function
// To read and map the POT values to 5s and 15s.
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
}

// Summoning the main file
void Ass_1B_main()
{
	// Creating the DAC array to store the sound info
	// One cycle of sine wave, times by 50 to create peaks at 80 DAC units
	// To create the grinding sound, the DMA loops it continuously
	for (uint16_t i=0; i< SAMPLES; i++){
		data[i] = (uint32_t) 50.0 * (sin(2*3.14159*i/SAMPLES)+1);
	}

	// Creating the PWM array, need to configure it to be less than 0.01s
	for (uint16_t i=0; i < 400; i++){
		LEDdataON[i] = (10000);
	}

	// Starts at 4% duty cycle (dim) then it ramps up to 100% over 400 steps
	for (uint16_t i=0; i < 400; i++){
		LEDdata[i] = (24.5*(i+400)-9600);
	}
	// Same as above, but from 100% (full brightness) duty cycle to 4% duty cycle over 400 steps
	for (uint16_t i=400; i < 800; i++){
		LEDdata[i] = -24.5*(i-400)+10000;
	}

	// Initialise the timer and start running
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);

	// Starting the ADC+DMA
	HAL_ADC_Start_DMA(&hadc1, &ADCValue, 1);

	// Ignore first interrupt
	while (start_loop == 0);
	start_loop = 0;

	// Grinder application
	while (loop_count < 6000) // Run for 1min assuming 10ms loop duration
	{
		// Wait for next loop
		if (start_loop == 1)
		{
			printf ("WARNING: Loop time exceeded\n");
		}
		wait_count = 0;
		while (start_loop == 0)
		{
			wait_count++;
		}
		start_loop = 0;

		// Performance monitoring
		loop_count++;
		wait_count_avg = (wait_count_avg+wait_count*(loop_count-1))/loop_count;
		if (wait_count > wait_count_max)
			wait_count_max = wait_count;
		if (wait_count < wait_count_min)
			wait_count_min = wait_count;

		// **** START COFFEE GRINDER MAIN LOOP CODE ****
		// Remember Aravind that PA11 is the TIMER 1 CHANNEL 4.
		switch(CurrentState){
		case OFF:
			if (BlueButton == 1){
				CurrentState = ON;
				BlueButton = 0;   // Resetting the Blue button flag
				// Calculate How long Needs to be ON for. Use Assignment 1A - Q4.
				// Refer to my PDF doc for how this formula was achieved.
				ADCValue_Float = (float)ADCValue;
				On_duration_left = (-0.002478)*(ADCValue_Float)+15.1487;
				// Start the DAC Speaker Sound and turn the LED on
				HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, data, SAMPLES, DAC_ALIGN_12B_R);
				HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t *) LEDdataON, 200);
			}
			break;
		case ON:
			On_duration_left=On_duration_left-0.01;   // To avoid the LED flicker
			if (On_duration_left<=0){
				CurrentState = OFF;
				HAL_TIM_PWM_Stop_DMA(&htim1,TIM_CHANNEL_4);   // Stop the PWM and DAC DMA to go OFF state
				HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1);
			}
			if (BlueButton == 1){
				BlueButton = 0;   // Resetting the Blue button flag
				CurrentState = PAUSE;
				PauseTimeCount=0;   // Resetting the Pause time flag
				// Stop the DAC Speaker sound and make the LED pulse (like a heart beat)
				HAL_TIM_PWM_Stop_DMA(&htim1,TIM_CHANNEL_4);
				HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1);
				HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t *) LEDdata, 800);
			}
			break;
		case PAUSE:
			PauseTimeCount=PauseTimeCount+0.01;
			// If in the system is in PAUSE state for more than 20 sec, then go OFF state
			if (PauseTimeCount>=20){
				CurrentState = OFF;
				HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_4);
			}
			if (BlueButton==1){
				BlueButton = 0;   // Resetting the Blue button flag
				CurrentState = ON;
				// Stop pulsing the LED and start the DAC Speaker sound (back to ON state)
				HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_4);
				HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t *) LEDdataON, 200);
				HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, data, SAMPLES, DAC_ALIGN_12B_R);
			}
			break;
		}
		// ****  END COFFEE GRINDER MAIN LOOP CODE ****

	} // end of while

	// Print performance information
	printf("INFO: loop_count     = %ld (%fs)\n", loop_count, (float)loop_count*(float)0.01);
	printf("INFO: wait_count_max = %ld\n", wait_count_max);
	printf("INFO: wait_count_avg = %ld\n", wait_count_avg);
	printf("INFO: wait_count_min = %ld\n", wait_count_min);

} // end of Ass_1B_main ()

#endif



