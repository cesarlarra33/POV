FIRMWARE := USART
CC := avr-gcc
OBJCOPY := avr-objcopy
AVRDUDE := avrdude
CFLAGS := -mmcu=atmega328p -DF_CPU=16000000UL -Os -Wall

all: $(FIRMWARE)/main.elf $(FIRMWARE)/main.bin

$(FIRMWARE)/main.elf: $(FIRMWARE)/main.c
	$(CC) $(CFLAGS) -o $@ $<

$(FIRMWARE)/main.bin: $(FIRMWARE)/main.elf
	$(OBJCOPY) -O binary -j .text -j .data $< $@

install: $(FIRMWARE)/main.bin
	$(AVRDUDE) -p atmega328p -c usbasp -U flash:w:$<

clean:
	rm -f $(FIRMWARE)/main.elf $(FIRMWARE)/main.bin