#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>

// I2C configuration for BK-AVR128 (ATmega128)
#define I2C_SCL_PORT PORTD
#define I2C_SDA_PORT PORTD
#define I2C_SCL_PIN PD0
#define I2C_SDA_PIN PD1
#define I2C_SPEED 100000UL  // 100 kHz I2C speed
#define F_CPU 8000000UL     // 8 MHz clock from BK-AVR128

/**
 * @brief Initializes the I2C module for LCD communication.
 * @param address The 7-bit I2C address of the LCD (e.g., 0x27 for PCF8574).
 */
void I2C_LcdInit(uint8_t address);

/**
 * @brief Starts the LCD with the specified dimensions.
 * @param rows Number of rows (e.g., 2 for a 16x2 LCD).
 * @param columns Number of columns (e.g., 16 for a 16x2 LCD).
 */
void I2C_LcdStart(uint8_t rows, uint8_t columns);

/**
 * @brief Clears the LCD screen.
 */
void I2C_LcdClear(void);

/**
 * @brief Sets the cursor position on the LCD.
 * @param row Row number (0-based).
 * @param column Column number (0-based).
 */
void I2C_LcdSetCursor(uint8_t row, uint8_t column);

/**
 * @brief Moves the cursor to the home position (0,0).
 */
void I2C_LcdHome(void);

/**
 * @brief Prints a string to the LCD at the current cursor position.
 * @param text Pointer to a null-terminated string to display.
 */
void I2C_LcdPrint(const char *text);

/**
 * @brief Shifts the entire display one position to the left.
 */
void I2C_LcdMoveLeft(void);

/**
 * @brief Shifts the entire display one position to the right.
 */
void I2C_LcdMoveRight(void);

/**
 * @brief Enables the LCD backlight.
 */
void I2C_LcdEnableBacklight(void);

/**
 * @brief Disables the LCD backlight.
 */
void I2C_LcdDisableBacklight(void);

/**
 * @brief Converts an integer to a string and prints it on the LCD.
 * @param value The integer value to convert and display.
 */
void I2C_LcdPrintInt(int32_t value);

#endif // I2C_LCD_H