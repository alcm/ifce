TARGET=posture_watcher
SRC=src/posture_watcher.c src/hardware.c src/adxl345.c lib/uart_logger.c lib/i2c.c
INC=-I./inc -I./lib
MCU=atmega32u4
COM=/dev/ttyACM0

app:
	avr-gcc -O2 -Wl,-u,vfprintf -lprintf_flt -lm -mmcu=$(MCU) $(INC) $(SRC) -o $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

lib:

burn:
	avrdude -p $(MCU) -c avr109 -P $(COM) -U flash:w:$(TARGET).hex

clean:
	rm $(TARGET).elf $(TARGET).hex
