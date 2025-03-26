# BK-AVR128 Development Board

![BK-AVR128 Development Board](resources/BK-AVR128.jpg)

Welcome to the **BK-AVR128 Development Board** repository! This project provides a comprehensive set of libraries, examples, and documentation for the BK-AVR128, an evaluation board based on the ATmega128 microcontroller. Whether you're a beginner exploring AVR programming or an experienced developer prototyping with the ATmega128, this repo has you covered.

---

## Overview

The BK-AVR128 is a versatile development board designed for learning and experimenting with the ATmega128 microcontroller. It features a variety of onboard peripherals, including LEDs, 7-segment displays, a keypad, a buzzer, buttons, and communication interfaces like I2C, RS232, and PS/2, plus support for LCD displays and motor control.

- **Microcontroller**: ATmega128
- **Clock**: 8 MHz external crystal
- **Power**: USB Type-B (power only) with a power switch (SW1)
- **Programming**: JTAG (J11) and ISP (J12) connectors

Download the schematic: [BK-AVR128 Schematic](resources/BK-AVR128%20Schematic.pdf)

---

## Hardware Mapping

### Microcontroller Pins and Ports
The ATmega128's ports are mapped to the board's peripherals as follows:

#### PORTA - LEDs and 7-Segment Displays
- **8 Red LEDs** (Active LOW):
  - LED1: PA0
  - LED2: PA1
  - LED3: PA2
  - LED4: PA3
  - LED5: PA4
  - LED6: PA5
  - LED7: PA6
  - LED8: PA7
- **7-Segment Displays** (2x4 digits, controlled via 74HC573 latch):
  - Digits 1-4: PA0-PA3
  - Digits 5-8: PA4-PA7
  - Segments A-G: PC0-PC7 (Active LOW)

#### PORTB - PWM LED
- **PWM LED**: Connected to PB4 (supports PWM output for brightness control).

#### PORTC - 7-Segment Segments
- Segments A-G: PC0-PC7 (Active LOW, via 74HC573 latch)

#### PORTD - I2C, PS/2, and Buttons
- **AT24C02 EEPROM (I2C)**:
  - SCL: PD0
  - SDA: PD1
- **PS/2 Keyboard**:
  - DAT: PD2
  - CLK: PD3
- **Buttons**: Four push buttons mapped to PD0-PD3 (configurable as inputs).

#### PORTE - Communication and Sensors
- **RS232 DB9**:
  - RX1: PE0
  - TX1: PE1
- **TL1838 IR Receiver**:
  - DAT: PE5
- **DS18B20 Temperature Sensor**:
  - DAT: PE6

#### ADC - Variable Resistor (VR1)
- **VR1**: Connected to an ADC pin (e.g., ADC0/PA0, configurable) for analog input adjustment.

#### Real-Time Clock (RTC) with Battery Backup
- **RTC**: Supports an external RTC module (e.g., DS1302/DS3231) with I2C or custom pin mapping (not directly assigned to fixed pins; configurable via software).
- **Battery Backup**: Backup battery slot for RTC, providing power to maintain timekeeping when the board is off (typically VBAT, GND pins).

#### LCD Interfaces
- **LCD1602 (16x2 Character LCD)**:
  - **Female Pin Header**: Available for connection (e.g., J3, configurable pins).
  - **Contrast Adjustment (VR2)**: Variable resistor VR2 for LCD1602 contrast control.
- **LCD12864 (128x64 Graphical LCD)**:
  - **Female Pin Header**: Available for connection (e.g., J15).
  - **Contrast Adjustment (VR3)**: Variable resistor VR3 for LCD12864 contrast control.
  - **Parallel/Serial Bus (J15)**: Supports parallel or SPI mode (VDD, GND, data lines configurable via software).

