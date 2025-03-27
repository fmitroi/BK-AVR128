/**
 * @file board.h
 * @author Florin (enhanced by Grok)
 * @brief Board-level initialization and library management for BK-AVR128.
 * @details Includes peripheral disable for low power and conditional library includes.
 */

 #ifndef BOARD_H
 #define BOARD_H
 
 #include <avr/io.h>
 #include <util/delay.h>
 #include <stdint.h>
 #include <stdbool.h>
 
 // Conditional Library Includes
 #define USE_CLOCK_CONFIG  ///< Enable clock_config.h
 #define USE_PORT          ///< Enable port.h
 #define USE_LEDS          ///< Enable leds.h
 #define USE_KEYPAD        ///< Enable keypad.h
 #define USE_BUZZER        ///< Enable buzzer.h
 #define USE_BUTTONS       ///< Enable buttons.h
 #define USE_74HC573       ///< Enable 74hc573.h
 #define USE_I2C_LCD       ///< Enable i2c_lcd.h
 #define USE_LCD           ///< Enable lcd.h
 
 #ifdef USE_CLOCK_CONFIG
     #include "clock_config.h"
 #endif
 #ifdef USE_PORT
     #include "port.h"
 #endif
 #ifdef USE_LEDS
     #include "leds.h"
 #endif
 #ifdef USE_KEYPAD
     #include "keypad.h"
 #endif
 #ifdef USE_BUZZER
     #include "buzzer.h"
 #endif
 #ifdef USE_BUTTONS
     #include "buttons.h"
 #endif
 #ifdef USE_74HC573
     #include "74hc573.h"
 #endif
 #ifdef USE_I2C_LCD
     #include "i2c_lcd.h"
 #endif
 #ifdef USE_LCD
 #include "lcd.h"
#endif
 
 /**
  * @brief Initialize the BK-AVR128 board for low-power mode.
  * @note Disables ADC, UART, SPI, TWI, and timers. Configures all ports as inputs with pull-ups,
  *       except PE7 (buzzer) as output to prevent unintended sound.
  */
 static inline void BoardInit(void) {
     ADCSRA &= ~(1 << ADEN);                     // Disable ADC
     UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0));   // Disable UART RX/TX
     SPCR &= ~(1 << SPE);                        // Disable SPI
     TWCR &= ~(1 << TWEN);                       // Disable TWI
     TCCR0 &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));  // Stop Timer0
     TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); // Stop Timer1
     TCCR2 &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));  // Stop Timer2
     TCCR3B &= ~((1 << CS32) | (1 << CS31) | (1 << CS30)); // Stop Timer3
 
     DDRA = 0x00; DDRB = 0x00; DDRC = 0x00; DDRD = 0x00; // All ports as inputs
     DDRE = 0x00; DDRF = 0x00; DDRG = 0x00;
 
     BuzzerInit(); // Initialize buzzer (PE7)
 
     PORTA = 0xFF; PORTB = 0xFF; PORTC = 0xFF; PORTD = 0xFF; // Pull-ups
     PORTE = 0xFF; PORTF = 0xFF; PORTG = 0x1F;              // PORTG has 5 pins
 }
 
 /**
  * @brief Reset board to initial state.
  * @note Calls BoardInit to restore low-power configuration.
  */
 static inline void BoardReset(void) {
     BoardInit();
 }
 
 #endif // BOARD_H