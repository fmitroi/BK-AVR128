#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>

// LCD pin configuration for BK-AVR128 (example pins, adjustable)
#define LCD_DATA_PORT PORTB    // Data lines (4 or 8 bits)
#define LCD_DATA_DDR  DDRB
#define LCD_DATA_PIN  PINB
#define LCD_CTRL_PORT PORTC    // Control lines (RS, RW, EN)
#define LCD_CTRL_DDR  DDRC
#define LCD_RS        PC0      // Register Select
#define LCD_RW        PC1      // Read/Write
#define LCD_EN        PC2      // Enable

// LCD mode options
typedef enum {
    LCD_MODE_4BIT = 0,  ///< 4-bit mode
    LCD_MODE_8BIT = 1   ///< 8-bit mode
} LcdMode_t;

/**
 * @brief Initializes the LCD with the specified mode.
 * @param mode LCD operating mode (LCD_MODE_4BIT or LCD_MODE_8BIT).
 */
void LcdInit(LcdMode_t mode);

/**
 * @brief Starts the LCD with the specified dimensions.
 * @param rows Number of rows (e.g., 2 for a 16x2 LCD).
 * @param columns Number of columns (e.g., 16 for a 16x2 LCD).
 */
void LcdStart(uint8_t rows, uint8_t columns);

/**
 * @brief Clears the LCD screen.
 */
void LcdClear(void);

/**
 * @brief Sets the cursor position on the LCD.
 * @param row Row number (0-based).
 * @param column Column number (0-based).
 */
void LcdSetCursor(uint8_t row, uint8_t column);

/**
 * @brief Moves the cursor to the home position (0,0).
 */
void LcdHome(void);

/**
 * @brief Prints a string to the LCD at the current cursor position.
 * @param text Pointer to a null-terminated string to display.
 */
void LcdPrint(const char *text);

/**
 * @brief Shifts the entire display one position to the left.
 */
void LcdMoveLeft(void);

/**
 * @brief Shifts the entire display one position to the right.
 */
void LcdMoveRight(void);

/**
 * @brief Enables the LCD backlight (if connected to a pin).
 */
void LcdEnableBacklight(void);

/**
 * @brief Disables the LCD backlight (if connected to a pin).
 */
void LcdDisableBacklight(void);

/**
 * @brief Converts an integer to a string and prints it on the LCD.
 * @param value The integer value to convert and display.
 */
void LcdPrintInt(int32_t value);

#endif // LCD_H