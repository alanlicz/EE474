#include <stdint.h>
#include <stdio.h>
#include "task2partc.h"

void extern_switch_init(void);
void timer_init(void);
void LED_on(char color);
void LED_off(char LED);
void check();
unsigned long switch_input(char button);
void trafficLight_SM(int POW, int PED);
void PortN_Handler(void);
void LED_init(void);

int main(void){
  extern_switch_init();
  LED_init();
  timer_init();
  
  while(1) {}
  return -1;
}

void timer_init(void){

  RCGCTIMER |= 0x7; //enable timer 0 
  GPTMICR_0 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!
  GPTMCTL_0 &= ~0x1; //disable timer 0 //used to be == 0x0                      
  GPTMCFG_0 = 0x0; //enables 32 bit timer configuration
  GPTMTAMR_0 |= 0x2; //configuring TAMR bitand TACDIR bit (one-shot mode and counting down)
  GPTMTAILR_0 = 0xF42400 * 5; //16,000,000 in HEX to achieve a 1 Hz blink rate (* 5 for 5 seconds)
  GPTMIMR_0 = 0x1; //Interrupt is enabled

  GPTMICR_1 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!
  GPTMCTL_1 &= ~0x1; //disable timer 0 //used to be == 0x0                                      
  GPTMCFG_1 = 0x0; //enables 32 bit timer configuration
  GPTMTAMR_1 = 0x2; //configuring TAMR bitand TACDIR bit (periodic mode and counting down)
  GPTMTAILR_1 = 0x1E84800; //32,000,000 in HEX to achieve a 1 Hz blink rate
  GPTMIMR_1 = 0x1; //Interrupt is enabled

  GPTMICR_2 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!
  GPTMCTL_2 &= ~0x1; //disable timer 0 //used to be == 0x0                                   
  GPTMCFG_2 = 0x0; //enables 32 bit timer configuration
  GPTMTAMR_2 = 0x2; //configuring TAMR bitand TACDIR bit (periodic mode and counting down)
  GPTMTAILR_2 = 0x1E84800; //32,000,000 in HEX to achieve a 1 Hz blink rate
 
  GPTMIMR_2 = 0x1; //Interrupt is enabled
  GPTMCTL_0 |= 0x1; //enabling timer 0
  //GPTMCTL_1 |= 0x1; //enabling timer 0
  //GPTMCTL_2 |= 0x1; //enabling timer 0
  EN_0 |= 0xA80000; //1010 1000 0000 0000 0000 0000


}

//sets up exteral switches for use through PN2 and PN3
//sets up exteral switches for use through PN2 and PN3
void extern_switch_init(void)
{
  printf("Start external!\n");
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
  
  
  //GPIOIBE_N = 0xC;//interupt on both edges
  
  
  
  GPIOIM_N = 0xC; //Interrupt is enabled
  GPIOICR_N = 0xC; 
  EN_2 = (1 << 9); //page 117 in data sheet 
  printf("Finish external!\n");
}

