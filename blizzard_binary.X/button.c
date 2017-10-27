#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include "button.h"

void init_button()
{

    //BUTTON A6, A7
    TRISA |= 0xC0;
    ANSELA &= ~0xC0;   
}

uint8_t read_button()
{
    static uint32_t up_count = 0;
    static uint32_t down_count = 0;
    static uint32_t both_count = 0;
    //0 for nothing
    //1 for top
    //2 for bottom
    //3 for both
    
    if(!(BUTTON_PORT & UP_BUTTON) && !(BUTTON_PORT & DOWN_BUTTON))
    {
        if(both_count < LONG_COUNT)
            both_count++;

        if(both_count == LONG_COUNT)
            return BOTH_HOLD;
        if(both_count == DEBOUNCE_COUNT)
            return BOTH;
    }
    else if(!(BUTTON_PORT & UP_BUTTON))
    {
        if(up_count < LONG_COUNT)
            up_count++;
        
        if(up_count == LONG_COUNT)
            return UP_HOLD;
        if(up_count == DEBOUNCE_COUNT)
            return UP;       
    }
    else if(!(BUTTON_PORT & DOWN_BUTTON))
    {
        if(down_count < LONG_COUNT)
            down_count++;
        
        if(down_count == LONG_COUNT)
            return DOWN_HOLD;
        if(down_count == DEBOUNCE_COUNT)
            return DOWN;       
    }
    else
    {
        both_count = 0;
        up_count = 0;
        down_count = 0;
    }
    return 0;
}