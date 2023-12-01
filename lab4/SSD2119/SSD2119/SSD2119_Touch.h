/*********************************************************************
 * SSD2119_Touch.h
 * The header file of the SSD2119 touchpad driver.
 ********************************************************************/

#ifndef __SSD2119_TOUCH_H__
#define __SSD2119_TOUCH_H__

// uncomment the corresponding line below to choose the ADC 
// module for the touchpad.
//#define TOUCH_USE_ADC0
#define TOUCH_USE_ADC1

// ************** Touch_Init *******************************
// - Initializes the GPIO used for the touchpad
// *********************************************************
// Input: none
// Output: none
// *********************************************************
void Touch_Init( void );

// ************** Touch_ReadX ******************************
// - 
// *********************************************************
// Input: none
// Output: X
// *********************************************************
unsigned long Touch_ReadX( void );

// ************** Touch_ReadY ********************************
// - 
// *********************************************************
// Input: none
// Output: Y
// *********************************************************
unsigned long Touch_ReadY( void );

#endif /* __SSD2119_TOUCH_H__ */
