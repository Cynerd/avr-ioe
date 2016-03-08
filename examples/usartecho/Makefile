MAKEFLAGS += --no-builtin-rules
PROJNAME = usartecho

SRC = echo.c

OBJ = $(patsubst %.c,%.o,$(SRC)) # This creates list of *.o files from *.c

.PHONY: all
ifneq ("$(wildcard config)","") # Checking if configuration exists
all: $(PROJNAME).hex
	@echo Now you can flash $< to your chip.
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
	@$(RM) $(OBJ)
	@echo " CLEAN $(PROJNAME).elf $(PROJNAME).hex"
	@$(RM) $(PROJNAME).elf $(PROJNAME).hex
	@$(MAKE) -C ../.. clean

# Building targets are available only if configuration is generated
ifneq ("$(wildcard config)","")
-include config
# If you want change some standard CFLAGS, change them in configuration not here.
# Add here only options that should not be applied to avr-ioe also.
CFLAGS = -I../../include -mmcu=$(MMCU) -imacros ../../.config.h \
	 $(shell echo $(CONFCFLAGS)) $(shell echo -DF_CPU=$(F_CPU)000L)

$(PROJNAME).elf: ../../libioe.a
$(PROJNAME).elf: $(OBJ)
	@echo " LD       $@"
	@avr-gcc -Os -mmcu=$(MMCU) $^ -o $@ -L../.. -lioe

$(PROJNAME).hex: $(PROJNAME).elf
	@echo " OBJCOPY  $@"
	@avr-objcopy -O ihex -R .eeprom $< $@

$(OBJ): %.o: %.c ../../libioe.a
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
