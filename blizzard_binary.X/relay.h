#ifndef RELAY_H
#define RELAY_H

#define RELAY_PORT PORTA
#define RELAY_PIN (1 << 0)

void init_relay(void);
void relay_on(void);
void relay_off(void);

#endif