MAKEFLAGS += --no-builtin-rules

MMCU = atmega328p
F_CPU = 16000000L
IOE_PREFIX = ../..
IOE_CFLAGS ?= -Os -ffunction-sections -fdata-sections -fshort-enums -g -Wall \
			  -DF_CPU=$(F_CPU) -mmcu=$(MMCU)

.PHONY: all
all:  master.hex slave.hex
	@echo
	@echo Flash master.hex and slave.hex to two chips and... TODO

.PHONY: all
clean: ioeclean
	$(RM) master.o slave.o
	$(RM) master.elf master.hex
	$(RM) slave.elf slave.hex

include ../../avr-ioe.mk

master.elf: master.o
slave.elf: slave.o
master.elf slave.elf: %.elf: $(IOE_OBJ_SPI)
	avr-gcc -Os -mmcu=$(MMCU) $^ -o $@

master.hex slave.hex: %.hex: %.elf
	 avr-objcopy -O ihex -R .eeprom $< $@

master.o slave.o: %.o: %.c
	avr-gcc $(IOE_CFLAGS) -c -o $@ $<
