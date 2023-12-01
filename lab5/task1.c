/*
* Nick Petregal-LeMay & Alan Li
* Nick: 1950981 ---- Alan: 1938332
* 1/19/2023
* This the main.c file for Lab 1 Task 1
* This file includes the main method for Task 1
* This file also includes deifinitions for all other functions used for Task 1
* Task 1 contains two parts
*       1a) creating a sequential blinking LED pattern (controlled by function task1a())
*       1b) controlling two LEDs via on board switches (controlled by function task1b())
*/
#include <stdint.h>
#include "task1.h"

void wait();
void task1a();
void task1b();
void led_and_switch_init(void);
void pwm_init(void);

//main method for task 1
int main(void)
{
  led_and_switch_init();
  pwm_init();
  while (1) {
    task1a();
  }
  return 0;
}

//Acts as a delay in the program by implementing a long loop
void wait() {
  for (int i = 0; i < 1000000; i++){} //delay
}
//completes task 1a functionality as described in lab spec
//turns on the onboard LEDs in a sequential pattern on then off
void task1a() {
  //sequential pattern
    GPIODATA_F = 0x1; // Set PF0 to 1
    wait(); //delay
    GPIODATA_F = 0x11; // Set PF0 and PF4 to 1
    wait(); //delay
    GPIODATA_N = 0x1; // Set PN0 to 1
    wait(); //delay
    GPIODATA_N = 0x3; // Set PN0 and PN1 to 1
    wait(); //delay
    GPIODATA_N = 0x1; // Set PN1 to 0
    wait(); //delay
    GPIODATA_N = 0x0; // Set PN0 to 0
    wait(); //delay
    GPIODATA_F = 0x1; // Set PF4 to 0
    wait(); //delay
    GPIODATA_F = 0x0; // Set PF0 to 0
    wait(); //delay
}
//completes task 1b functionality as described in lab spec
//controls PN0 and PN1 LEDs through the onboard buttons
void task1b(){
  if ((GPIODATA_J & 0x2) == 0x0) { //Switches are active low, thats why checking == 0x0
      GPIODATA_N |= 0x1; // Set PN0 to 1 leaving other pins untouched
    } else {
      GPIODATA_N &= ~0x1; // Set PN0 to 0 leaving other pins untouched
    }
    
    if ((GPIODATA_J & 0x1) == 0x0) { 
      GPIODATA_N |= 0x2; // Set PN1 to 1 leaving other pins untouched
    } else {
      GPIODATA_N &= ~0x2; // Set PN1 to 0 leaving other pins untouched
    }
}

//intializes required registers so onboard LEDs and buttons can be used
void led_and_switch_init(void){
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

//follows pwm initiliazition on datasheet page 1678
void pwm_init(void) {
  volatile unsigned short delay = 0;  
  RCGCPWM |= 0x1; //enable clock to PWM module 0 

  RCGCGPIO |= 0x1; // Enable Port F
  delay++; 
  delay++;// Refer to Page. 756 of Datasheet for info
  GPIOAFSEL_A |= 0x3; //0011 for pin 0 and 1
  GPIOPCTL_A |= 0x3;//not so sure what to do here... also do I need other GPIO registers? //look page 1808
  PWMCC = 0x0; //PWM clock frequency is system clock /2
  PWM0CTL = 0x0;   //countdown mode
  PWM0GENA = 0x8C; //these are count down values
  PWM0GENB = 0x80C;//these are count down values
  
  PWM0LOAD = 0x18F;
  PWM0CMPA = 0x12B; //pin F0 = 25% duty cycle
  PWM0CMPB = 0x63;  //pin F1 = 75% duty cycle
  
  PWM0CTL = 0x1;   //start timers
  PWMENABLE = 0x3; //enable PWM outputs
  
}