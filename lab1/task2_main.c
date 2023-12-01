/*
* Nick Petregal-LeMay & Alan Li
* Nick: 1950981 ---- Alan: 1938332
* 1/19/2023
* This the main.c file for Lab 2 
* This file includes the main method for Task 1
* This file also includes deifinitions for all other functions used for Task 1
* Task 1 contains two parts
*       1a) creating a sequential blinking LED pattern (controlled by function task1a())
*       1b) controlling two LEDs via on board switches (controlled by function task1b())
*/
#include <stdint.h>
#include <stdio.h> //for printf for test
#include "lab1.h"

void wait();
void task1a();
void led_and_switch_init(void);
void timer_init(void);
void extern_switch_init(void);
void LED_init(void);
unsigned long switch_input(char button);
void LED_on(char color);
void LED_off(char LED);
void trafficLight_SM();

volatile unsigned short ButtonReleased = 1; //makes sure the system requires separate pushes to turn the system on and off
enum states { off, stop, go, warn } state; //define states for state machine use later on

//main method for task 1
int main(void)
{
  led_and_switch_init();
  LED_init();
  extern_switch_init();
  
  state = off; // Indicates initial call
  
  while (1) {
    //task1a();
    trafficLight_SM();
  }
  return 0;
}

//Acts as a delay in the program by implementing timer 0 in periodic operation mode

//completes task 1a functionality as described in lab spec
//turns on the onboard LEDs in a sequential pattern on then off
void task1a() {
  //sequential pattern
  GPIODATA_F = 0x1; // Set PF0 to 1
  wait(1); //delay
  GPIODATA_F = 0x11; // Set PF0 and PF4 to 1
  wait(1); //delay 
  GPIODATA_N = 0x1; // Set PN0 to 1
  wait(1); //delay
  GPIODATA_N = 0x3; // Set PN0 and PN1 to 1
  wait(1); //delay
  GPIODATA_N = 0x1; // Set PN1 to 0
  wait(1); //delay
  GPIODATA_N = 0x0; // Set PN0 to 0
  wait(1); //delay
  GPIODATA_F = 0x1; // Set PF4 to 0
  wait(1); //delay
  GPIODATA_F = 0x0; // Set PF0 to 0
  wait(1); //delay
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

//sets up exteral switches for use through PN2 and PN3
void extern_switch_init(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x1000; // Enable Port N Gating Clock
  delay++;
  delay++;
  GPIOAMSEL_N &= ~0x4; // Disable PN2 analog function
  GPIOAMSEL_N &= ~0x8; // Disable PN3 analog function
  GPIOAFSEL_N &= ~0x4; // Select PN2 regular port function
  GPIOAFSEL_N &= ~0x8; // Select PN3 regular port function
  GPIODIR_N &= ~0x4; // Set PN2 to input direction
  GPIODIR_N &= ~0x8; // Set PN3 to input direction
  GPIODEN_N |= 0x4; // Enable PN2 digital function
  GPIODEN_N |= 0x8; // Enable PN3 digital function
}

//P = pedestrian button (button furthest from LEDs on board)
//O = On/Off button
unsigned long switch_input(char button)
{
  if (button == 'P'){
    return (GPIODATA_N & 0x4); // 0x4 (pressed) or 0 (not pressed)
  } else if (button == 'O'){
    return (GPIODATA_N & 0x8); // 0x8 (pressed) or 0 (not pressed)
  }
  return -1; //this should never happen
 
}

//sets up exteral LEDs for use through PC4, PC5, and PC6
void LED_init(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x04; // activate clock for Port C
  delay++;
  delay++;
  GPIOAMSEL_C &= ~0x10; // disable analog function of PC4
  GPIOAMSEL_C &= ~0x20; // disable analog function of PC5
  GPIOAMSEL_C &= ~0x40; // disable analog function of PC6
  GPIODIR_C |= 0x10; // set PC4 to output
  GPIODIR_C |= 0x20; // set PC5 to output
  GPIODIR_C |= 0x40; // set PC6 to output
  GPIOAFSEL_C &= ~0x10; // set PC4 regular port function
  GPIOAFSEL_C &= ~0x20; // set PC5 regular port function
  GPIOAFSEL_C &= ~0x40; // set PC6 regular port function
  GPIODEN_C |= 0x10; // enable digital output on PC4
  GPIODEN_C |= 0x20; // enable digital output on PC5
  GPIODEN_C |= 0x40; // enable digital output on PC6
}
//Turns on individual external LEDs
//takes on parameter char color which corresponds to the color LED to be turned on
//'Y' = yellow LED
//'R' = red LED
//'G' = green LED
void LED_on(char color)
{
  if (color == 'Y'){
    GPIODATA_C |= 0x10;
  } else if (color == 'R'){
    GPIODATA_C |= 0x20;
  } else if (color == 'G'){
    GPIODATA_C |= 0x40;
  }
}
//Turns off individual external LEDs or all external LEDs
//takes on parameter char LED which LEDs to turn off
//'Y' = yellow LED
//'R' = red LED
//'G' = green LED
//'A' = all LED
void LED_off(char LED)
{
  if (LED == 'Y'){
    GPIODATA_C &= ~0x10;
  } else if (LED == 'R'){
    GPIODATA_C &= ~0x20;
  } else if (LED == 'G'){
    GPIODATA_C &= ~0x40;
  } else if (LED == 'A'){
    GPIODATA_C = 0x0;
  }
}

void wait() {
  for (int i = 0; i < 1000000; i++){} //delay
}
  
//This method implements the requirments from the lab spec to create a traffic light state machine
//manages transitions between states and actions to be taken in each state
void trafficLight_SM(int power, int pedestrian)
{
  switch(state) {   // Transitions
    case off:  // Initial transition  
      if (switch_input('O') == 0x8){ //if On/Off button is pressed and was previously unpressed
        state = stop;
      } else {
        state = off;
      }
      break;

    case stop:
      if (switch_input('O') == 0x8) {//if On/Off button is pressed and was previously unpressed
        state = go;
      } else {
        state = off;
      }
      break;

    case go:
      if (switch_input('O') == 0x8) {//if On/Off button is pressed and was previously unpressed
        if (switch_input('P') == 0x4) {
          state = warn;
        } else {
          state = stop;
        }
      }
      else {
        state = off;
      }
      break;
        
    case warn:
      if (switch_input('O') == 0x8) {//if On/Off button is pressed and was previously unpressed
         state = off;
      } else {
        state = stop;
      }
      break;

     default:
        state = stop;
      break;
  } // Transitions

  switch(state) {   // State actions
    case off:
      LED_off('A');
      wait();
      break;

    case stop:
      LED_off('A');
      LED_on('R');
      wait();
      break;
        
    case go:
      LED_off('A');
      LED_on('G');
      wait();
      break;
     
    case warn: 
      LED_off('A');
      LED_on('Y');
      wait();
      break;

    default:
      LED_off('A');
      break;
   } 
}


