MAKEFLAGS += --no-builtin-rules

MMCU = atmega328p
F_CPU = 16000000L
IOE_PREFIX = ../..
IOE_CFLAGS = -Os -ffunction-sections -fdata-sections -fshort-enums -Wall \
			 -DCONFIG_IOE_USART_OUTBUFFER_SIZE=64 \
			 -DCONFIG_IOE_USART_OUTBUFFER_MODE=0 \
			 -DCONFIG_IOE_USART_BAUD=115200 \
			 -DCONFIG_IOE_USART_PARITY=USART_PARITY_NONE \
			 -DCONFIG_IOE_USART_STOPBIT=USART_STOPBIT_SINGLE \
			 -DCONFIG_IOE_USART_DATABITS=8

all: usart.hex
	@echo Now you can flash usart.hex to your chip.

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
