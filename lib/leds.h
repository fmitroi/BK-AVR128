/**
 * @file leds.h
 * @author Florin (enhanced by Grok)
 * @brief Library for controlling LEDs on the BK-AVR128 board.
 * @details Manages 8 LEDs connected to PORTA (PA0-PA7). LEDs are active LOW (anodes to VCC).
 */

 #ifndef LEDS_H
 #define LEDS_H
 
 #include <avr/io.h>
 #include <util/delay.h>
 #include <stdint.h>
 
 // Port and Pin Definitions
 #define LEDS_DDR    DDRA    ///< Data Direction Register for LEDs
 #define LEDS_PORT   PORTA   ///< Output Port for LEDs
 #define LED1        PA0     ///< LED1 connected to PA0
 #define LED2        PA1     ///< LED2 connected to PA1
 #define LED3        PA2     ///< LED3 connected to PA2
 #define LED4        PA3     ///< LED4 connected to PA3
 #define LED5        PA4     ///< LED5 connected to PA4
 #define LED6        PA5     ///< LED6 connected to PA5
 #define LED7        PA6     ///< LED7 connected to PA6
 #define LED8        PA7     ///< LED8 connected to PA7
 
 /**
  * @brief Initialize the LED port.
  * @note Configures all PORTA pins as outputs, turns off LEDs (HIGH), and performs
  *       five short blinks to signal initialization.
  */
 static inline void LedsInit(void) {
     LEDS_DDR = 0xFF;    // All PORTA pins as outputs
     LEDS_PORT = 0xFF;   // All LEDs off (HIGH = off)
 
     for (uint8_t counter = 0; counter < 10; counter++) {
         LEDS_PORT ^= 0xFF;  // Toggle all LEDs
         _delay_ms(50);      // 50ms delay
     }
 }
 
 /**
  * @brief Turn on a single LED.
  * @param bit LED pin to enable (LED1 to LED8)
  * @note Sets pin LOW to turn on LED; does nothing if bit > 7.
  * @example LedSet(LED1); // Turns on LED1
  */
 static inline void LedSet(uint8_t bit) {
     if (bit > 7) return;         // Safety check
     LEDS_PORT &= ~(1 << bit);    // Clear bit to turn on LED
 }
 
 /**
  * @brief Turn off a single LED.
  * @param bit LED pin to disable (LED1 to LED8)
  * @note Sets pin HIGH to turn off LED; does nothing if bit > 7.
  * @example LedClear(LED3); // Turns off LED3
  */
 static inline void LedClear(uint8_t bit) {
     if (bit > 7) return;         // Safety check
     LEDS_PORT |= (1 << bit);     // Set bit to turn off LED
 }
 
 /**
  * @brief Toggle the state of a single LED.
  * @param bit LED pin to toggle (LED1 to LED8)
  * @note Does nothing if bit > 7.
  * @example LedToggle(LED8); // Toggles LED8
  */
 static inline void LedToggle(uint8_t bit) {
     if (bit > 7) return;         // Safety check
     LEDS_PORT ^= (1 << bit);     // Toggle the specified bit
 }
 
 /**
  * @brief Turn on all LEDs.
  * @note Sets PORTA to 0x00 (all LOW).
  */
 static inline void LedSetPort(void) {
     LEDS_PORT = 0x00;  // All LEDs on
 }
 
 /**
  * @brief Turn off all LEDs.
  * @note Sets PORTA to 0xFF (all HIGH).
  */
 static inline void LedClearPort(void) {
     LEDS_PORT = 0xFF;  // All LEDs off
 }
 
 /**
  * @brief Set multiple LEDs using a bit mask.
  * @param mask Bit mask where 0 = LED on, 1 = LED off (e.g., 0xF0 = LED1-LED4 on)
  * @note Added for convenience.
  */
 static inline void LedSetMask(uint8_t mask) {
     LEDS_PORT = mask;
 }
 
 #endif // LEDS_H