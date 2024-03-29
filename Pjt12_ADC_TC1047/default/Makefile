###############################################################################
# Makefile for the project Pjt12_ADC_TC1047
###############################################################################

## General Flags
PROJECT = Pjt12_ADC_TC1047
MCU = atmega2560
TARGET = Pjt12_ADC_TC1047.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99   -DF_CPU=7372800UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=Pjt12_ADC_TC1047.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = app.o link.o main.o prime.o queue.o timer_task.o uart.o ADC.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) Pjt12_ADC_TC1047.hex Pjt12_ADC_TC1047.eep Pjt12_ADC_TC1047.lss size

## Compile
app.o: ../app.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

link.o: ../link.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

prime.o: ../prime.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

queue.o: ../queue.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

timer_task.o: ../timer_task.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart.o: ../uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ADC.o: ../ADC.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) Pjt12_ADC_TC1047.elf dep/* Pjt12_ADC_TC1047.hex Pjt12_ADC_TC1047.eep Pjt12_ADC_TC1047.lss Pjt12_ADC_TC1047.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

