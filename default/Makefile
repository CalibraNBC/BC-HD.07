###############################################################################
# Makefile for the project BC1
###############################################################################

## General Flags
PROJECT = BC1
MCU = atmega644p
TARGET = BC1.elf
CC = avr-gcc

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99                                      -DF_CPU=16000000UL -Os -fsigned-char
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=BC1.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = main.o int_ee.o i2c.o accelerometer.o keys.o delay.o menu.o meranie_spotreby.o meranie_vzdialenosti_rychlosti.o meranie_teploty.o meranie_nadrze.o beep.o meranie_baterky.o meranie_podsvietenia.o lcd_S65_LS020.o font_8_12.o mnu_bc.o mnu_max_hodnoty.o mnu_nastavenia.o input_int.o mnu_pretazenie.o zrychlenie.o verzia.o vystraha.o eeprom_24Cxx.o logo.o reset.o mnu_motor.o mnu_develop.o input_char.o mnu_400m.o bw_picture.o mnu_stopky.o nadrz.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) BC1.hex BC1.eep BC1.lss size

## Compile
main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

int_ee.o: ../int_ee.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

i2c.o: ../i2c.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

accelerometer.o: ../accelerometer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

keys.o: ../keys.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

delay.o: ../delay.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

menu.o: ../menu.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

meranie_spotreby.o: ../meranie_spotreby.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

meranie_vzdialenosti_rychlosti.o: ../meranie_vzdialenosti_rychlosti.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

meranie_teploty.o: ../meranie_teploty.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

meranie_nadrze.o: ../meranie_nadrze.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

beep.o: ../beep.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

meranie_baterky.o: ../meranie_baterky.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

meranie_podsvietenia.o: ../meranie_podsvietenia.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

lcd_S65_LS020.o: ../lcd_S65_LS020.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

font_8_12.o: ../font_8_12.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

mnu_bc.o: ../mnu_bc.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

mnu_max_hodnoty.o: ../mnu_max_hodnoty.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

mnu_nastavenia.o: ../mnu_nastavenia.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

input_int.o: ../input_int.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

mnu_pretazenie.o: ../mnu_pretazenie.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

zrychlenie.o: ../zrychlenie.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

verzia.o: ../verzia.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

vystraha.o: ../vystraha.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

eeprom_24Cxx.o: ../eeprom_24Cxx.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

logo.o: ../logo.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

reset.o: ../reset.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

mnu_motor.o: ../mnu_motor.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

mnu_develop.o: ../mnu_develop.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

input_char.o: ../input_char.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

mnu_400m.o: ../mnu_400m.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

bw_picture.o: ../bw_picture.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

mnu_stopky.o: ../mnu_stopky.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

nadrz.o: ../nadrz.c
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
	-rm -rf $(OBJECTS) BC1.elf dep/* BC1.hex BC1.eep BC1.lss BC1.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

