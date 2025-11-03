CC = avr-gcc
CFLAGS = -mmcu=atmega328p -Os -DF_CPU=16000000UL
SRC_DIR = multi
BUILD = build
TARGET = main

all: $(BUILD)/$(TARGET).bin

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/$(TARGET).elf: $(SRC_DIR)/$(TARGET).c | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	avr-objcopy -O binary $< $@

install: $(BUILD)/$(TARGET).bin
	avrdude -p atmega328p -c arduino -P /dev/tty.usbmodem1201 -U flash:w:$<

clean:
	rm -rf $(BUILD)
