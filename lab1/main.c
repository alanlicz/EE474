void LED_init(void) { 
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x04; // activate clock for Port C 
    delay++; 
    delay++;

    GPIOAMSEL_C &= ~0x10; // disable analog function of PC4 
    GPIODIR_C |= 0x10; // set PC4 to output 
    GPIOAFSEL_C &= ~0x10; // set PC4 regular port function 
    GPIODEN_C |= 0x10; // enable digital output on PC4
}
// turn on LED connected to PC4 
void LED_on(void) { 
    GPIODATA_C |= 0x10; 
}

// turn off LED connected to PC4 
void LED_off(void) { 
    GPIODATA_C &= ~0x10; 
}