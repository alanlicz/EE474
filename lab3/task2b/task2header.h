/*
* Nick Petregal-LeMay & Alan Li
* Nick: 1950981 ---- Alan: 1938332
* 2/16/2023
* This the header file for Lab 3
* This file sets up the registers required to work with UART and ADC
* Also includes registers for onboard LEDs and buttons
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

#define RCGCUART 	(*((volatile uint32_t *)0x400FE618)) // Universal Asynchronous Receiver/Transmitter Run Mode Clock
#define GPIODR2R_A 	(*((volatile uint32_t *)0x40058500)) // GPIO 2-mA Drive Select
#define GPIOSLR_A       (*((volatile uint32_t *)0x40058518)) // GPIO Slew Rate Control Select
#define GPIOPCTL_A      (*((volatile uint32_t *)0x4005852C)) // GPIO port control  
#define UARTCTL         (*((volatile uint32_t *)0x4000C030)) // UART Control
#define UARTLCRH        (*((volatile uint32_t *)0x4000C02C)) // UART Line Control
#define UARTCC          (*((volatile uint32_t *)0x4000CFC8)) // UART Clock Configuration
#define UARTDR          (*((volatile uint32_t *)0x4000C000)) // UART data  
#define UARTFR          (*((volatile uint32_t *)0x4000C018)) // Flag register

#define RCGCUART 	(*((volatile uint32_t *)0x400FE618)) // Universal Asynchronous Receiver/Transmitter Run Mode Clock
#define GPIODR2R_A 	(*((volatile uint32_t *)0x40058500)) // GPIO 2-mA Drive Select
#define GPIOSLR_A       (*((volatile uint32_t *)0x40058518)) // GPIO Slew Rate Control Select
#define GPIOPCTL_A      (*((volatile uint32_t *)0x4005852C)) // GPIO port control  
#define UARTCTL         (*((volatile uint32_t *)0x4000C030)) // UART Control
#define UARTLCRH        (*((volatile uint32_t *)0x4000C02C)) // UART Line Control
#define UARTCC          (*((volatile uint32_t *)0x4000CFC8)) // UART Clock Configuration
#define UARTDR          (*((volatile uint32_t *)0x4000C000)) // UART data  
#define UARTFR          (*((volatile uint32_t *)0x4000C018)) // Flag register

//setup UART2
#define RCGCUART2       (*((volatile uint32_t *)0x400FE618))
#define UARTIBRD2       (*((volatile uint32_t *)0x4000E024))
#define UARTFBRD2       (*((volatile uint32_t *)0x4000E028))
#define UARTLCRH2       (*((volatile uint32_t *)0x4000E02C))
#define UARTCTL2        (*((volatile uint32_t *)0x4000E030))
#define UARTCC2         (*((volatile uint32_t *)0x4000EFC8))
#define UARTFR2         (*((volatile uint32_t *)0x4000E018))
#define UARTDR2         (*((volatile uint32_t *)0x4000E000))

#endif //__HEADER1_H__