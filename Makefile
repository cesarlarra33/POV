# Variables du Makfile 
CC = avr-gcc 
CHIP = atmega328p
F_CPU = 13000000UL
CFLAGS = -mmcu=$(CHIP) -Os -DF_CPU=$(F_CPU) -Wall
SRC_DIR = src
BUILD = build
TARGET = MBI5024

##################################################
# PIPELINE DE COMPILATION :
# compile .c en .o => .c.o => lie les .o en un .elf => convertit le .elf en .bin
##################################################

# trouve tous les .c dans src/ 
SRCS = $(wildcard $(SRC_DIR)/*.c)
# transforme les .c en .o dans build/ => va voir la règle de compilation plus bas
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD)/%.o)

# regle quand tu fais juste make, doit finir avec des build/*.bin, va aller 
# voir les dépendances des build/*.bin
all: $(BUILD)/$(TARGET).bin

$(BUILD):
	mkdir -p $(BUILD)

# build/*.o nécessite de compiler les src/*.c et d'avoir un build/ 
$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# build/*.elf nécessite de lier les build/*.o
$(BUILD)/$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# build/*.bin nécessite un build/*.elf
$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	avr-objcopy -O binary $< $@

# flash le code sur la carte
install: $(BUILD)/$(TARGET).bin
	avrdude -p $(CHIP) -c usbasp -U flash:w:$<

# réinstalle le code d'origine
backup:
	avrdude -p $(CHIP) -c usbasp -U flash:r:backup1.hex:i

clean:
	rm -rf $(BUILD)