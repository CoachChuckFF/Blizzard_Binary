/******************************************************************************/
/* Files to Include                                                           */
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
#include "led.h"
#include "timer.h"
#include "button.h"
#include "relay.h"
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

uint8_t DMX[513];
uint8_t DMX_ADDRESS = 1;

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    init_led();
    init_button();
    init_relay();
    init_timer();
    init_uart();
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Enable interrupts */
}

