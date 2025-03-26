/**
 * @file buzzer.h
 * @author Florin (enhanced by Grok)
 * @brief Library for controlling the buzzer on the BK-AVR128 board.
 * @details Buzzer is connected to PE7; active HIGH.
 */

 #ifndef BUZZER_H
 #define BUZZER_H
 
 #include <avr/io.h>
 #include <util/delay.h>
 
 // Buzzer Pin Definitions
 #define BUZZER_DIR  DDRE    ///< Data Direction Register for buzzer
 #define BUZZER_PORT PORTE   ///< Output Port for buzzer
 #define BUZZER_PIN  PE7     ///< Buzzer connected to PE7
 
 /**
  * @brief Initialize the buzzer.
  * @note Configures PE7 as output and turns off the buzzer (LOW).
  */
 static inline void BuzzerInit(void) {
     BUZZER_DIR |= (1 << BUZZER_PIN);   // PE7 as output
     BUZZER_PORT &= ~(1 << BUZZER_PIN); // Buzzer off
 }
 
 /**
  * @brief Turn on the buzzer.
  * @note Sets PE7 HIGH to activate the buzzer.
  */
 static inline void BuzzerOn(void) {
     BUZZER_PORT |= (1 << BUZZER_PIN);
 }
 
 /**
  * @brief Turn off the buzzer.
  * @note Sets PE7 LOW to deactivate the buzzer.
  */
 static inline void BuzzerOff(void) {
     BUZZER_PORT &= ~(1 << BUZZER_PIN);
 }
 
 /**
  * @brief Generate a short beep.
  * @param duration_ms Duration of the beep in milliseconds
  * @note Turns on the buzzer for the specified duration, then turns it off.
  */
 static inline void BuzzerBeep(uint16_t duration_ms) {
     BuzzerOn();
     _delay_ms(duration_ms);
     BuzzerOff();
 }
 
 #endif // BUZZER_H