#include "../lib/i2c_lcd.h"

int main(void) {
    // Initialize I2C LCD at address 0x27 (common for PCF8574-based modules)
    I2C_LcdInit(0x27);
    I2C_LcdStart(2, 16);  // 16x2 LCD

    // Display a welcome message
    I2C_LcdPrint("Hello, BK-AVR128!");
    I2C_LcdSetCursor(1, 0);
    I2C_LcdPrint("Grok rocks!");

    // Enable backlight and show a counter
    I2C_LcdEnableBacklight();
    uint16_t counter = 0;

    while (1) {
        I2C_LcdSetCursor(1, 11);
        I2C_LcdPrintInt(counter++);
        _delay_ms(500);

        // Shift display for fun
        if (counter % 10 == 0) {
            I2C_LcdMoveLeft();
        } else if (counter % 5 == 0) {
            I2C_LcdMoveRight();
        }
    }

    return 0;
}