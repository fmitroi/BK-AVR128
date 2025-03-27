#include "../lib/lcd.h"

int main(void) {
    // Initialize LCD in 4-bit mode
    LcdInit(LCD_MODE_4BIT);
    LcdStart(2, 16);  // 16x2 LCD

    // Display a welcome message
    LcdPrint("Hello, BK-AVR128!");
    LcdSetCursor(1, 0);
    LcdPrint("Grok is here!");

    // Enable backlight and show a counter
    LcdEnableBacklight();
    uint16_t counter = 0;

    while (1) {
        LcdSetCursor(1, 11);
        LcdPrintInt(counter++);
        _delay_ms(500);

        // Shift display for fun
        if (counter % 10 == 0) {
            LcdMoveLeft();
        } else if (counter % 5 == 0) {
            LcdMoveRight();
        }
    }

    return 0;
}