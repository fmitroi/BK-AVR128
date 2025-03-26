#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

static inline void KeypadInit(void) {
    // PD0-PD3 como salidas (filas)
    DDRD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3);
    PORTD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3);  // Filas en HIGH

    // PD4-PD7 como entradas (columnas)
    DDRD &= ~((1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
    PORTD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);  // Pull-ups en columnas
}

static inline uint8_t KeypadRead(void) {
    for (uint8_t row = 0; row < 4; row++) {
        // Poner todas las filas en HIGH
        PORTD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3);
        // Poner la fila actual en LOW
        PORTD &= ~(1 << (PD0 + row));
        
        // Pequeño retardo para estabilizar
        _delay_us(10);

        // Leer columnas (PD4-PD7)
        uint8_t col_state = PIND & 0xF0;
        if (col_state != 0xF0) {  // Alguna columna en LOW
            _delay_ms(50);  // Debounce
            col_state = PIND & 0xF0;
            if (col_state != 0xF0) {
                if (!(col_state & (1 << PD4))) return (row * 4) + 1;  // K1, K5, K9, K13
                if (!(col_state & (1 << PD5))) return (row * 4) + 2;  // K2, K6, K10, K14
                if (!(col_state & (1 << PD6))) return (row * 4) + 3;  // K3, K7, K11, K15
                if (!(col_state & (1 << PD7))) return (row * 4) + 4;  // K4, K8, K12, K16
            }
        }
    }
    return 0;  // Ninguna tecla presionada
}

#endif