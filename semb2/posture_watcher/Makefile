TARGET = posture_watcher
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Wall -Werror -Wextra -O2
LDFLAGS = -Wl,-u,vfprintf -lprintf_flt -lm
SOURCES = src/posture_watcher.c src/hardware.c src/adxl345.c lib/uart_logger.c lib/i2c.c
INCLUDE_PATH = -I./include -I./lib
MCU = atmega32u4
COM = /dev/ttyACM0

all: app burn

app:
	@echo "Compiling app ..."
	$(CC) $(CFLAGS) $(LDFLAGS) -mmcu=$(MCU) $(INCLUDE_PATH) $(SOURCES) -o $(TARGET).elf
	$(OBJCOPY) -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

burn:
	@echo "\nFlashing app into microcontroller using the port $(COM) ..."
	avrdude -p $(MCU) -c avr109 -P $(COM) -U flash:w:$(TARGET).hex

clean:
	@rm $(TARGET).elf $(TARGET).hex
