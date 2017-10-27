#ifndef BUTTON_H
#define BUTTON_H

#define DEBOUNCE_COUNT 3
#define LONG_COUNT 1000

#define BOTH 4
#define BOTH_HOLD BOTH * 3
#define UP 2
#define UP_HOLD UP * 3
#define DOWN 1
#define DOWN_HOLD DOWN * 3

#define BUTTON_PORT PORTA
#define UP_BUTTON 0x80
#define DOWN_BUTTON 0x40

void init_button(void);
uint8_t read_button(void);

#endif