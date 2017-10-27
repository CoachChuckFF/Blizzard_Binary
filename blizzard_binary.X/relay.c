#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include "relay.h"

void init_relay()
{
    TRISA &= ~(RELAY_PIN);
    ANSELA&= ~(RELAY_PIN);
    WPUA &= ~(RELAY_PIN);
    ODCONA &= ~(RELAY_PIN);
}

void relay_on()
{
    RELAY_PORT |= RELAY_PIN;
}

void relay_off()
{
    RELAY_PORT &= ~RELAY_PIN;
}
