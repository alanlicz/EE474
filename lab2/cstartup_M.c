/**************************************************
 *
 * This file contains an interrupt vector for Cortex-M written in C.
 * The actual interrupt functions must be provided by the application developer.
 *
 * Copyright 2007-2017 IAR Systems AB.
 *
 * $Revision: 112610 $
 *
 **************************************************/

#pragma language=extended
#pragma segment="CSTACK"

extern void __iar_program_start( void );

extern void NMI_Handler( void );
extern void HardFault_Handler( void );
extern void MemManage_Handler( void );
extern void BusFault_Handler( void );
extern void UsageFault_Handler( void );
extern void SVC_Handler( void );
extern void DebugMon_Handler( void );
extern void PendSV_Handler( void );
extern void SysTick_Handler( void );

extern void Timer0A_Handler( void );
extern void Timer1A_Handler( void );
extern void Timer2A_Handler( void );
extern void PortJ_Handler( void );
extern void PortN_Handler( void );

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

// The vector table is normally located at address 0.
// When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
// If you need to define interrupt service routines,
// make a copy of this file and include it in your project.
// The name "__vector_table" has special meaning for C-SPY, which
// is where to find the SP start value.
// If vector table is not located at address 0, the user has to initialize
// the  NVIC vector table register (VTOR) before using interrupts.


#pragma location = ".intvec"
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },  //0
  __iar_program_start,             
  NMI_Handler,
  HardFault_Handler,
  MemManage_Handler,
  BusFault_Handler,                //5
  UsageFault_Handler,
  0,
  0,
  0,
  0,                               //10
  SVC_Handler,
  DebugMon_Handler,
  0,
  PendSV_Handler,
  SysTick_Handler,                 //15
  0,
  0,
  0,
  0,
  0,                               //20
  0,
  0,
  0,
  0,
  0,                               //25
  0,
  0,
  0,
  0,
  0,                               //30
  0,
  0,
  0,
  0,
  Timer0A_Handler,                 //35
  0,                               
  Timer1A_Handler,
  0,
  Timer2A_Handler,
  0,                               //40
  0,                               
  0,
  0,
  0,
  0,                               //45
  0,                               
  0,
  0,
  0,
  0,                               //50
  0,                               
  0,
  0,
  0,
  0,                               //55
  0,                               
  0,
  0,
  0,
  0,                               //60
  0,                               
  0,
  0,
  0,
  0,                               //65
  0,                               
  PortJ_Handler,                   //67
  0,                               
  0,                               
  0,                               //70
  0,                               
  0,                               
  0,
  0,
  0,                               //75
  0,                               
  0,                               
  0,
  0,
  0,                               //80
  0,                               
  0,                               
  0,
  0,
  0,                               //85
  0,                               
  0,                               
  0,
  PortN_Handler                    //89
};

#pragma call_graph_root = "interrupt"
__weak void NMI_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void HardFault_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void MemManage_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void BusFault_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void UsageFault_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void SVC_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void DebugMon_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void PendSV_Handler( void ) { while (1) {} }
#pragma call_graph_root = "interrupt"
__weak void SysTick_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void Timer0A_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void Timer1A_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void Timer2A_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void PortJ_Handler( void ) { while (1) {} }

#pragma call_graph_root = "interrupt"
__weak void PortN_Handler( void ) { while (1) {} }

void __cmain( void );
__weak void __iar_init_core( void );
__weak void __iar_init_vfp( void );

#pragma required=__vector_table
void __iar_program_start( void )
{
  __iar_init_core();
  __iar_init_vfp();
  __cmain();
}
