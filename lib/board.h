/*
BK-AVR128 Development Board Definitions and Settings
MCU: AtMega128
XTAL: 8Mhz
PWM Led     --> PB4 - Active Low
AT24C02     --> SCL - PD0 ; SDA  PD1
ULN2003     --> IN1 - PB0; IN2 - PB1; IN3 - PB2; IN4 - PB3;  IN7 - PB4
DS1302      --> SCLK - PE2; I/O - PE3; RST - PE4 ( BT1 - Battery Backup)
PS/2        --> DAT - PD2; CLK - PD3
ADC POT VR1 --> PF0
TL1838      --> DAT - PE5
DS18B20     --> PE6
RS232-DB9   --> RX1-IN - PE0; TX1-IN - PE1
POT VR2     --> LCD1602 Contrast 
POT VR3     --> LCD12864 Contrast
J14         --> PIN1  - GND
            --> PIN2  - VCC
            --> PIN3  - VL - VR2  Contrast
            --> PIN4  - RS - PB5
            --> PIN5  - R/W - PB6
            --> PIN6  - E - PB7
            --> PIN7  - D0 - PA0
            --> PIN8  - D1 - PA1
            --> PIN9  - D2 - PA2
            --> PIN10 - D3 - PA3
            --> PIN11 - D4 - PA4
            --> PIN12 - D5 - PA5
            --> PIN13 - D6 - PA6
            --> PIN14 - D7 - PA7
            --> PIN15 - BLA - VCC (Backlight Led Anode)
            --> PIN16 - BLK - GND (Backlight Led Cathode)
J16         --> PIN1  - VSS
            --> PIN2  - GND
            --> PIN3  - VO - VR3 Contrast
            --> PIN4  - RS - (CS)   - PB5
            --> PIN5  - RW/SID      - PB6
            --> PIN6  - E/CLK       - PB7
            --> PIN7  - DB0         - PA0
            --> PIN8  - DB1         - PA1
            --> PIN9  - DB2         - PA2
            --> PIN10 - DB3         - PA3
            --> PIN11 - DB4         - PA4
            --> PIN12 - DB5         - PA5
            --> PIN13 - DB6         - PA6
            --> PIN14 - DB7         - PA7
            --> PIN15 - PSB (Parallel / Serial Bit Select )
            --> PIN16 - NC   (Not Connected)
            --> PIN17 - /RST (Not Connected)
            --> PIN18 - VOUT        - VOUT
            --> PIN19 - LEDA (Backlight Led Anode)
            --> PIN20 - LEDK (Backlight Led Cathode)
4X4 Key Matrix  -- >    K1 - K16  --> ROW1      - PD0
                                  --> ROW2      - PD1
                                  --> ROW3      - PD2
                                  --> ROW4      - PD3
                                  --> COLUMN1   - PD4
                                  --> COLUMN2   - PD5
                                  --> COLUMN3   - PD6
                                  --> COLUMN4   - PD7
4X1 KEYS TO GND -->     K17 - K20 --> K17       - PD0
                                  --> K18       - PD1
                                  --> K19       - PD2
                                  --> K20       - PD3
8 RED LEDS SIL - Anode to GND - Active Low (PORT PIN = 0)
(Leds are controlled by U6 74HC573 ALE Pin Connected to PF3 --> Outputs Active High)
LED1 - PA0; LED2 - PA1; LED3 - PA2; LED4 - PA3
LED5 - PA4; LED6 - PA5; LED7 - PA6; LED8 - PA7

2 x 7 Segments display (8 Digits 4 + 4)
(Digits are controlled by U5 74HC573 ALE Pin Connected to PF2 --> Outputs Active High)
(Digits Active High  --> PA0 = 1; PA1 = 1; ... ETC)
Digit1 - PA0; Digit2 - PA1; Digit3 - PA2; Digit4 - PA3
Digit5 - PA4; Digit6 - PA5; Digit7 - PA6; Digit8 - PA7

(Segments are controlled by U4 74HC573 ALE Pin Connected to PF1 --> Outputs Active High)
(Segments Active Low --> PC0 = 0; PC1 = 0; ... ETC)
Segment A - PC0; Segment B - PC1; Segment C - PC2; Segment D - PC3
Segment E - PC4; Segment F - PC5; Segment G - PC6; DP - PC7

BUZZER SP1 BEE--> Connected on PE7 (Active High)
K0 --> Reset Button
D0 --> Power Led
J2 --> Pin Header 3X2 - (1,3,5 - VCC) (2,4,6 - GND)
USB Type B --> Only for power the board
SW1 --> Power Switch
J4  --> 3 Pin Connector (1 - GND; 2 - NC; 3  VCC)
J15 --> 3 Pin Connector (1 - GND; 2 - PSB (LCD12864 Parallel / Serial Bit Control); 3  VCC)
J5  --> 5 Pin Connector (1 - D; 2 - C; 3 - B; 4 - A; 5 -- VCC)
J6  --> 2 Pin Connector (1 - VCC; 2 - OUT7 ULN2003 - Motor Control)

J11 --> JTAG Connector  --> 1 - TCK     - PF4           ______
                        --> 2 -         - GND          |      |
                        --> 3 - TDO     - PF6         1| º  º |2
                        --> 4           - VCC         3| º  º |4
                        --> 5 - TMS     - PF5         5| º  º |6
                        --> 6           - NC          7| º  º |8
                        --> 7 -         - VCC         9| º  º |10        
                        --> 8 -         - NC           |______| 
                        --> 9 - TDI     - PF7
                        --> 10 -        - GND

J12 --> ISP Connector   --> 1 - MOSI    - PF4           ______
                        --> 2 -         - VCC          |      |
                        --> 3 -         - NC          1| º  º |2
                        --> 4           - GND         3| º  º |4
                        --> 5 - REST    - REST        5| º  º |6
                        --> 6           - GND         7| º  º |8
                        --> 7 - SCK     - PB1         9| º  º |10        
                        --> 8 -         - GND          |______| 
                        --> 9 - MISO    - PE1
                        --> 10 -        - GND
*/

