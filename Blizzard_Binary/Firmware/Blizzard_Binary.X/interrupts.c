/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "user.h"
#include "uart.h"

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

uint8_t dmx_state = BREAK_STATE;
uint16_t dmx_index = 0;
uint8_t temp;
extern uint8_t tick;
extern uint8_t DMX[513];

void interrupt isr(void)
{
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 separate if blocks.
    Do not use a separate if block for each interrupt flag to avoid run
    time errors. */

    INTCON &= ~0xC0; //stop interrupts

    if(PIR0 & 0x20)
    {
        tick = 1;
        PIR0 &= ~0x20;
        TMR0L = 0x00;
        TMR0H = 0x00;

        PIE0 = 0x20;
    }
    else if(PIR3 & 0x20)
    {
        
        //if frame error put in break mode
        if(RC1STA & 0x04) //FERR
        {
            dmx_state = BREAK_STATE;
            dmx_index = 0;
            temp = RC1REG; //clears all flags
            goto EXIT_ISR;
        }

        temp = RC1REG;
        switch(dmx_state)
        {

            case BREAK_STATE:

                if(dmx_index == 0x00 && temp == 0x00)//start code
                {
                    
                    DMX[0] = temp; //start code goes in 0 index
                    dmx_index = 1;
                    dmx_state = DATA_STATE;
                }
                else
                    dmx_index = 1; //broken DMX frame

                break;
            case DATA_STATE:
                DMX[dmx_index++] = temp;
                if(dmx_index >= 513)
                {
                    dmx_state = BREAK_STATE;
                }
                break;
        }
    }
    
EXIT_ISR:
    INTCON |= 0xC0; //enable interrupts   
}
#endif


