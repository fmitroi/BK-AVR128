/*
 * File: port.h
 * Author: Florin (refactored by ChatGPT)
 * Description:
 *   Library for controlling and managing the digital input and output pins
 *   of the ATmega128 microcontroller using AVR-GCC.
 *
 *   Provides functions to configure pins as input or output,
 *   enable pull-up resistors, read and write logic levels,
 *   and toggle pin states.
 *
 * Usage Example:
 *   // Set PA0 as output
 *   PORT_SetPinDirection(&DDRA, 0, PORT_DIR_OUT);
 *
 *   // Set PA0 high
 *   PORT_WritePin(&PORTA, 0, true);
 *
 *   // Read the state of PB1
 *   bool state = PORT_ReadPin(&PINB, 1);
 *
 *   // Toggle the state of PC2
 *   PORT_TogglePin(&PINC, 2);
 *
 * Notes:
 *   - Designed for ports A to G of the ATmega128
 *   - Valid pin numbers are 0 to 7
 */

#ifndef PORT_H
#define PORT_H

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

/** Enum for pin direction */
typedef enum {
    PORT_DIR_IN,   // Set pin as input
    PORT_DIR_OUT   // Set pin as output
} port_dir_t;

/** Enum for pull-up configuration */
typedef enum {
    PORT_PULL_OFF, // No pull-up
    PORT_PULL_UP   // Enable pull-up
} port_pull_t;

/**
 * @brief Set the direction of a specific pin
 * @param ddr Pointer to DDRx register
 * @param pin Pin number (0-7)
 * @param dir PORT_DIR_IN or PORT_DIR_OUT
 */
static inline void PORT_SetPinDirection(volatile uint8_t *ddr, uint8_t pin, port_dir_t dir) {
    if (pin > 7) return;
    if (dir == PORT_DIR_OUT)
        *ddr |= (1 << pin);
    else
        *ddr &= ~(1 << pin);
}

/**
 * @brief Configure pull-up resistor for a pin
 * @param port Pointer to PORTx register
 * @param ddr Pointer to DDRx register
 * @param pin Pin number (0-7)
 * @param pull PORT_PULL_UP or PORT_PULL_OFF
 */
static inline void PORT_SetPullUp(volatile uint8_t *port, volatile uint8_t *ddr, uint8_t pin, port_pull_t pull) {
    if (pin > 7) return;
    *ddr &= ~(1 << pin); // Always configure as input
    if (pull == PORT_PULL_UP)
        *port |= (1 << pin);
    else
        *port &= ~(1 << pin);
}

/**
 * @brief Write a logic level to a pin
 * @param port Pointer to PORTx register
 * @param pin Pin number (0-7)
 * @param level true = HIGH, false = LOW
 */
static inline void PORT_WritePin(volatile uint8_t *port, uint8_t pin, bool level) {
    if (pin > 7) return;
    if (level)
        *port |= (1 << pin);
    else
        *port &= ~(1 << pin);
}

/**
 * @brief Read the logic level of a pin
 * @param pinreg Pointer to PINx register
 * @param pin Pin number (0-7)
 * @return true if pin is HIGH, false if LOW
 */
static inline bool PORT_ReadPin(volatile uint8_t *pinreg, uint8_t pin) {
    if (pin > 7) return false;
    return (*pinreg & (1 << pin));
}

/**
 * @brief Toggle the logic level of a pin
 * @param pinreg Pointer to PINx register (used for toggling in AVR)
 * @param pin Pin number (0-7)
 */
static inline void PORT_TogglePin(volatile uint8_t *pinreg, uint8_t pin) {
    if (pin > 7) return;
    *pinreg = (1 << pin);
}

#endif // PORT_H
