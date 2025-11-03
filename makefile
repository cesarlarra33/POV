FIRMWARE := glow_LED
all:
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000 -Os -o $(FIRMWARE)/main.elf $(FIRMWARE)/main.c
	avr-objcopy -O binary $(FIRMWARE)/main.elf $(FIRMWARE)/main.bin

install:
	avrdude -p atmega328p -c arduino -P /dev/ttyACM0 -U flash:w:$(FIRMWARE)/main.bin

clean:
	rm $(FIRMWARE)/main.elf $(FIRMWARE)/main.bin
