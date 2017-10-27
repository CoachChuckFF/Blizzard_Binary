#ifndef LED_H
#define LED_H

#define LED_A (1 << 3) //PortD
#define LED_B (1 << 5) //PortC
#define LED_C (1 << 6) //PortD
#define LED_D (1 << 7) //PortD
#define LED_E (1 << 5) //PortD
#define LED_F (1 << 2) //PortD
#define LED_G (1 << 4) //PortD

#define DIGIT_2 (1 << 2) //PortE
#define DIGIT_1 (1 << 1) //PortE
#define DIGIT_0 (1 << 0) //PortE

#define DIGIT_COUNT 3


void init_led(void);
void update_number(uint16_t number);
void display_number(uint8_t digit, uint8_t number);
void update_display(void);
void clear_display(void);

#endif