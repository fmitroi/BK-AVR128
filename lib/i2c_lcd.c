#include "i2c_lcd.h"

// LCD command constants (for HD44780 via PCF8574)
#define LCD_CMD_CLEAR       0x01
#define LCD_CMD_HOME        0x02
#define LCD_CMD_ENTRY_MODE  0x06
#define LCD_CMD_DISPLAY_ON  0x0C
#define LCD_CMD_FUNCTION_SET 0x28  // 4-bit, 2 lines, 5x8 font
#define LCD_BACKLIGHT_ON    0x08
#define LCD_BACKLIGHT_OFF   0x00
#define LCD_EN              0x04
#define LCD_RS              0x01

// Global variables
static uint8_t lcd_address;    // I2C address of the LCD
static uint8_t lcd_backlight;  // Backlight state
static uint8_t lcd_rows;       // Number of rows
static uint8_t lcd_cols;       // Number of columns

// Low-level I2C functions
static void i2c_init(void) {
    // Set SCL and SDA as outputs
    DDRD |= (1 << I2C_SCL_PIN) | (1 << I2C_SDA_PIN);
    // Set I2C frequency: TWBR = ((F_CPU / I2C_SPEED) - 16) / 2
    TWBR = ((F_CPU / I2C_SPEED) - 16) / 2;
    TWSR = 0;  // Prescaler = 1
}

static void i2c_start(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

static void i2c_stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while (TWCR & (1 << TWSTO));
}

static void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

// Send a byte to the LCD (4-bit mode via PCF8574)
static void lcd_write_byte(uint8_t data, uint8_t rs) {
    uint8_t data_high = (data & 0xF0) | (rs ? LCD_RS : 0) | lcd_backlight;
    uint8_t data_low = ((data << 4) & 0xF0) | (rs ? LCD_RS : 0) | lcd_backlight;

    i2c_start();
    i2c_write(lcd_address << 1);
    i2c_write(data_high | LCD_EN);  // Enable high
    _delay_us(1);
    i2c_write(data_high);           // Enable low
    i2c_write(data_low | LCD_EN);   // Enable high
    _delay_us(1);
    i2c_write(data_low);            // Enable low
    i2c_stop();
    _delay_us(50);  // Wait for LCD to process
}

// Send command to LCD
static void lcd_command(uint8_t cmd) {
    lcd_write_byte(cmd, 0);
}

// Send data to LCD
static void lcd_data(uint8_t data) {
    lcd_write_byte(data, 1);
}

/**
 * @brief Initializes the I2C module for LCD communication.
 * @param address The 7-bit I2C address of the LCD (e.g., 0x27 for PCF8574).
 */
void I2C_LcdInit(uint8_t address) {
    lcd_address = address;
    lcd_backlight = LCD_BACKLIGHT_ON;
    i2c_init();
    _delay_ms(50);  // Wait for LCD to power up
}

/**
 * @brief Starts the LCD with the specified dimensions.
 * @param rows Number of rows (e.g., 2 for a 16x2 LCD).
 * @param columns Number of columns (e.g., 16 for a 16x2 LCD).
 */
void I2C_LcdStart(uint8_t rows, uint8_t columns) {
    lcd_rows = rows;
    lcd_cols = columns;

    // Initialization sequence for HD44780 in 4-bit mode
    _delay_ms(15);
    lcd_command(0x03);
    _delay_ms(5);
    lcd_command(0x03);
    _delay_us(100);
    lcd_command(0x03);
    lcd_command(0x02);  // Set 4-bit mode
    lcd_command(LCD_CMD_FUNCTION_SET);
    lcd_command(LCD_CMD_DISPLAY_ON);
    lcd_command(LCD_CMD_ENTRY_MODE);
    I2C_LcdClear();
}

/**
 * @brief Clears the LCD screen.
 */
void I2C_LcdClear(void) {
    lcd_command(LCD_CMD_CLEAR);
    _delay_ms(2);  // Clear command takes longer
}

/**
 * @brief Sets the cursor position on the LCD.
 * @param row Row number (0-based).
 * @param column Column number (0-based).
 */
void I2C_LcdSetCursor(uint8_t row, uint8_t column) {
    if (row >= lcd_rows || column >= lcd_cols) return;
    uint8_t address = (row == 0) ? 0x00 : 0x40;
    if (row == 1 && lcd_rows > 2) address = 0x14;
    if (row == 2 && lcd_rows > 3) address = 0x54;
    lcd_command(0x80 | (address + column));
}

/**
 * @brief Moves the cursor to the home position (0,0).
 */
void I2C_LcdHome(void) {
    lcd_command(LCD_CMD_HOME);
    _delay_ms(2);  // Home command takes longer
}

/**
 * @brief Prints a string to the LCD at the current cursor position.
 * @param text Pointer to a null-terminated string to display.
 */
void I2C_LcdPrint(const char *text) {
    while (*text) {
        lcd_data(*text++);
    }
}

/**
 * @brief Shifts the entire display one position to the left.
 */
void I2C_LcdMoveLeft(void) {
    lcd_command(0x18);
}

/**
 * @brief Shifts the entire display one position to the right.
 */
void I2C_LcdMoveRight(void) {
    lcd_command(0x1C);
}

/**
 * @brief Enables the LCD backlight.
 */
void I2C_LcdEnableBacklight(void) {
    lcd_backlight = LCD_BACKLIGHT_ON;
    lcd_command(0x00);  // Dummy command to update backlight
}

/**
 * @brief Disables the LCD backlight.
 */
void I2C_LcdDisableBacklight(void) {
    lcd_backlight = LCD_BACKLIGHT_OFF;
    lcd_command(0x00);  // Dummy command to update backlight
}

/**
 * @brief Converts an integer to a string and prints it on the LCD.
 * @param value The integer value to convert and display.
 */
void I2C_LcdPrintInt(int32_t value) {
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