#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include "timer.h"

void init_timer()
{
    //Timer configuration
    T0CON1 = 0x70; //HFINTOSC - Syncronized - 2 prescaler ~ 1ms
    T0CON0 = 0x90; //enabled - 16 bit - 1:1 prescale
    TMR0L = 0x00;
    TMR0H = 0x00;
    
    //Inturrupts
    PIE0 = 0x20;
}
