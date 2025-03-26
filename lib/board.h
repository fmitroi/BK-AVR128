#ifndef BOARD_H
#define BOARD_H

// AVR-gcc and standard C libraries include
#include <avr/io.h>         // AVR device-specific IO definitions
#include <util/delay.h>     // Convenience functions for busy-wait delay loops
#include <stdint.h>         // Standard Integer Types
#include <stdbool.h>        // Boolean type and values

/* Macros for enabling/disabling library includes
 * Comment or uncomment as needed
 */
#define USE_CLOCK_CONFIG
#define USE_PORT
#define USE_LEDS
#define USE_KEYPAD
#define USE_BUZZER
#define USE_BUTTONS
#define USE_74HC573

// Conditional library includes
#ifdef USE_CLOCK_CONFIG
    #include "clock_config.h"
#endif

#ifdef USE_PORT  // Corregí: #ifndef USE_PORT -> #ifdef USE_PORT
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

/**
 * @brief Disable peripherals for Low Power Start Mode.
 * @note  Disables ADC, UART, SPI, TWI, and timers. Sets all ports as inputs with pull-ups,
 *        except for PORTE Bit7 (buzzer), which is set as output to avoid unintended sound.
 */
static inline void BoardInit(void) {
    ADCSRA &= ~(1 << ADEN);                     // Disable ADC
    UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0));   // Disable UART RX and TX
    SPCR &= ~(1 << SPE);                        // Disable SPI
    TWCR &= ~(1 << TWEN);                       // Disable TWI (I2C)
    TCCR0 &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));  // Stop Timer0
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); // Stop Timer1
    TCCR2 &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));  // Stop Timer2
    TCCR3B &= ~((1 << CS32) | (1 << CS31) | (1 << CS30)); // Stop Timer3

    // Set all ports as inputs
    DDRA = 0x00; DDRB = 0x00; DDRC = 0x00; DDRD = 0x00;
    DDRE = 0x00; DDRF = 0x00; DDRG = 0x00;

    // Initialize buzzer to avoid unintended sound (PORTE Bit7)
    BuzzerInit();

    // Enable pull-ups on all ports (except PORTE Bit7 handled by BuzzerInit)
    PORTA = 0xFF; PORTB = 0xFF; PORTC = 0xFF; PORTD = 0xFF;
    PORTE = 0xFF; PORTF = 0xFF; PORTG = 0x1F;
}

/*
 * After this function, peripherals and I/O can be configured as needed.
 */

#endif // BOARD_H