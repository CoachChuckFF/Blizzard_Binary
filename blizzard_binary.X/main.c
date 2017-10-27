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

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

extern uint8_t DMX[513];
extern uint8_t DMX_ADDRESS;
uint8_t RELAY_ON = 0;
uint8_t tick = 0;
uint8_t toggle = 0;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    uint8_t temp=0;
    uint32_t n = 0;
    uint32_t j = 0;
    DMX_ADDRESS = 1;
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    
    /* Initialize I/O and Peripherals for application */
    InitApp();

    DMX_ADDRESS = 1;
    
    while(1)
    {
    n = DMX[3];
    if(n != 130)
        DMX_ADDRESS = n;
    
        if(tick)
        {
            //DMX_ADDRESS = DMX[3];
            //TODO test this on another pin
            /*if(DMX[3] > 33)
            {
                if(!RELAY_ON)
                {
                    relay_on();
                    DMX_ADDRESS++;
                    RELAY_ON = 1;
                }
            }
            else if(DMX[3] <= 33)
            {
                if(RELAY_ON)
                {
                    relay_off();
                    DMX_ADDRESS--;
                    RELAY_ON = 0;
                }
            }*/
            
            switch(read_button())
            {
                case UP:
                    //DMX_ADDRESS++;
                    break;
                case DOWN:
                    //DMX_ADDRESS--;
                    break;
                case UP_HOLD:
                    //DMX_ADDRESS = 1;
                    break;
                case DOWN_HOLD:
                    update_display();
                    break;
                default:
                    break;
            }
                   
            update_number(DMX_ADDRESS);
            update_display();
            
            tick = 0;
            CLRWDT();
        }

    }

}

