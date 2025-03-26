#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

static inline void ButtonsInit(void) {
    DDRD &= ~((1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3));
    PORTD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3);
}

static inline uint8_t ButtonsRead(void) {
    uint8_t state = PIND & 0x0F;
    if(state != 0x0F) {
        _delay_ms(50);
        state = PIND & 0x0F;
        if(state != 0x0F) {
            if(!(state & (1 << PD0))) return 1;
            if(!(state & (1 << PD1))) return 2;
            if(!(state & (1 << PD2))) return 3;
            if(!(state & (1 << PD3))) return 4;
        }
    }
    return 0;
}

#endif