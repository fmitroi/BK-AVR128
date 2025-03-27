#include "lcd.h"

// LCD command constants (for HD44780)
#define LCD_CMD_CLEAR       0x01
#define LCD_CMD_HOME        0x02
#define LCD_CMD_ENTRY_MODE  0x06
#define LCD_CMD_DISPLAY_ON  0x0C
#define LCD_CMD_FUNCTION_4BIT 0x28  // 4-bit, 2 lines, 5x8 font
#define LCD_CMD_FUNCTION_8BIT 0x38  // 8-bit, 2 lines, 5x8 font

// Global variables
static LcdMode_t lcd_mode;     // Current operating mode
static uint8_t lcd_rows;       // Number of rows
static uint8_t lcd_cols;       // Number of columns
static bool lcd_backlight;     // Backlight state (assuming PB3 as example)

// Low-level LCD functions
static void lcd_pulse_enable(void) {
    LCD_CTRL_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_CTRL_PORT &= ~(1 << LCD_EN);
    _delay_us(50);  // Wait for LCD to process
}

static void lcd_write(uint8_t data, uint8_t rs) {
    // Set RS (0 for command, 1 for data)
    if (rs) LCD_CTRL_PORT |= (1 << LCD_RS);
    else LCD_CTRL_PORT &= ~(1 << LCD_RS);

    // Set RW to write (0)
    LCD_CTRL_PORT &= ~(1 << LCD_RW);

    if (lcd_mode == LCD_MODE_8BIT) {
        LCD_DATA_PORT = data;
        lcd_pulse_enable();
    } else {  // 4-bit mode
        LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
        lcd_pulse_enable();
        LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data << 4) & 0xF0);
        lcd_pulse_enable();
    }
}

// Send command to LCD
static void lcd_command(uint8_t cmd) {
    lcd_write(cmd, 0);
    if (cmd == LCD_CMD_CLEAR || cmd == LCD_CMD_HOME) _delay_ms(2);  // Longer delay
}

// Send data to LCD
static void lcd_data(uint8_t data) {
    lcd_write(data, 1);
}

/**
 * @brief Initializes the LCD with the specified mode.
 * @param mode LCD operating mode (LCD_MODE_4BIT or LCD_MODE_8BIT).
 */
void LcdInit(LcdMode_t mode) {
    lcd_mode = mode;
    lcd_backlight = true;  // Assume backlight on by default

    // Set control pins as outputs
    LCD_CTRL_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN);
    // Set data pins as outputs (PB0-PB7 for 8-bit, PB4-PB7 for 4-bit)
    LCD_DATA_DDR |= (mode == LCD_MODE_8BIT) ? 0xFF : 0xF0;

    // Backlight pin (example: PB3)
    DDRB |= (1 << PB3);
    PORTB |= (1 << PB3);  // Backlight on

    _delay_ms(50);  // Wait for LCD to power up
}

/**
 * @brief Starts the LCD with the specified dimensions.
 * @param rows Number of rows (e.g., 2 for a 16x2 LCD).
 * @param columns Number of columns (e.g., 16 for a 16x2 LCD).
 */
void LcdStart(uint8_t rows, uint8_t columns) {
    lcd_rows = rows;
    lcd_cols = columns;

    // Initialization sequence for HD44780
    _delay_ms(15);
    if (lcd_mode == LCD_MODE_8BIT) {
        lcd_command(0x30);  // 8-bit mode init
        _delay_ms(5);
        lcd_command(0x30);
        _delay_us(100);
        lcd_command(0x30);
        lcd_command(LCD_CMD_FUNCTION_8BIT);
    } else {  // 4-bit mode
        lcd_command(0x03);
        _delay_ms(5);
        lcd_command(0x03);
        _delay_us(100);
        lcd_command(0x02);  // Set 4-bit mode
        lcd_command(LCD_CMD_FUNCTION_4BIT);
    }
    lcd_command(LCD_CMD_DISPLAY_ON);
    lcd_command(LCD_CMD_ENTRY_MODE);
    LcdClear();
}

/**
 * @brief Clears the LCD screen.
 */
void LcdClear(void) {
    lcd_command(LCD_CMD_CLEAR);
}

/**
 * @brief Sets the cursor position on the LCD.
 * @param row Row number (0-based).
 * @param column Column number (0-based).
 */
void LcdSetCursor(uint8_t row, uint8_t column) {
    if (row >= lcd_rows || column >= lcd_cols) return;
    uint8_t address = (row == 0) ? 0x00 : 0x40;
    if (row == 1 && lcd_rows > 2) address = 0x14;
    if (row == 2 && lcd_rows > 3) address = 0x54;
    lcd_command(0x80 | (address + column));
}

/**
 * @brief Moves the cursor to the home position (0,0).
 */
void LcdHome(void) {
    lcd_command(LCD_CMD_HOME);
}

/**
 * @brief Prints a string to the LCD at the current cursor position.
 * @param text Pointer to a null-terminated string to display.
 */
void LcdPrint(const char *text) {
    while (*text) {
        lcd_data(*text++);
    }
}

/**
 * @brief Shifts the entire display one position to the left.
 */
void LcdMoveLeft(void) {
    lcd_command(0x18);
}

/**
 * @brief Shifts the entire display one position to the right.
 */
void LcdMoveRight(void) {
    lcd_command(0x1C);
}

/**
 * @brief Enables the LCD backlight (if connected to PB3).
 */
void LcdEnableBacklight(void) {
    lcd_backlight = true;
    PORTB |= (1 << PB3);
}

/**
 * @brief Disables the LCD backlight (if connected to PB3).
 */
void LcdDisableBacklight(void) {
    lcd_backlight = false;
    PORTB &= ~(1 << PB3);
}

/**
 * @brief Converts an integer to a string and prints it on the LCD.
 * @param value The integer value to convert and display.
 */
void LcdPrintInt(int32_t value) {
    char buffer[12];  // Enough for -2147483648 + null
    int8_t i = 0;

    if (value == 0) {
        lcd_data('0');
        return;
    }

    if (value < 0) {
        lcd_data('-');
        value = -value;
    }

    while (value > 0) {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    }

    while (i > 0) {
        lcd_data(buffer[--i]);
    }
}