#ifndef BOARD_H
#define BOARD_H

#include <avr/io.h>
#include "clock_config.h"
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include "74hc573.h"
#include "port.h"

static inline void MCU_SavePowerInit(void)
{
	/* On AVR devices all peripherals are enabled from power on reset, this
	 * disables all peripherals to save power. Driver shall enable
	 * peripheral if used */
    // Desactivar ADC: Poner ADEN en ADCSRA a 0

    // Desactivar ADC: Poner ADEN en ADCSRA a 0
    ADCSRA &= ~(1 << ADEN);

    // Desactivar USART0: Poner RXEN0 y TXEN0 en UCSR0B a 0
    UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0));

    // Desactivar SPI: Poner SPE en SPCR a 0
    SPCR &= ~(1 << SPE);

    // Desactivar TWI (I2C): Poner TWEN en TWCR a 0
    TWCR &= ~(1 << TWEN);

    // Desactivar Temporizadores: Configurar los bits de prescaler CSn2:0 a 000
    // Timer0 (8-bit): Detener el reloj
    TCCR0 &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));

    // Timer1 (16-bit): Detener el reloj
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));

    // Timer2 (8-bit): Detener el reloj
    TCCR2 &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));

    // Timer3 (16-bit): Detener el reloj
    TCCR3B &= ~((1 << CS32) | (1 << CS31) | (1 << CS30));

    // Configurar todos los puertos como entradas (DDRx = 0)
    DDRA = 0x00;  // PORTA como entrada
    DDRB = 0x00;  // PORTB como entrada
    DDRC = 0x00;  // PORTC como entrada
    DDRD = 0x00;  // PORTD como entrada
    DDRE = 0x00;  // PORTE como entrada
    DDRF = 0x00;  // PORTF como entrada
    DDRG = 0x00;  // PORTG como entrada (solo PG0-PG4 son válidos)

    // Habilitar pull-ups internos en todos los puertos (PORTx = 0xFF)
    PORTA = 0xFF; // Pull-up en PORTA
    PORTB = 0xFF; // Pull-up en PORTB
    PORTC = 0xFF; // Pull-up en PORTC
    PORTD = 0xFF; // Pull-up en PORTD
    PORTE = 0xFF; // Pull-up en PORTE
    PORTF = 0xFF; // Pull-up en PORTF
    PORTG = 0x1F; // Pull-up en PORTG (solo PG0-PG4, 5 bits: 0b00011111)

}


#endif // BOARD_H