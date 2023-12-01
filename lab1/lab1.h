#ifndef __HEADER1_H__
#define __HEADER1_H__
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))

#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))

#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))

#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))

//task2 additions

#define GPIOAMSEL_C (*((volatile uint32_t *)0x4005A528)) 
#define GPIODIR_C (*((volatile uint32_t *)0x4005A400))
#define GPIODEN_C (*((volatile uint32_t *)0x4005A51C))
#define GPIOAFSEL_C (*((volatile uint32_t *)0x4005A420))
#define GPIODATA_C (*((volatile uint32_t *)0x4005A3FC))

#define GPIOAMSEL_N (*((volatile uint32_t *)0x40064528))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIOAFSEL_N (*((volatile uint32_t *)0x40064420))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

#define RCGCGPIO         (*((volatile uint32_t *)0x400FE608)) 
#define GPIOAMSEL_C      (*((volatile uint32_t *)0x4005A528)) 
#define GPIODIR_C        (*((volatile uint32_t *)0x4005A400)) 
#define GPIODEN_C        (*((volatile uint32_t *)0x4005A51C)) 
#define GPIOAFSEL_C      (*((volatile uint32_t *)0x4005A420)) 
#define GPIODATA_C       (*((volatile uint32_t *)0x4005A3FC)) 

#endif //__HEADER1_H__