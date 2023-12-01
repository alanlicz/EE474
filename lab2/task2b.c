#include <stdint.h>
#include <stdio.h> 
#include "lab2.h"

void led_and_switch_init(void);
void timer_init(void);

int main(void){
    led_and_switch_init();
    timer_init();
    while(1) {
      printf("%d", GPIODATA_J & 0x2);
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
  
  //new
  EN_1 = (1 << 19); //page 117 in data sheet
  GPIOIM_J = 0x1; //Interrupt is enabled
  GPIOICR_J = 0x3;
}

void timer_init(void){

  
  //GPTMIMR_0 = 0x1; //Interrupt is enabled
  //CFGCTRL |= 0x3;
  RCGCTIMER |= 0x1; //enable timer 0 
  GPTMICR_0 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!
  GPTMCTL_0 &= ~0x1; //disable timer 0 //used to be == 0x0                      
  GPTMCFG_0 = 0x0; //enables 32 bit timer configuration
  GPTMTAMR_0 |= 0x2; //configuring TAMR bitand TACDIR bit (one-shot mode and counting down)
  //GPTMTAMR_0 |= 0x8; //configuring TACDIR bit not needed?
  GPTMTAILR_0 = 0xF42400; //16,000,000 in HEX to achieve a 1 Hz blink rate
  EN_0 = (1 << 19);
  
  //EN_0 = 0x80000; //(1 << 19u);
  GPTMIMR_0 = 0x1; //Interrupt is enabled
  GPTMCTL_0 |= 0x1; //enabling timer 0 
}

enum states {on, off} state;
void Timer0A_Handler(void) {
    printf("state: %d\n", state);
    switch(state) {
        case on:
            state = off;
            GPIODATA_N |= 0x1;
            break;
        
        case off:
            state = on;
            GPIODATA_N &= ~0x1;
            break;
    }
            
}

void PortJ_Handler(void) {
  printf("%d\n", (GPIODATA_J & 0x2));
  //GPIOICR_J |= 0x3;
  
  if ((GPIODATA_J & 0x1) == 0){
     printf("SW1\n");
     GPTMIMR_0 |= 0x1; //Interrupt is enabled
     GPTMCTL_0 |= 0x1; //enabling timer 0 
     GPTMICR_0 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!
     GPIODATA_N &= ~0x2;
     //GPIOICR_J = 0x3;
  }
  if ((GPIODATA_J & 0x2) == 0){ 
    printf("SW2\n");
     GPTMIMR_0 &= ~0x1; //Interrupt is disabled
     GPIODATA_N |= 0x1;
     GPIODATA_N |= 0x2;
     //GPIOICR_J = 0x2;
  } 
  
    GPIOICR_J = 0x3;
/*
  if ((GPIODATA_J & 0x1) == 0){
    if ((GPIODATA_J & 0x2) == 0){ 
     printf("both");
     GPTMIMR_0 &= ~0x1; //Interrupt is disabled
     GPIODATA_N |= 0x1;
     GPIODATA_N |= 0x2;
     //GPIOICR_J = 0x2;
    } else {
     printf("SW1\n");
     GPTMIMR_0 |= 0x1; //Interrupt is enabled
     GPTMCTL_0 |= 0x1; //enabling timer 0 
     GPTMICR_0 |= 0x1; //clearing TATORIS bit *new* <-- this made a difference!
     GPIODATA_N &= ~0x2;
     //GPIOICR_J = 0x3;
    }
     
  }
  if ((GPIODATA_J & 0x2) == 0){ 
    printf("SW2\n");
     GPTMIMR_0 &= ~0x1; //Interrupt is disabled
     GPIODATA_N |= 0x1;
     GPIODATA_N |= 0x2;
     //GPIOICR_J = 0x2;
  } 
  
    GPIOICR_J = 0x3;*/
}