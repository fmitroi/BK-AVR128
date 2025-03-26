#include    "../lib/board.h"

#include <avr/io.h>
#include <util/delay.h>

// Tabla de segmentos para 0-9 (sin invertir)
const uint8_t segment_table[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

// Digitos a mostrar
uint8_t digitos[8] = {1, 2, 3, 4, 5, 6, 7, 8};

int main(void) {
    DDRA = 0xFF;  // PA0 - PA7 salida (control displays)
    DDRC = 0xFF;  // PC0 - PC7 salida (segmentos)
    DDRF |= (1 << PF1) | (1 << PF2);
    PORTF = 0X06;

    while (1) {
        for (uint8_t counter = 0; counter < 8; counter++) {
            PORTC = 0x00;    // Apaga todos los segmentos
            PORTA = 0x00;    // Apaga todos los displays

            uint8_t numero = digitos[counter];
            if (numero < 10) {
                // Invertir los bits para Ánodo Común
                PORTC = ~(segment_table[numero]); // o segment_table[numero] ^ 0xFF;
            } else {
                PORTC = 0xFF;  // Todo apagado en inversión
            }

            PORTA = (1 << counter); // Activa el display correspondiente
            _delay_ms(2);
        }
    }
}

