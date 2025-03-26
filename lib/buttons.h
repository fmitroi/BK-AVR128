/**
 * @file buttons.h
 * @author Florin (enhanced by Grok)
 * @brief Library for reading buttons on the BK-AVR128 board.
 * @details Uses PD0-PD3 as inputs with pull-ups; returns button number (1-4) or 0 if none pressed.
 */

 #ifndef BUTTONS_H
 #define BUTTONS_H
 
 #include <avr/io.h>
 #include <stdint.h>
 #include <util/delay.h>
 
 /**
  * @brief Initialize the buttons.
  * @note Configures PD0-PD3 as inputs with pull-ups.
  */
 static inline void ButtonsInit(void) {
     DDRD &= ~((1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3)); // Inputs
     PORTD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3);   // Pull-ups
 }
 
 /**
  * @brief Read the pressed button.
  * @return Button number (1-4) or 0 if no button is pressed.
  * @note Button mapping: 1 (PD0), 2 (PD1), 3 (PD2), 4 (PD3). Includes 50ms debounce.
  */
 static inline uint8_t ButtonsRead(void) {
     uint8_t state = PIND & 0x0F;
     if (state != 0x0F) { // A button is pressed (LOW)
         _delay_ms(50);   // Debounce
         state = PIND & 0x0F;
         if (state != 0x0F) {
             if (!(state & (1 << PD0))) return 1;
             if (!(state & (1 << PD1))) return 2;
             if (!(state & (1 << PD2))) return 3;
             if (!(state & (1 << PD3))) return 4;
         }
     }
     return 0; // No button pressed
 }
 
 #endif // BUTTONS_H