# Configuración general
MCU = atmega128
F_CPU = 8000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Ilib
LDFLAGS = -mmcu=$(MCU)
SIZE = avr-size

# Variable que recibe el nombre del proyecto (la carpeta del proyecto)
PROJECT ?= LedBlink  # Si no se pasa como parámetro, por defecto será LedBlink

# Librerías comunes
LIB_SOURCES := $(wildcard lib/*.c)

# Configuración de avrdude para Arduino UNO como ISP
PROGRAMMER = stk500v1
PORT = /dev/ttyArduinoUNO
BAUD = 19200

# Compilación por proyecto
all:
	@echo "🛠️ Compilando $(PROJECT)..."
	$(CC) $(CFLAGS) $(LIB_SOURCES) $(PROJECT)/main.c -o $(PROJECT)/main.elf
	$(OBJCOPY) -O ihex $(PROJECT)/main.elf $(PROJECT)/main.hex
	@echo "✅ Compilación terminada."

	# Mostrar uso de memoria (flash, datos y EEPROM)
	@echo "========================================="
	@echo "Memoria Flash usada y libre:"
	@$(SIZE) --format=avr --mcu=$(MCU) $(PROJECT)/main.elf | awk '/Program/ {print $$0}'
	@echo "========================================="
	@echo "Memoria de datos usada y libre:"
	@$(SIZE) --format=avr --mcu=$(MCU) $(PROJECT)/main.elf | awk '/Data/ {print $$0}'
	@echo "========================================="
	@echo "EEPROM usado y libre (se calcula a partir del tamaño total y la memoria total):"
	@$(SIZE) --format=avr --mcu=$(MCU) $(PROJECT)/main.elf | awk '/EEPROM/ {print $$0}'
	@echo "========================================="

# Mostrar uso de memoria
size:
	@echo "📏 Mostrando uso de memoria para $(PROJECT)..."
	$(SIZE) --mcu=$(MCU) -C $(PROJECT)/main.elf

# Limpiar el proyecto
clean:
	rm -f $(PROJECT)/main.elf $(PROJECT)/main.hex
	@echo "🧹 Limpiado $(PROJECT)"

# Subir el código al microcontrolador
flash:
	@echo "🚀 Subiendo código a $(PROJECT)..."
	avrdude -c $(PROGRAMMER) -p m128 -P $(PORT) -b $(BAUD) -U flash:w:$(PROJECT)/main.hex:i
	@echo "✅ Código subido a ATmega128"

# Verificar el código subido
verify:
	@echo "🔍 Verificando código en $(PROJECT)..."
	avrdude -c $(PROGRAMMER) -p m128 -P $(PORT) -b $(BAUD) -U flash:v:$(PROJECT)/main.hex:i
	@echo "✅ Verificación completa"

# Grabar los FUSES
fuses:
	@echo "⚙️ Grabando fuses (LFUSE=$(LFUSE), HFUSE=$(HFUSE))..."
	avrdude -c $(PROGRAMMER) -p m128 -P $(PORT) -b $(BAUD) \
	-U lfuse:w:$(LFUSE):m \
	-U hfuse:w:$(HFUSE):m \
	-U efuse:w:$(EFUSE):m
	@echo "✅ Fuses programados correctamente"

# Leer los FUSES (extra)
read_fuses:
	@echo "🔎 Leyendo fuses..."
	avrdude -c $(PROGRAMMER) -p m128 -P $(PORT) -b $(BAUD) \
	-U lfuse:r:-:h \
	-U hfuse:r:-:h \
	-U efuse:r:-:h
