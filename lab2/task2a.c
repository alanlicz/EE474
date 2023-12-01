#include <stdint.h>
#include <stdio.h>
#include "lab2.h"

void led_and_switch_init(void);
void timer_init(void);

void timer_init(void){
  /*
  RCGCTIMER |= 0x1; //enable timer 0 
  GPTMCTL_0 &= ~0x1; //disable timer 0 //used to be == 0x0                                      
  GPTMCFG_0 = 0x0; //enables 32 bit timer configuration
  GPTMTAMR_0 |= 0x2; //configuring TAMR bitand TACDIR bit (periodic mode and counting down)
  GPTMTAILR_0 = 0xF42400; //16,000,000 in HEX to achieve a 1 Hz blink rate
  GPTMCTL_0 |= 0x1; //enabling timer 0
  */
  RCGCTIMER |= 0x1; //enable timer 0 
  GPTMCTL_0 &= ~0x1; //disable timer 0 //used to be == 0x0
  GPTMCFG_0 = 0x00000000; //step required per the lab spec                                         
  GPTMCFG_0 = 0x0; //enables 32 bit timer configuration
  GPTMTAMR_0 |= 0x2; //configuring TAMR bitand TACDIR bit (periodic mode and counting down)
  GPTMTAMR_0 |= 0x0; //configuring TACDIR bit not needed?
  GPTMTAILR_0 = 0xF42400; //16,000,000 in HEX to achieve a 1 Hz blink rate
  EN_0 = (1 << 19);
  GPTMIMR_0 = 0x1; //Interrupt is enabled
  GPTMCTL_0 |= 0x1; //enabling timer 0 
}

//Acts as a delay in the program by implementing timer 0 in periodic operation mode
/*
void wait(int multiplier) {
  GPTMCTL_0 &= ~0x1; //disable timer 0 //used to be == 0x0
  GPTMTAILR_0 = 0xF42400; //16,000,000 in HEX to achieve a 1 Hz blink rate
  GPTMCTL_0 |= 0x1; //enabling timer 0 
  
  for (int i = 1; i <= multiplier; i++){
    while (GPTMRIS_0 == 0x0){} //delay while timer is counting down
    GPTMICR_0 = 0x1; //clearing TATORIS bit
  }
}
*/

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

/*
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
*/
int i = 1;
enum states {led1, led2, led3, led4} state;
void Timer0A_Handler(void) {
    printf("state: %d\n", state);
    switch(state) {
        case led1:
            printf("%d\n", i);
            if (i % 4 == 1) {
            state = led2;
            }
            i++;
            GPIODATA_F = 0x0;
            GPIODATA_N = 0x2;
            break;
        
        case led2:
            printf("%d\n", i);
            if (i % 4 == 2) {
            state = led3;
            }
            i++;
            GPIODATA_F = 0x0;
            GPIODATA_N = 0x1;
            break;
            
        case led3:
            printf("%d\n", i);
            if (i % 4 == 3) {
            state = led4;
            }
            i++;
            GPIODATA_F = 0x10;
            GPIODATA_N = 0x0;
            break;
            
        case led4:
            printf("%d\n", i);
            if (i % 4 == 0) {
            state = led1;
            }
            i++;
            GPIODATA_F = 0x1;
            GPIODATA_N = 0x0;
            break;
        
        default:
            state = led1;
            break;
    }
}

int main(void){
    printf("Test!");
    led_and_switch_init();
    timer_init();
    while(1) {}
    return 0;
}