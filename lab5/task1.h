/
#ifndef HEADER1_H
#define HEADER1_H

//Controls clock enabled/disabled for all ports
#define RCGCGPIO (((volatile uint32_t )0x400FE608))

//used for setting pins as output/input
#define GPIODIR_F (((volatile uint32_t )0x4005D400))
#define GPIODIR_N (((volatile uint32_t )0x40064400))
#define GPIODIR_J (((volatile uint32_t )0x40060400))

//used to enable ports as digital output
#define GPIODEN_F (((volatile uint32_t )0x4005D51C))
#define GPIODEN_N (((volatile uint32_t )0x4006451C))
#define GPIODEN_J (((volatile uint32_t )0x4006051C))

//used to turn on and off pins
#define GPIODATA_F (((volatile uint32_t )0x4005D3FC))
#define GPIODATA_N (((volatile uint32_t )0x400643FC))
#define GPIODATA_J (((volatile uint32_t )0x400603FC))

//used to attach pull-up resistors
#define GPIOPUR_J (((volatile uint32_t )0x40060510))

//new
#define RCGCPWM (((volatile uint32_t )0x400FE640))
#define GPIOAFSEL_A (((volatile uint32_t )0x40058420)) //for port A
#define GPIOPCTL_A (((volatile uint32_t )0x4005852C)) //for port A
#define PWMCC (((volatile uint32_t )0x40028FC8)) 
#define PWM0CTL (((volatile uint32_t )0x40028040)) 
#define PWM0GENA (((volatile uint32_t )0x40028060)) 
#define PWM0GENB (((volatile uint32_t )0x40028064)) 
#define PWM0LOAD (((volatile uint32_t )0x40028050)) 
#define PWM0CMPA (((volatile uint32_t )0x40028058)) 
#define PWM0CMPB (((volatile uint32_t )0x4002805C)) 
#define PWMENABLE (((volatile uint32_t *)0x40028008)) 





#endif //HEADER1_H