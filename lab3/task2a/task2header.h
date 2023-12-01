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

//used to enable ports as digital output
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))

//used to turn on and off pins
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

#define GPIODIR_E (*((volatile uint32_t *)0x4005C400)) //GPIO Direction (input vd output)
#define GPIODEN_E (*((volatile uint32_t *)0x4005C51C)) // GPIO Digital Enable
#define GPIODATA_E (*((volatile uint32_t *)0x4005C3FC))
#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))//GPIO analog mode select
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420)) //GPIO Alternate Function Select

//onboard buttons

//used for setting pins as output/input
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))

//used to enable ports as digital output
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))

//used to turn on and off pins
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))

//used to attach pull-up resistors
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))






/*
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
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C)) 
#define GPTMRIS_1 (*((volatile uint32_t *)0x4003101C)) 
#define GPTMRIS_2 (*((volatile uint32_t *)0x4003201C)) 

//used to clear TATORIS bit
//#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))
#define GPTMICR_1 (*((volatile uint32_t *)0x40031024))
#define GPTMICR_2 (*((volatile uint32_t *)0x40032024))

#define GPTMIMR_0 (*((volatile uint32_t *)0x40030018))
#define GPTMIMR_1 (*((volatile uint32_t *)0x40031018))
#define GPTMIMR_2 (*((volatile uint32_t *)0x40032018))

#define EN_0 (*((volatile uint32_t *)0xE000E100))

//interupt for port J
#define GPIOIM_J (*((volatile uint32_t *)0x40060410))
#define EN_1 (*((volatile uint32_t *)0xE000E104)) 

//interupt for port N
#define GPIOIM_N (*((volatile uint32_t *)0x40064410))
#define EN_2 (*((volatile uint32_t *)0xE000E108)) 

//for clear
#define GPIOICR_J (*((volatile uint32_t *)0x4006041C)) 
#define GPIOICR_N (*((volatile uint32_t *)0x4006441C))

#define GPIOIBE_N (*((volatile uint32_t *)0x40064408)) */

#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))

//used for disabling timer
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))

//used to select 32 bit timer configuration
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))

//used to enable periodic timer mode
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))

//used to set starting value for timers to count down from
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))

//used to determine when timer has counted down to 0
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C)) 

//used to clear TATORIS bit
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))

#define GPTMIMR_0 (*((volatile uint32_t *)0x40030018))


#define EN_0 (*((volatile uint32_t *)0xE000E100))
//lab 3 new

#define RCGCADC         (*((volatile uint32_t *)0x400FE638)) //run mode clock gating control  -->enable ADC clock
#define ADCSSPRI        (*((volatile uint32_t *)0x40038020)) //GPIO Alternate Function Select //using ADC0 base not ADC1 base
#define ADCCC           (*((volatile uint32_t *)0x40038FC8)) //ADC Clock Configuration
#define ADCACTSS        (*((volatile uint32_t *)0x40038000)) //ASC Active Sample Sequencer
#define ADCEMUX         (*((volatile uint32_t *)0x40038014)) //ADC Event Multiplexer Select
#define ADDCSSCTL3      (*((volatile uint32_t *)0x400380A4)) //ADC Sample Sequence Control 3
#define ADCIM           (*((volatile uint32_t *)0x40038008)) //Interupt mask
#define ADCSSMUX3       (*((volatile uint32_t *)0x400380A0)) //ADC Sample Sequence Extended Input Multiplexer
#define ADCSSEMUX3      (*((volatile uint32_t *)0x400380B8)) //ADC Sample Sequence Extended Input Multiplexer
#define GPTMADCEV       (*((volatile uint32_t *)0x40030070)) //GPTM ADC event - link with timer 
#define ADCRIS          (*((volatile uint32_t *)0x40038004)) //monitoring ADC interrupt
#define ADCISC          (*((volatile uint32_t *)0x4003800C)) //clearing ADC interrupt

#define ADCSSFIFO3 	(*((volatile uint32_t *)0x400380A8)) //ADC Sample Sequence3 Result

//for using the temperature sensor below 

//#define ADCSSCTL1 (*((volatile uint32_t *)0x40038064)) // ADC Sample Sequence Control 1 - set ts0 bit 
#define ADCSSTSH3 	(*((volatile uint32_t *)0x400380BC))//ADC Sample Sequence 1 Sample and Hold Time - should be configured for at least 16 ADC clocks

//task 2 new below 


//used for setting pins as output/input
#define GPIODIR_A 	(*((volatile uint32_t *)0x40058400))

//used to enable ports as digital output
#define GPIODEN_A 	(*((volatile uint32_t *)0x4005851C))

//used to turn on and off pins
#define GPIODATA_A 	(*((volatile uint32_t *)0x400583FC))

#define GPIOAMSEL_A 	(*((volatile uint32_t *)0x40058528))//GPIO analog mode select

#define GPIOAFSEL_A 	(*((volatile uint32_t *)0x40058420)) //GPIO Alternate Function Select

#define UARTIBRD 	(*((volatile uint32_t *)0x4000C024)) //UART Integer Baud-Rate Divider
#define UARTFBRD 	(*((volatile uint32_t *)0x4000C028)) //UART Fractional Baud-Rate Divisor

//not sure which of these are needed
//#define UARTPP (*((volatile uint32_t *)0x4000CFC0)) //UART Peripheral Properties
//#define UARTCC (*((volatile uint32_t *)0x4000CFC8)) //UART Clock Configuration
//#define UARTPeriphID0 (*((volatile uint32_t *)0x4000CFE0)) //UART Peripheral Identification 0
//#define UARTPCellID0 (*((volatile uint32_t *)0x4000CFF0)) //UART PrimeCell Identification 0 
//#define UART9BITAMASK (*((volatile uint32_t *)0x4000C0A8)) //UART 9-Bit Self Address Mask
//#define UARTICR (*((volatile uint32_t *)0x4000C044)) // UART Interrupt Clear
//#define UARTRIS (*((volatile uint32_t *)0x4000C03C)) // UART Raw Interrupt Status
#define RCGCUART 	(*((volatile uint32_t *)0x400FE618)) // Universal Asynchronous Receiver/Transmitter Run Mode Clock
#define GPIODR2R_A 	(*((volatile uint32_t *)0x40058500)) // GPIO 2-mA Drive Select
#define GPIOSLR_A       (*((volatile uint32_t *)0x40058518)) // GPIO Slew Rate Control Select
#define GPIOPCTL_A      (*((volatile uint32_t *)0x4005852C)) // GPIO port control  
#define UARTCTL         (*((volatile uint32_t *)0x4000C030)) // UART Control
#define UARTLCRH        (*((volatile uint32_t *)0x4000C02C)) // UART Line Control
#define UARTCC          (*((volatile uint32_t *)0x4000CFC8)) // UART Clock Configuration
#define UARTDR          (*((volatile uint32_t *)0x4000C000)) // UART data  
#define UARTFR          (*((volatile uint32_t *)0x4000C018)) // Flag register

#endif //__HEADER1_H__