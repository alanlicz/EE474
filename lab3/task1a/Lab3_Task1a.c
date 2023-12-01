/**
 * EE/CSE 474: Lab3 Task1a main function
 */

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdint.h>
#include <stdio.h> //for printf
#include "Lab3_Inits.h"
#include "task1header.h"

// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

void led_init(void);

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  EN_0 &= ~0xFFFFFFFF;
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  led_init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  float resistance;
  while(1) {
    // STEP 5: Change the pattern of LEDs based on the resistance.
    // 5.1: Convert ADC_value to resistance in kilo-ohm
    resistance = ADC_value / 4095.0 * 10.0;
    printf("resistance: %f\n", resistance);
    // 5.2: Change the pattern of LEDs based on the resistance
    if (resistance < 2.5) {
      GPIODATA_F = 0x0; 
      GPIODATA_N = 0x2; // Set PN0 and PN1 to 1
    } else if (resistance < 5.0) {
      GPIODATA_F = 0x0; 
      GPIODATA_N = 0x3; // Set PN0 to 1
    } else if (resistance < 7.5) {
      GPIODATA_N = 0x3; // Set PN0 to 1
      GPIODATA_F = 0x10; // Set PF0 and PF4 to 1
    } else {
      GPIODATA_N = 0x3; // Set PN0 to 1
      GPIODATA_F = 0x11; // Set PF0 to 1 //just test values to see LEDs turn on
    }
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC |= 0x8; //clearing ADC flag
  GPTMICR_0 |= 0x1; //clearing timer flag (just in case)
  
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = (0xFFFF & ADCSSFIFO3); //becuase data fifo is only first 12 bits
}



