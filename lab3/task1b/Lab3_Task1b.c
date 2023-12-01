/*
* Nick Petregal-LeMay & Alan Li
* Nick: 1950981 ---- Alan: 1938332
* 2/16/2023
* This the main function file for Lab 3
* This file contains main function for task1 part b
*/

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdint.h>
#include <stdio.h> //for printf
#include "Lab3_Inits.h"
#include "task2header.h"

// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

void led_init(void);
void UART_init(void);

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  EN_0 &= ~0xFFFFFFFF;
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  led_init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  //UART_init();
  float resistance;
  float temp;
  while(1) {
    
    if ((GPIODATA_J & 0x2) == 0x0){ // Change system clock to 120mhz if switch is pressed
      freq = 120;
      PLL_Init(freq);
      printf("freq = 120");
    }
    if ((GPIODATA_J & 0x1) == 0x0){ // Change system clock to 12mhz if switch is pressed
      freq = 12;
      PLL_Init(freq);
      printf("freq = 12");
    }
    // STEP 5: Change the pattern of LEDs based on the resistance.
    // 5.1: Convert ADC_value to resistance in kilo-ohm
    resistance = ADC_value / 4095.0 * 10.0;
    //printf("resistance: %f", resistance);
    // 5.2: Change the pattern of LEDs based on the resistance
    temp = 147.5 - ((75 * (3.3) * ADC_value) / 4096); /
    printf("Temp: %f\n", temp);
  }
  return 0;
}
/* this works and is task a */
void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC |= 0x8; //clearing ADC flag
  GPTMICR_0 |= 0x1; //clearing timer flag (just in case)
  
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = (0xFFFF & ADCSSFIFO3); //becuase data fifo is only first 12 bits
}



