TARGET = posture_watcher
CFLAGS = -Wall -Werror -O2 -Wl,-u,vfprintf
LDFLAGS = -lprintf_flt -lm
SOURCES = src/posture_watcher.c src/hardware.c src/adxl345.c lib/uart_logger.c lib/i2c.c
INCLUDE_PATH = -I./include -I./lib
MCU = atmega32u4
COM = /dev/ttyACM0

app:
	@echo "Compiling app ..."
	avr-gcc $(CFLAGS) $(LDFLAGS) -mmcu=$(MCU) $(INCLUDE_PATH) $(SOURCES) -o $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

lib:

burn:
	@echo "Flashing app into microcontroller using the port $(COM) ..."
	avrdude -p $(MCU) -c avr109 -P $(COM) -U flash:w:$(TARGET).hex

clean:
	@rm $(TARGET).elf $(TARGET).hex
