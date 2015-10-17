MAKEFLAGS += --no-builtin-rules

MMCU = atmega328p
F_CPU = 16000000L
IOE_PREFIX = ../..
IOE_SHORTOUTPUT=y
IOE_CFLAGS = -Os -ffunction-sections -fdata-sections -fshort-enums -Wall \
			 -DF_CPU=$(F_CPU) -mmcu=$(MMCU) \
			 -DCONFIG_IOE_USART \
			 -DCONFIG_IOE_USART_OUTBUFFER_SIZE=64 \
			 -DCONFIG_IOE_USART_OUTBUFFER_MODE=0 \
			 -DCONFIG_IOE_USART_OUTFILE \
			 -DCONFIG_IOE_USART_BAUD=115200 \
			 -DCONFIG_IOE_USART_PARITY=USART_PARITY_NONE \
			 -DCONFIG_IOE_USART_STOPBIT=USART_STOPBIT_SINGLE \
			 -DCONFIG_IOE_USART_DATABITS=8 \
			 -DCONFIG_IOE_TIMERS \
			 -DCONFIG_IOE_SENSOR_DHT22

all: dht22.hex
	@echo Now you can flash dht22.hex to your chip.

clean: ioeclean
	$(RM) dht22.o
	$(RM) dht22.elf dht22.hex

include ../../avr-ioe.mk

dht22.elf: %.elf: $(IOE_OBJ) dht22.o
	@echo " LD       $@"
	@avr-gcc -Os -mmcu=$(MMCU) $^ -o $@

dht22.hex: %.hex: %.elf
	@echo " OBJCOPY  $@"
	@avr-objcopy -O ihex -R .eeprom $< $@

dht22.o: %.o: %.c
	@echo " CC       $@"
	@avr-gcc $(IOE_CFLAGS) -c -o $@ $<
