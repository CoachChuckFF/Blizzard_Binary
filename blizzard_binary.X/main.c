/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "led.h"
#include "uart.h"
#include "button.h"
#include "relay.h"

#define DMX_DEBOUNCE_TICK 3 //ticks until DMX is valid

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

extern uint8_t DMX[513];
uint8_t RELAY_ON = 0;
uint8_t tick = 0;
uint8_t toggle = 0;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    uint8_t dmx = 0;
    uint8_t dmx_temp = 0;
    uint8_t dmx_valid = 0;
    uint8_t dmx_debounce_count = 0;
    
    //TODO get old DMX ADDRESS
    DMX_ADDRESS = 1;
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    
    /* Initialize I/O and Peripherals for application */
    InitApp();


    
    while(1)
    {
    
        if(tick)
        {
            
            dmx = DMX[DMX_ADDRESS];
            
            if(dmx == dmx_temp)
            {
                if(dmx_debounce_count >= DMX_DEBOUNCE_TICK)
                {
                    dmx_valid = 1;                    
                }
                else
                {
                    dmx_debounce_count++;
                    dmx_valid = 0;
                }            
            }
            else
            {
                dmx_debounce_count = 0;     
                dmx_valid = 0;
            }
            
            dmx_temp = dmx;

            //TODO test this on another pin
            //change if its a dimmer
            if(dmx_valid)
            {
                if(dmx)
                {
                    if(!RELAY_ON)
                    {
                        relay_on();
                        RELAY_ON = 1;
                    }
                }
                else
                {
                    if(RELAY_ON)
                    {
                        relay_off();
                        RELAY_ON = 0;
                    }
                }
            }
            
            switch(read_button())
            {
                case UP:
                    DMX_ADDRESS++;
                    break;
                case DOWN:
                    DMX_ADDRESS--;
                    break;
                case UP_HOLD:
                    DMX_ADDRESS = 1;
                    break;
                case DOWN_HOLD:
                    update_display();
                    break;
                default:
                    break;
            }
                   
            if(dmx_valid && dmx)
                update_number(dmx);
            else
                update_number(DMX_ADDRESS);
            update_display();
            
            tick = 0;
            CLRWDT();
        }

    }

}

