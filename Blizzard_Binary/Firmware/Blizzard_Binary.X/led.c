#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "led.h"

//TODO update with EEPROM
uint16_t NUMBER = 1;

void init_led()
{
    //LED PORT D
    TRISD &= ~(LED_A | LED_C | LED_D | LED_E | LED_F | LED_G);
    ANSELD &= ~(LED_A | LED_C | LED_D | LED_E | LED_F | LED_G);
    WPUD &= ~(LED_A | LED_C | LED_D | LED_E | LED_F | LED_G);
    ODCOND &= ~(LED_A | LED_C | LED_D | LED_E | LED_F | LED_G);
    
    //LED PORT C
    TRISC &= ~(LED_B);
    ANSELC &= ~(LED_B);
    WPUC &= ~(LED_B);
    ODCONC &= ~(LED_B);
    
    //LED PORT E
    TRISE &= ~(DIGIT_0 | DIGIT_1 | DIGIT_2);
    ANSELE &= ~(DIGIT_0 | DIGIT_1 | DIGIT_2);
    WPUE &= ~(DIGIT_0 | DIGIT_1 | DIGIT_2);
    ODCONE &= ~(DIGIT_0 | DIGIT_1 | DIGIT_2);
    

}

void update_number(uint16_t number)
{
    NUMBER = number;
}

void update_display()
{
    static uint8_t digit_tick = 0;
    
    if(digit_tick++ > DIGIT_COUNT)
        digit_tick = 0;
        
    switch(digit_tick)
    {
        case 0:
            display_number(0, NUMBER % 10);
            break;
        case 1:
            if(NUMBER > 9)
                display_number(1, ((NUMBER % 100)-(NUMBER % 10)) / 10);
            else
                display_number(1, 10);
            break;
        case 2:
            if(NUMBER > 99)
                display_number(2, ((NUMBER % 1000) - (NUMBER % 100)) / 100);
            else
                display_number(2, 10);
            break;   
    }
}

//10 is no show
void display_number(uint8_t digit, uint8_t number)
{
    clear_display();
    if(number > 9)
        return;
    
    switch(digit)
    {
        case 0:
            PORTE |= DIGIT_0;
            break;
        case 1:
            PORTE |= DIGIT_1;
            break;
        case 2: 
            PORTE |= DIGIT_2;
            break;
        default:
            break;
    }
    
    switch(number)
    {
        case 0: 
            PORTD |= LED_G;
            break;
        case 1:
            PORTD |= (LED_A | LED_D | LED_E | LED_F | LED_G);
            break;
        case 2:
            PORTD |= (LED_F | LED_C);
            break;
        case 3:
            PORTD |= (LED_E | LED_F);
            break;
        case 4:
            PORTD |= (LED_A | LED_D | LED_E);
            break;
        case 5:
            PORTD |= (LED_E);
            PORTC |= (LED_B);
            break;
        case 6:
            PORTC |= (LED_B);
            break;
        case 7:
            PORTD |= (LED_E | LED_D | LED_G | LED_F);
            break;
        case 8:
            //nothing!
            break;
        case 9:
            PORTD |= (LED_D | LED_E);
            break;
    }
    
}

void clear_display()
{
    //clears whole display
    PORTD &= ~(LED_A | LED_C | LED_D | LED_E | LED_F | LED_G);
    PORTC &= ~(LED_B);
    PORTE &= ~(DIGIT_0 | DIGIT_1 | DIGIT_2);
}