//sets up exteral LEDs for use through PC4, PC5, and PC6
void LED_init(void)
{
 printf("Start LED!\n");
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
 printf("Finish LED!\n");
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


void Timer1A_Handler(void) {
  //EN_0 &= ~(1 << 19); //enable interupt
  //GPTMCTL_1 &= ~0x1; //disable timer 1
  printf("timer1\n");
  trafficLight_SM(1, 0); 
  GPTMIMR_0 = 0x1;
  GPTMCTL_0 |= 0x1; //start timer interupt, enable timer1
  GPTMICR_0 |= 0x1; //clearing TATORIS bit
  GPTMICR_1 |= 0x1; //clearing TATORIS bit

  
}

void Timer2A_Handler(void) {
       
  //EN_0 &= ~(1 << 21);//enable interupt

  printf("timer2\n");
  GPTMICR_0 |= 0x1; //clearing TATORIS bit
  trafficLight_SM(0, 1);   
  //GPTMIMR_0 = 0x1;
  //GPTMCTL_0 |= 0x1; //start timer interupt, enable timer1
  GPTMICR_0 |= 0x1; //clearing TATORIS bit
  GPTMICR_2 |= 0x1; //clearing TATORIS bit
  //GPTMCTL_2 &= ~0x1; //disable timer 1
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

//This method implements the requirements from the lab spec to create a traffic light state machine
//manages transitions between states and actions to be taken in each state
//This method implements the requirements from the lab spec to create a traffic light state machine
//manages transitions between states and actions to be taken in each state
enum states { off, stop, go, warn } state; //define states for state machine use later on
void trafficLight_SM(int POW, int PED)
{
  switch(state) {   // Transitions
     case off:  // Initial transition  
       if (POW == 1){ //if timer 1 flag raises (on/off button held for 2 seconds)
         state = stop;
       } else {
         state = off;
       }
        break;

     case stop:
        if (POW == 1) {//if timer 1 flag raises (on/off button held for 2 seconds)
          state = off;
        } else {
          state = go;          
        }
        break;

     case go:
        if (POW == 1) {//if timer 1 flag raises (on/off button held for 2 seconds)
           state = off;
        } else if (PED == 1) {//if timer 2 flag raises (pedestrian button held for 2 seconds)
           state = warn;
        } else {
          state = stop;
        }
        break;
        
     case warn:

        if (POW == 1) {//if timer 1 flag raises (on/off button held for 2 seconds)
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
        //GPTMICR_1 |= 0x1; //clearing TATORIS bits
        //GPTMICR_2 |= 0x1; //clearing TATORIS bits
        break;

     case stop:

        LED_off('A');
        LED_on('R');
        //GPTMICR_1 |= 0x1; //clearing TATORIS bits
        //GPTMICR_2 |= 0x1; //clearing TATORIS bits
        break;
        
     case go:

        LED_off('A');
        LED_on('G');
        //GPTMICR_1 |= 0x1; //clearing TATORIS bits
        //GPTMICR_2 |= 0x1; //clearing TATORIS bits
        break;
     
     case warn: 

        LED_off('A');
        LED_on('Y');
        //GPTMICR_1 = 0x1; //clearing TATORIS bits
        //GPTMICR_2 = 0x1; //clearing TATORIS bits
        break;

     default:
        break;
   } 
}

void Timer0A_Handler(void) {
  printf("ye\n");
  trafficLight_SM(0, 0);
  GPTMICR_0 |= 0x1; //clearing TATORIS bit
}

//checks if either button is pressed for 2 seconds
//if a button is not currently pressed the corresponding button timerwill be reset and start counting for 2 seconds
//this works becuase if a button does stay pushed for 2 seconds then the given flag will be raised on GPTMRIS
//the state machine tick will be checking to see if GPTMRIS flag is raised, if so button has been pressed two seconds
void check() {
  printf("%d\n", GPIODATA_N);
  if ((GPIODATA_N & 0x8) == 0x8){
    GPTMIMR_1 = 0x1;
    //GPTMICR_1 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!    
    GPTMCTL_1 |= 0x1; //start timer interupt, enable timer1
    
  } else if (switch_input('O') != 0x8 && (GPTMRIS_1 & 0x1) == 0){
    GPTMIMR_1 = 0x0;
    GPTMCTL_1 &= ~0x1; //disable timer 1
    GPTMICR_1 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!    
   
  } else if ((GPIODATA_N & 0x4) == 0x4){
    GPTMIMR_2 = 0x1;
    //GPTMICR_2 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!
    GPTMCTL_2 |= 0x1; //start timer interupt, enable timer2
    
  } else if (switch_input('P') != 0x4 && (GPTMRIS_2 & 0x1) == 0){
    GPTMIMR_2 = 0x0;
    GPTMCTL_2 &= ~0x1; //disable timer 2
    GPTMICR_2 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!

  }
}


void PortN_Handler(void) {
    printf("Hit!\n");
    GPIOICR_N = 0xC;
    printf("%d", GPIODATA_N);
  if ((GPIODATA_N & 0x8) == 0x8){         
    GPTMICR_1 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!    
    GPTMCTL_1 |= 0x1; //start timer interupt, enable timer1
    
  } else {
    GPTMCTL_1 &= ~0x1; //disable timer 1
  }
  if ((GPIODATA_N & 0x4) == 0x4){
    GPTMICR_2 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!
    GPTMCTL_2 |= 0x1; //start timer interupt, enable timer2
    
  } else {
    GPTMCTL_2 &= ~0x1; //disable timer 2

  }
}

