/**
 * @file keypad.h
 * @author Florin (enhanced by Grok)
 * @brief Library for reading a 4x4 keypad on the BK-AVR128 board.
 * @details Uses PD0-PD3 as outputs (rows) and PD4-PD7 as inputs with pull-ups (columns).
 *          Returns key number (1-16) or 0 if no key is pressed.
 */

 #ifndef KEYPAD_H
 #define KEYPAD_H
 
 #include <avr/io.h>
 #include <stdint.h>
 #include <util/delay.h>
 
 /**
  * @brief Initialize the 4x4 keypad.
  * @note Configures PD0-PD3 as outputs (rows) set HIGH and PD4-PD7 as inputs with pull-ups (columns).
  */
 static inline void KeypadInit(void) {
     DDRD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3);   // Rows as outputs
     PORTD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3);  // Rows HIGH
     DDRD &= ~((1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7)); // Columns as inputs
     PORTD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);  // Pull-ups on columns
 }
 
 /**
  * @brief Read the pressed key from the keypad.
  * @return Key number (1-16) or 0 if no key is pressed.
  * @note Key mapping:
  *       - Row 0: 1 (PD4), 2 (PD5), 3 (PD6), 4 (PD7)
  *       - Row 1: 5 (PD4), 6 (PD5), 7 (PD6), 8 (PD7)
  *       - Row 2: 9 (PD4), 10 (PD5), 11 (PD6), 12 (PD7)
  *       - Row 3: 13 (PD4), 14 (PD5), 15 (PD6), 16 (PD7)
  *       Includes 50ms debounce delay.
  */
 static inline uint8_t KeypadRead(void) {
     for (uint8_t row = 0; row < 4; row++) {
         PORTD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3); // All rows HIGH
         PORTD &= ~(1 << (PD0 + row));                              // Current row LOW
         _delay_us(10);                                             // Stabilization delay
 
         uint8_t col_state = PIND & 0xF0; // Read columns (PD4-PD7)
         if (col_state != 0xF0) {         // A column is LOW
             _delay_ms(50);               // Debounce
             col_state = PIND & 0xF0;
             if (col_state != 0xF0) {
                 if (!(col_state & (1 << PD4))) return (row * 4) + 1;
                 if (!(col_state & (1 << PD5))) return (row * 4) + 2;
                 if (!(col_state & (1 << PD6))) return (row * 4) + 3;
                 if (!(col_state & (1 << PD7))) return (row * 4) + 4;
             }
         }
     }
     return 0; // No key pressed
 }
 
 #endif // KEYPAD_H