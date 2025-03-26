# General Configuration
MCU = atmega128
F_CPU = 8000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Ilib
LDFLAGS = -mmcu=$(MCU)
SIZE = avr-size

# Project variable (defaults to LedBlink if not specified)
PROJECT ?= LedBlink

# Common library sources
LIB_SOURCES := $(wildcard lib/*.c)

# avrdude configuration for Arduino UNO as ISP
PROGRAMMER = stk500v1
PORT = /dev/ttyArduinoUNO
BAUD = 19200

# Default target
all:
	@echo "🛠️ Compiling $(PROJECT)..."
	$(CC) $(CFLAGS) $(LIB_SOURCES) $(PROJECT)/main.c -o $(PROJECT)/main.elf
	$(OBJCOPY) -O ihex $(PROJECT)/main.elf $(PROJECT)/main.hex
	@echo "✅ Compilation completed."
	@echo "========================================="
	@echo "📏 Flash memory usage:"
	@$(SIZE) --format=avr --mcu=$(MCU) $(PROJECT)/main.elf | awk '/Program/ {print $$0}'
	@echo "========================================="
	@echo "📊 Data memory usage:"
	@$(SIZE) --format=avr --mcu=$(MCU) $(PROJECT)/main.elf | awk '/Data/ {print $$0}'
	@echo "========================================="
	@echo "💾 EEPROM usage:"
	@$(SIZE) --format=avr --mcu=$(MCU) $(PROJECT)/main.elf | awk '/EEPROM/ {print $$0}'
	@echo "========================================="

# Show memory usage
size:
	@echo "📏 Showing memory usage for $(PROJECT)..."
	$(SIZE) --mcu=$(MCU) -C $(PROJECT)/main.elf

# Clean project
clean:
	@echo "🧹 Cleaning $(PROJECT)..."
	rm -f $(PROJECT)/main.elf $(PROJECT)/main.hex
	@echo "✅ Cleaned $(PROJECT)"

# Flash the microcontroller
flash:
	@echo "🚀 Flashing $(PROJECT) to ATmega128..."
	avrdude -c $(PROGRAMMER) -p m128 -P $(PORT) -b $(BAUD) -U flash:w:$(PROJECT)/main.hex:i
	@echo "✅ Code flashed to ATmega128"

# Verify flashed code
verify:
	@echo "🔍 Verifying code for $(PROJECT)..."
	avrdude -c $(PROGRAMMER) -p m128 -P $(PORT) -b $(BAUD) -U flash:v:$(PROJECT)/main.hex:i
	@echo "✅ Verification complete"

# Program fuses
fuses:
	@echo "⚙️ Programming fuses (LFUSE=$(LFUSE), HFUSE=$(HFUSE))..."
	avrdude -c $(PROGRAMMER) -p m128 -P $(PORT) -b $(BAUD) \
	-U lfuse:w:$(LFUSE):m \
	-U hfuse:w:$(HFUSE):m \
	-U efuse:w:$(EFUSE):m
	@echo "✅ Fuses programmed successfully"

# Read fuses
read_fuses:
	@echo "🔎 Reading fuses..."
	avrdude -c $(PROGRAMMER) -p m128 -P $(PORT) -b $(BAUD) \
	-U lfuse:r:-:h \
	-U hfuse:r:-:h \
	-U efuse:r:-:h

# Phony targets
.PHONY: all size clean flash verify fuses read_fuses