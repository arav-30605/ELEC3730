// Question 4 code by Aravind Gowrinathan
#include "Ass-1A.h"

#if DO_QUESTION == 4

// ADC output register variables
// Output is stored as unsigned integer variable with 32 bit storage
uint32_t ADCValue;
float ADCValue_Float;

// Tracking the timer overflow count
volatile uint8_t TimerOverflowCounter = 0;

// Time range for mapping sensor data to seconds [0.0, 1.0]
// Time being in seconds with decimals, it's best to store it as a float data type
float LOW_BOUND_OUTPUT = 0;
float HIGH_BOUND_OUTPUT = 0;

// Change is permitted, so it gets flagged when changed
int changeFlag = 0;

// Setting up the states
enum LED_States State = State_LED1;

// counter to control how often we change state at 10 Hz
int tick_counter = 0;      // number of 0.1 s ticks elapsed
int ticks_needed = 10;     // how many 0.1 s ticks before changing LED (1..10)

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

}

// Callback triggered when ADC conversion or DMA transfer is complete
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim3 ){
        // To increment the timer overflow counter for timer to overflow every 0.1s
        TimerOverflowCounter = 1;
    }
}

// Summoning to access the main file
void Ass_1A_main ()
{
    // Initialize the timer and updating the pre-scaler so that the timer overflows every 0.1 seconds.
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_ADC_Start_DMA(&hadc1, &ADCValue, 1);

    TIM3->ARR = 1999;
    TIM3->PSC = 9999;

    // Ignore first interrupt
    while (TimerOverflowCounter == 0);
    TimerOverflowCounter = 0;

    while (1) {
        // Make the while(1) loop iterate at 10 Hz
        // Wait for the 0.1 s timer tick
        while (TimerOverflowCounter == 0);
        // Clear the flag so we wait for the next tick next time
        TimerOverflowCounter = 0;
        // Now everything below runs exactly once every 0.1 s

        // Start the ADC
        // Get the float ADC Value and store in ADCValue
        ADCValue_Float = (float)ADCValue;

        // Trial method 1:
        // Performing calculations to scale the 1Hz to 10 Hz values
        // LOW_BOUND_OUTPUT = ((ADCValue_Float*3/5600)+0.0625)*10;
        // HIGH_BOUND_OUTPUT = (-(ADCValue_Float/2050)+2.0975)*10;

        // We map ADCValue to ticks_needed: number of 0.1 s ticks before changing LED.
        // Closer to center -> larger ticks_needed so slower.
        // Further from center -> smaller ticks_needed faster.

        // Defining a center region
        float centre_low  = 2000.0f;
        float centre_high = 2200.0f;

        if (ADCValue_Float >= centre_low && ADCValue_Float <= centre_high) {
            // Potentiometer roughly at center:
            // The lit LED will not change position.
            ticks_needed = 1000;   // large value so it never hits technically
        }
         else {
            float dist;

            if (ADCValue_Float < centre_low) {
                // Right of center (ADC small): downward sequence
                // Distance from center
                dist = centre_low - ADCValue_Float;
                // Normalize 63 to 69, varying values of the ADC (Pot)
                float norm = dist / (centre_low - 67.0f);   // 0 to 1
                // Map 0 to 1 to ticks 10 to 1
                ticks_needed = 10 - (int)(norm * 9.0f);     // 10 to 1
            } else {
                // Left of center (ADC large): upward sequence
                dist = ADCValue_Float - centre_high;
                // Normalize max ADC float value of 4095 (Pot)
                float norm = dist / (4095.0f - centre_high); // 0 to 1
                ticks_needed = 10 - (int)(norm * 9.0f);      // 10 to 1
            }

            if (ticks_needed < 1)  ticks_needed = 1;
            if (ticks_needed > 10) ticks_needed = 10;
        }

        // Count how many 0.1 s ticks have passed
        tick_counter++;

        // Check if enough time has elapsed to change LED
        if (tick_counter >= ticks_needed) {
            // Resetting the timer overflow counter flag here (logical timing counter)
            tick_counter = 0;

            // LED must change when the ADC value goes from + to - or vice versa.
            // Change state based on integer value of ADC
            if (ADCValue < 2000) {
                // Right of center: LEDs illuminate in a downward sequence
                State = State + 1;
            }
            else if (ADCValue > 2200) {
                // Left of center : LEDs illuminate in an upward sequence
                State = State - 1;
            }

            // To make sure State is within it's bounds and gets reseted if it is out of bounds
            if (State == 4) {
                State = 0;
            }
            if (State == 255) {
                State = 3;
            }

            // States using case functions to define which LEDs to turn on/off.
            // Only one LED ON at any time.
            switch (State) {
            case State_LED1:
                HAL_GPIO_WritePin (GPIOI, LED1_Pin,0);
                HAL_GPIO_WritePin (GPIOI, LED2_Pin,1);
                HAL_GPIO_WritePin (GPIOI, LED3_Pin,1);
                HAL_GPIO_WritePin (GPIOI, LED4_Pin,1);
                break;
            case State_LED2:
                HAL_GPIO_WritePin (GPIOI, LED1_Pin,1);
                HAL_GPIO_WritePin (GPIOI, LED2_Pin,0);
                HAL_GPIO_WritePin (GPIOI, LED3_Pin,1);
                HAL_GPIO_WritePin (GPIOI, LED4_Pin,1);
                break;
            case State_LED3:
                HAL_GPIO_WritePin (GPIOI, LED1_Pin,1);
                HAL_GPIO_WritePin (GPIOI, LED2_Pin,1);
                HAL_GPIO_WritePin (GPIOI, LED3_Pin,0);
                HAL_GPIO_WritePin (GPIOI, LED4_Pin,1);
                break;
            case State_LED4:
                HAL_GPIO_WritePin (GPIOI, LED1_Pin,1);
                HAL_GPIO_WritePin (GPIOI, LED2_Pin,1);
                HAL_GPIO_WritePin (GPIOI, LED3_Pin,1);
                HAL_GPIO_WritePin (GPIOI, LED4_Pin,0);
                break;
            }
        }
    }
}
#endif
