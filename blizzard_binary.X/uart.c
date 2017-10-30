#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include "uart.h"

void init_uart()
{
    //GPIO SETUP
    TRISC |= 0xC0; //RX as input
    //TRISC &= ~0x40; //TX as output
    ANSELC &= ~0xC0; //TX-RX as digital IO
    
    //Peripheral Pin Select (PPS) Registers
    RX1DTPPS = 0x17;
    TX1CKPPS = 0x16;
    
    //USART Configuration
    
    //Baud rate config
    BAUD1CON = 0x0A;//TEST
    //SP1BRGL = 31;
    SP1BRGL = 7;
    SP1BRGH = 0x00;
    
    //Enable Registers
    TX1STA = 0xC0; //test
    RC1STA |= 0xD0; 
    
    //Interrupt Setup
    PIE3 = 0x20;
    INTCON |= 0xC0;
}