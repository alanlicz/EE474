#include <stdint.h>
#include "lab1.h"

void wait() {
  for (int i = 0; i < 1000000; i++){} //delay
}

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

int main(void)
{
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
  
  
  while (1) {
    
    task1b();
    //task1a();
  }
  return 0;
}