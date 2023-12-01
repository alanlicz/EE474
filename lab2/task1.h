/*
* Nick Petregal-LeMay & Alan Li
* Nick: 1950981 ---- Alan: 1938332
* 1/19/2023
* This the header file for Lab 2
* This file sets up the registers required to interact with the LEDs and buttons on the board
*/
#ifndef __HEADER1_H__
#define __HEADER1_H__

//Controls clock enabled/disabled for all ports
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

//used for setting pins as output/input
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))

//used to enable ports as digital output
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))

//used to turn on and off pins
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))

//used to attach pull-up resistors
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))

//for traffic light controller (below)

//controls analog function of ports
#define GPIOAMSEL_C (*((volatile uint32_t *)0x4005A528)) 
#define GPIOAMSEL_N (*((volatile uint32_t *)0x40064528))

//used for setting pins as output/input
#define GPIODIR_C (*((volatile uint32_t *)0x4005A400))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))

//used to enable ports as digital output
#define GPIODEN_C (*((volatile uint32_t *)0x4005A51C))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))

//used to set regular GPIO port function
#define GPIOAFSEL_C (*((volatile uint32_t *)0x4005A420))
#define GPIOAFSEL_N (*((volatile uint32_t *)0x40064420))

//used to turn on and off pins
#define GPIODATA_C (*((volatile uint32_t *)0x4005A3FC))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

//controls analog function of ports
#define GPIOAMSEL_C (*((volatile uint32_t *)0x4005A528)) 
#define GPIOAMSEL_N (*((volatile uint32_t *)0x40064528))

//used for setting pins as output/input
#define GPIODIR_C (*((volatile uint32_t *)0x4005A400))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))

//used to enable ports as digital output
#define GPIODEN_C (*((volatile uint32_t *)0x4005A51C))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))

//used to set regular GPIO port function
#define GPIOAFSEL_C (*((volatile uint32_t *)0x4005A420))
#define GPIOAFSEL_N (*((volatile uint32_t *)0x40064420))

//used to turn on and off pins
#define GPIODATA_C (*((volatile uint32_t *)0x4005A3FC))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))



//new additions in lab 2

//used to Enable and provide a clock to 16/32-bit general-purpose timer 0
//#define RCGCTIMER_0 (*((volatile uint32_t *)0x400FE604))
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))

//used for disabling timer
//#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCTL_1 (*((volatile uint32_t *)0x4003100C))
#define GPTMCTL_2 (*((volatile uint32_t *)0x4003200C))

//used to select 32 bit timer configuration
//#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define GPTMCFG_1 (*((volatile uint32_t *)0x40031000))
#define GPTMCFG_2 (*((volatile uint32_t *)0x40032000))

//used to enable periodic timer mode
//#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define GPTMTAMR_1 (*((volatile uint32_t *)0x40031004))
#define GPTMTAMR_2 (*((volatile uint32_t *)0x40032004))

//used to set starting value for timers to count down from
//#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMTAILR_1 (*((volatile uint32_t *)0x40031028))
#define GPTMTAILR_2 (*((volatile uint32_t *)0x40032028))

//used to determine when timer has counted down to 0
//#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C)) 
#define GPTMRIS (*((volatile uint32_t *)0x4003001C)) 

//used to clear TATORIS bit
//#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))
#define GPTMICR (*((volatile uint32_t *)0x40030024))

#endif //__HEADER1_H__