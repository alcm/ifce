TARGET = posture_watcher
SOURCES = $(wildcard src/*.c lib/*.c)
INCLUDE_PATH = -I./include -I./lib
OBJECTS = $(SOURCES:.c=.o)

CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Wall -Werror -Wextra -O2
LDFLAGS = -Wl,-u,vfprintf -lprintf_flt -lm
MCU = atmega32u4

ifndef MCU_PORT
MCU_PORT = /dev/ttyACM0
endif

.PHONY: all app clean install

all: app install

app: $(OBJECTS)
	@echo "\nGenerating app ..."
	$(CC) $(CFLAGS) $(LDFLAGS) -mmcu=$(MCU) $(INCLUDE_PATH) $^ -o $(TARGET).elf
	$(OBJCOPY) -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

install:
	@echo "\nFlashing app into microcontroller using the port $(MCU_PORT) ..."
	avrdude -p $(MCU) -c avr109 -P $(MCU_PORT) -U flash:w:$(TARGET).hex

src/%.o: src/%.c include/%.h
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) $(LDFLAGS) -mmcu=$(MCU) $(INCLUDE_PATH) -c $< -o $@

lib/%.o: lib/%.c lib/%.h
	@echo "Compiling $< ..."
	$(CC) $(CFLAGS) $(LDFLAGS) -mmcu=$(MCU) $(INCLUDE_PATH) -c $< -o $@

clean:
	@rm lib/*.o src/*.o $(TARGET).elf $(TARGET).hex
