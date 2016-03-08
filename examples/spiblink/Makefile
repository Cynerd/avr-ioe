MAKEFLAGS += --no-builtin-rules
PROJNAME = spiblink

MSRC = master.c
SSRC = slave.c

MOBJ = $(patsubst %.c,%.o,$(MSRC))
SOBJ = $(patsubst %.c,%.o,$(SSRC))

.PHONY: all
ifneq ("$(wildcard config)","") # Checking if configuration exists
all: master.hex slave.hex
	@echo Now you can flash $^ to your chips.
else
all: help
endif

# Edit here help like you ever want
.PHONY: help
help:
	@echo  "AVR-IOE USART echo example"
	@echo  " all         - Build example"
	@echo  " config      - Start configuration program"
	@echo  " menuconfig  - NCurses based configuration program"
	@echo  " help        - Prints this text"
	@echo  " clean       - Removing all object files generated from source files"

.PHONY: clean
clean:
	@echo " CLEAN OBJ"
	@$(RM) $(MOBJ) $(SOBJ)
	@echo " CLEAN master and slave *.hex, *.elf"
	@$(RM) master.elf master.hex
	@$(RM) slave.elf slave.hex
	@$(MAKE) -C ../.. clean

# Building targets are available only if configuration is generated
ifneq ("$(wildcard config)","")
-include config
# If you want change some standard CFLAGS, change them in configuration not here.
# Add here only options that should not be applied to avr-ioe also.
CFLAGS = -I../../include -mmcu=$(MMCU) -imacros ../../.config.h \
	 $(shell echo $(CONFCFLAGS)) $(shell echo -DF_CPU=$(F_CPU)000L)

master.elf slave.elf: %.elf: ../../libioe.a %.o
	@echo " LD       $@"
	@avr-gcc -Os -mmcu=$(MMCU) $^ -o $@ -L../.. -lioe

master.hex slave.hex: %.hex: %.elf
	@echo " OBJCOPY  $@"
	@avr-objcopy -O ihex -R .eeprom $< $@

$(MOBJ) $(SOBJ): %.o: %.c ../../libioe.a
	@echo " CC       $@"
	@avr-gcc $(CFLAGS) -c -o $@ $<

../../libioe.a: config
	@CONFIG=$$(readlink -f config) $(MAKE) -C ../.. libioe.a
endif

config:
	@CONFIG=$$(readlink -f config) $(MAKE) -C ../.. config

.PHONY: menuconfig
menuconfig:
	@CONFIG=$$(readlink -f config) $(MAKE) -C ../.. menuconfig
