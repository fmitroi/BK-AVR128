/**
 * @file port.h
 * @author Florin (refactored and enhanced by Grok)
 * @brief Library for controlling digital I/O pins of the ATmega128 microcontroller.
 * @details Provides functions to configure pin direction, enable pull-ups, read/write logic levels,
 *          and toggle pin states. Designed for AVR-GCC and ports A to G of ATmega128.
 *
 * @example
 *   // Configure PA0 as output and set it HIGH
 *   PORT_SetPinDirection(&DDRA, 0, PORT_DIR_OUT);
 *   PORT_WritePin(&PORTA, 0, true);
 *
 *   // Read PB1 state
 *   bool state = PORT_ReadPin(&PINB, 1);
 *
 *   // Toggle PC2
 *   PORT_TogglePin(&PINC, 2);
 */

 #ifndef PORT_H
 #define PORT_H
 
 #include <avr/io.h>
 #include <stdint.h>
 #include <stdbool.h>
 
 /**
  * @brief Enum for pin direction configuration.
  */
 typedef enum {
     PORT_DIR_IN,   ///< Set pin as input
     PORT_DIR_OUT   ///< Set pin as output
 } port_dir_t;
 
 /**
  * @brief Enum for pull-up resistor configuration.
  */
 typedef enum {
     PORT_PULL_OFF, ///< Disable pull-up resistor
     PORT_PULL_UP   ///< Enable pull-up resistor
 } port_pull_t;
 
 /**
  * @brief Set the direction of a specific pin.
  * @param ddr Pointer to the Data Direction Register (e.g., &DDRA)
  * @param pin Pin number (0-7)
  * @param dir Direction to set (PORT_DIR_IN or PORT_DIR_OUT)
  * @note Does nothing if pin number is out of range (> 7).
  */
 static inline void PORT_SetPinDirection(volatile uint8_t *ddr, uint8_t pin, port_dir_t dir) {
     if (pin > 7) return; // Safety check for valid pin range
     if (dir == PORT_DIR_OUT)
         *ddr |= (1 << pin);
     else
         *ddr &= ~(1 << pin);
 }
 
 /**
  * @brief Configure pull-up resistor for a specific pin.
  * @param port Pointer to the Port Register (e.g., &PORTA)
  * @param ddr Pointer to the Data Direction Register (e.g., &DDRA)
  * @param pin Pin number (0-7)
  * @param pull Pull-up state (PORT_PULL_UP or PORT_PULL_OFF)
  * @note Pin is always set as input; does nothing if pin > 7.
  */
 static inline void PORT_SetPullUp(volatile uint8_t *port, volatile uint8_t *ddr, uint8_t pin, port_pull_t pull) {
     if (pin > 7) return; // Safety check
     *ddr &= ~(1 << pin); // Ensure pin is input
     if (pull == PORT_PULL_UP)
         *port |= (1 << pin);
     else
         *port &= ~(1 << pin);
 }
 
 /**
  * @brief Write a logic level to a specific pin.
  * @param port Pointer to the Port Register (e.g., &PORTA)
  * @param pin Pin number (0-7)
  * @param level Logic level (true = HIGH, false = LOW)
  * @note Does nothing if pin > 7; assumes pin is configured as output.
  */
 static inline void PORT_WritePin(volatile uint8_t *port, uint8_t pin, bool level) {
     if (pin > 7) return; // Safety check
     if (level)
         *port |= (1 << pin);
     else
         *port &= ~(1 << pin);
 }
 
 /**
  * @brief Read the logic level of a specific pin.
  * @param pinreg Pointer to the Pin Register (e.g., &PINA)
  * @param pin Pin number (0-7)
  * @return true if pin is HIGH, false if LOW or pin > 7
  */
 static inline bool PORT_ReadPin(volatile uint8_t *pinreg, uint8_t pin) {
     if (pin > 7) return false; // Safety check
     return (*pinreg & (1 << pin)) != 0; // Return true if bit is set
 }
 
 /**
  * @brief Toggle the logic level of a specific pin.
  * @param pinreg Pointer to the Pin Register (e.g., &PINA)
  * @param pin Pin number (0-7)
  * @note Uses PINx register write trick for toggling; does nothing if pin > 7.
  */
 static inline void PORT_TogglePin(volatile uint8_t *pinreg, uint8_t pin) {
     if (pin > 7) return; // Safety check
     *pinreg = (1 << pin); // Writing to PINx toggles the corresponding PORTx bit
 }
 
 /**
  * @brief Configure all pins of a port at once.
  * @param ddr Pointer to the Data Direction Register (e.g., &DDRA)
  * @param direction Mask where 1 = output, 0 = input (e.g., 0xFF for all outputs)
  * @note Added for convenience; affects entire port.
  */
 static inline void PORT_SetPortDirection(volatile uint8_t *ddr, uint8_t direction) {
     *ddr = direction;
 }
 
 #endif // PORT_H