MAKEFLAGS += --no-builtin-rules

MMCU = atmega328p
F_CPU = 16000000L
IOE_PREFIX = ../..
IOE_CFLAGS = -Os -ffunction-sections -fdata-sections -fshort-enums -Wall -g \
			 -DCONFIG_IOE_USART_OUTBUFFER_SIZE=64 \
			 -DCONFIG_IOE_USART_OUTBUFFER_MODE=0

all: usart.hex
	@echo Flash usart.hex to chip

install: usart.hex
	# TODO

clean: ioeclean
	$(RM) echo.o
	$(RM) usart.elf usart.hex

include ../../avr-ioe.mk

usart.elf: %.elf: $(IOE_OBJ_USART) echo.o
	avr-gcc -mmcu=$(MMCU) $^ -o $@

usart.hex: %.hex: %.elf
	avr-objcopy -O ihex -R .eeprom $< $@

echo.o: %.o: %.c
	avr-gcc $(IOE_CFLAGS) -c -o $@ $<
