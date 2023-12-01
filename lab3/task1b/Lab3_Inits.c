/**
 * EE/CSE 474: Lab3 drivers starter code
 */

#include "PLL_Header.h"
#include "Lab3_Inits.h"

#include "task1header.h"
// YOUR CUSTOM HEADER FILE HERE

int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void led_init(void) {
  // STEP 1: Initialize the 4 on board LEDs by initializing the corresponding
  // GPIO pins.
  
  // YOUR CODE HERE
 //intializes required registers so onboard LEDs and buttons can be used
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x20; // Enable PortF GPIO 0010 0000, |= is bitmask, &=! to turn off
  RCGCGPIO |= 0x1000; // Enable PortN GPIO 0001 0000 0000 0000
  RCGCGPIO |= 0x100; // Enable PortJ GPIO  0001 0000 0000

  delay++; // Delay 2 more cycles before access Timer registers
  delay++; // Refer to Page. 756 of Datasheet for info
  GPIODIR_F = 0x11; // Set PF0 to output //PF4 and PN1
  GPIODIR_N = 0x3; // Set PN0 to output
  GPIODIR_J = 0x0; // Set PJ0 to input
  
  GPIODEN_F = 0x11; // Set PF0 to digital port
  GPIODEN_N = 0x3; // Set PN0 to digital port
  GPIODEN_J = 0x3; // Set PN0 to digital port
 
  GPIOPUR_J = 0x3; // enable PJ0 pull-up resistor
  
}

void ADCReadPot_Init(void) {
  volatile unsigned short delay = 0;

  
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  //delay = 0;
  RCGCADC |= 0x1;
  // 2.2: Delay for RCGCADC (Refer to page 1073)
  delay++;
  delay++;
  delay++;
  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADCCC |= 0x1;
  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
  delay = 0;
  RCGCGPIO |= 0x10; // Enable PortE
  // 2.7: Delay for RCGCGPIO
  delay++; // Delay 2 more cycles before access Timer registers
  delay++; // Refer to Page. 756 of Datasheet for info
  
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
  GPIOAFSEL_E |= 0x8; // Select PE3 regular port function 1 0 0 0 

  // 2.9: Clear the GPIODEN bits for the ADC input pins
  GPIODEN_E &= ~0x8;

  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  GPIOAMSEL_E |= 0x8;
  // 2.11: Disable sample sequencer 3 (SS3)
  ADCACTSS &= ~0x8; 
  // 2.12: Select timer as the trigger for SS3
  ADCEMUX |= 0x5000; //<--- maybe check 
  
  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
  ADCSSMUX3 = 0x0;//(select Ain0)
  ADCSSEMUX3 = 0x0;//(select Ain0)
  // 2.14: Configure ADCSSCTL3 register
  ADDCSSCTL3 |= 0xE; // 0110 <----- trying 1110 for temperature sensor
  ADCSSTSH3 |= 0x4; //<-- for 1b temp sensor
  // 2.15: Set the SS3 interrupt mask
  ADCIM |= 0x8;
  ADCISC |= 0x8; //clearing ADC flag
  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  EN_0 |= 0x20000;//(1 << 17u); 
   

  // 2.17: Enable ADC0 SS3
  ADCACTSS |= 0x8;
  
}

void TimerADCTriger_Init(void) {
  volatile unsigned short delay = 0;
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet
  // YOUR CODE HERE
  RCGCTIMER |= 0x1; //enable timer 0 ...was 7 but from lab 3 i think
  delay++;
  delay++;
  GPTMICR_0 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!
  GPTMCTL_0 &= ~0x1; //disable timer 0                   
  GPTMCFG_0 = 0x0; //enables 32 bit timer configuration
  GPTMTAMR_0 |= 0x2; //configuring TAMR bitand TACDIR bit (periodic mode and counting down)
  GPTMTAILR_0 = 0x3938700; //60,000,000 in HEX to achieve a 1 Hz blink rate with the 60 MHz clock
  
  GPTMCTL_0 |= 0x20; //output timer a ADC trigger is enabled
  
  GPTMADCEV |= 0x1;                                                      //**new**
  GPTMCTL_0 |= 0x1; //enabling timer 0
  
  //below this is for temperature sensor

}

// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler

void UART_init(void) {
  // STEP 1: Initialize the 4 on board LEDs by initializing the corresponding
  // GPIO pins.
  RCGCUART |= 0x1; //enable clock to UART0  **** following steps on datasheet page 1172
  GPIOAFSEL_A |= 0x2;//do I want one pin is transmit one is recieve??? ***** I think pin 0 is recieve, and pin 1 is transmit
  GPIOSLR |= 0x3; //slew rate control is enabled on pins 0 and 1
  GPIOPCTL |= 0x11;//0001 0001 
  
  // YOUR CODE HERE
 //intializes required registers so onboard LEDs and buttons can be used
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x1; // Enable PortJ GPIO  0001 0000 0000

  delay++; // Delay 2 more cycles before access Timer registers
  delay++; // Refer to Page. 756 of Datasheet for info
  
//GPIODIR_A = 0x11; // Set PF0 to output
  
  GPIODEN_A = 0x3; // Set PF0 to digital port
  
  UARTIBRD |= 0xCC;
  UARTFBRD |= 0xB;

  
}




