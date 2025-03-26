#ifndef LEDS_H
#define LEDS_H

// PORT and Pin Macros
#define LEDS_DDR    DDRA    // Data Direction Register for LEDs
#define LEDS_PORT   PORTA   // Output Port for LEDs
#define LED1        PA0     // LED1 connected to PA0
#define LED2        PA1     // LED2 connected to PA1
#define LED3        PA2     // LED3 connected to PA2
#define LED4        PA3     // LED4 connected to PA3
#define LED5        PA4     // LED5 connected to PA4
#define LED6        PA5     // LED6 connected to PA5
#define LED7        PA6     // LED7 connected to PA6
#define LED8        PA7     // LED8 connected to PA7

/**
 * @brief   Initialize the LED port.
 * @note    Configures all PORTA pins as outputs and turns off LEDs initially.
 *          Performs five short blinks to indicate initialization.
 */
static inline void LedsInit(void) {
    LEDS_DDR = 0xFF;    // Set all PORTA pins as outputs
    LEDS_PORT = 0xFF;   // Set all LEDs off (assuming anodes to VCC, LOW = on)

    // Five short blinks to signal initialization
    for (uint8_t counter = 0; counter < 10; counter++) {
        LEDS_PORT ^= 0xFF;  // Toggle all LEDs
        _delay_ms(50);      // 50ms delay between toggles
    }
}

/**
 * @brief   Turn on a single LED.
 * @param   bit  LED pin to enable (LED1 to LED8)
 * @note    Example: LedSet(LED1); // Turns on LED1
 *          Does nothing if bit > 7.
 */
static inline void LedSet(uint8_t bit) {
    if (bit > 7) return;         // Guard against invalid bit
    LEDS_PORT &= ~(1 << bit);    // Clear bit to turn on LED (LOW = on)
}

/**
 * @brief   Turn off a single LED.
 * @param   bit  LED pin to disable (LED1 to LED8)
 * @note    Example: LedClear(LED3); // Turns off LED3
 *          Does nothing if bit > 7.
 */
static inline void LedClear(uint8_t bit) {
    if (bit > 7) return;         // Guard against invalid bit
    LEDS_PORT |= (1 << bit);     // Set bit to turn off LED (HIGH = off)
}

/**
 * @brief   Toggle the state of a single LED.
 * @param   bit  LED pin to toggle (LED1 to LED8)
 * @note    Example: LedToggle(LED8); // Toggles LED8
 *          Does nothing if bit > 7.
 */
static inline void LedToggle(uint8_t bit) {
    if (bit > 7) return;         // Guard against invalid bit
    LEDS_PORT ^= (1 << bit);     // Toggle the specified bit
}

/**
 * @brief   Turn on all LEDs.
 * @note    Assumes anodes connected to VCC; LOW state turns LEDs on.
 */
static inline void LedSetPort(void) {
    LEDS_PORT = 0x00;  // All bits low to turn on all LEDs
}

/**
 * @brief   Turn off all LEDs.
 * @note    Assumes anodes connected to VCC; HIGH state turns LEDs off.
 */
static inline void LedClearPort(void) {
    LEDS_PORT = 0xFF;  // All bits high to turn off all LEDs
}

#endif // LEDS_H