#include "../lib/board.h"

/**
 * @brief Generate a short beep using the buzzer with pseudo-random duration.
 * @param minTime  Minimum duration of the beep in milliseconds.
 * @param maxTime  Maximum duration of the beep in milliseconds.
 * @note Example: beep(20, 100); // Beep duration between 20ms and 100ms.
 */
static inline void beep(uint8_t minTime, uint8_t maxTime) {
    static uint8_t seed = 42;  // Initial seed for pseudo-randomness
    seed = (seed * 17 + 43) & 0xFF;  // Simple LFSR-like update
    uint8_t range = maxTime - minTime;
    uint8_t randomTime = minTime + (seed % range);  // Pseudo-random value in range
    
    BuzzerOn();  // Activate the buzzer
    for (uint8_t i = 0; i < randomTime; i++) {
        _delay_ms(1);  // Delay 1ms per iteration
    }
    BuzzerOff();  // Deactivate the buzzer
}

/**
 * @brief Main application entry point.
 * @return int  Returns 0 on exit (never reached due to infinite loop).
 */
int main(void) {
    // Initialize hardware components
    BoardInit();   // Set up board peripherals for low power mode
    KeypadInit();  // Initialize keypad module
    LedsInit();    // Initialize LEDs with startup blink sequence
    BuzzerInit();  // Initialize buzzer module

    uint8_t prevKey = 0;  // Variable to store the previous key state (0 = no key pressed)

    // Main infinite loop
    while (1) {
        uint8_t key = KeypadRead();  // Read the pressed key from the keypad

        // Turn off all LEDs efficiently using the port function
        LedClearPort();

        // Turn on the corresponding LED based on keypad input
        switch (key) {
            case 1: LedSet(LED1); break;  // Key 1: Turn on LED1
            case 2: LedSet(LED2); break;  // Key 2: Turn on LED2
            case 3: LedSet(LED3); break;  // Key 3: Turn on LED3
            case 4: LedSet(LED4); break;  // Key 4: Turn on LED4
            case 5: LedSet(LED5); break;  // Key 5: Turn on LED5
            case 6: LedSet(LED6); break;  // Key 6: Turn on LED6
            case 7: LedSet(LED7); break;  // Key 7: Turn on LED7
            case 8: LedSet(LED8); break;  // Key 8: Turn on LED8
            default: break;               // No action for invalid keys
        }

        // Beep only on key press (rising edge detection) with random duration
        if (key != 0 && prevKey == 0) {  // Key pressed and no key was pressed before
            beep(20, 100);               // Beep for a random duration between 20ms and 100ms
        }
        prevKey = key;  // Update previous key state

        // Latch control for external LED driver (e.g., 74HC573)
        LatchLeds_On();   // Enable latch to update LED states
        _delay_us(10);    // Short delay for latch timing (10 microseconds)
        LatchLeds_Off();  // Disable latch after update
    }

    return 0;  // Never reached due to infinite loop
}