### Connectors
- **J2 (Male Pin Header)**: GND and VCC output for external devices.
- **J4**: VUSB and GND for USB power distribution.
- **J5**: Stepper motor outputs (configurable pins, typically PORTB or PORTD).
- **J6**: Normal DC motor outputs (configurable pins).
- **J15**: Parallel/serial bus for LCD12864 (includes VDD, GND, and data lines).

### Peripheral Locations
- **LEDs**: 8 red LEDs aligned along the top edge, controllable via PORTA.
- **PWM LED**: Single LED near the center, driven by PB4 with PWM capability.
- **7-Segment Displays**: Two groups of four digits, centrally located, driven by PORTA (digits) and PORTC (segments) through a 74HC573 latch.
- **Buzzer**: Near the bottom left, controlled via software (check `buzzer.h`).
- **Buttons**: Four push buttons near the bottom, mapped to PD0-PD3.
- **Keypad**: 4x4 matrix keypad, interfaced through software (see `keypad.h`).
- **Power Switch (SW1)**: Bottom right, toggles USB power.
- **JTAG/ISP**: Bottom edge, J11 (JTAG) and J12 (ISP) for programming/debugging.
- **VR1**: Variable resistor for ADC input, adjustable via a potentiometer.
- **LCD Headers**: Female headers for LCD1602 and LCD12864, with VR2 and VR3 nearby for contrast tuning.
- **RTC Battery Slot**: Near the RTC connection pins for backup power.

---

## Getting Started

### Prerequisites
- **AVR-GCC**: Compiler for AVR microcontrollers (`sudo apt install avr-gcc` on Linux).
- **avrdude**: Tool for flashing the ATmega128 (`sudo apt install avrdude`).
- **Arduino UNO** (optional): Used as an ISP programmer (adjust `PORT` in `Makefile` if needed).

### Setup
1. Clone the repository:
   ```bash
   git clone https://github.com/fmitroi/BK-AVR128
   cd BK-AVR128

   Using the Makefile in the AVR128 folder, you can compile projects with make PROJECT=<project_name>. Available example projects include ButtonsExample, BuzzerExample, DisplaysExample, KeypadExample, LedBlink, and LedsArrayExample. You can also create new projects in the root of AVR128. Commands available:

make PROJECT=<project_name>: Compiles the specified project, generating .elf and .hex files, and displays memory usage. Example: make PROJECT=LedBlink

make PROJECT=<project_name> clean: Removes the .elf and .hex files from the project folder. Example: make PROJECT=LedBlink clean

make PROJECT=<project_name> flash: Uploads the .hex file to the ATmega128 using avrdude (default: Arduino UNO at /dev/ttyArduinoUNO). Example: make PROJECT=LedBlink flash

make PROJECT=<project_name> size: Shows detailed memory usage (flash, data, EEPROM) of the compiled project. Example: make PROJECT=LedBlink size

make PROJECT=<project_name> verify: Verifies that the uploaded code matches the .hex file. Example: make PROJECT=LedBlink verify

make PROJECT=<project_name> fuses LFUSE=<value> HFUSE=<value> EFUSE=<value>: Programs the ATmega128 fuses (advanced; see datasheet). Example: make PROJECT=LedBlink fuses LFUSE=0xFF HFUSE=0xD9 EFUSE=0xFF

make PROJECT=<project_name> read_fuses: Reads the current fuse values from the ATmega128. Example: make PROJECT=LedBlink read_fuses Use Tab after make PROJECT= to autocomplete available project names.

Compile an example:
make PROJECT=LedBlink

Flash it to the ATmega128:
make PROJECT=LedBlink flash

See each header file for detailed documentation and usage.

Contributing
Found a bug? Want to add a new example? Feel free to:

Open an issue on GitHub.
Submit a pull request with your changes.

Documentation
ATmega128 Datasheet https://ww1.microchip.com/downloads/en/DeviceDoc/doc2467.pdf

License:
This project is released under the . Feel free to use, modify, and distribute it as you see fit.

Happy coding with the BK-AVR128!