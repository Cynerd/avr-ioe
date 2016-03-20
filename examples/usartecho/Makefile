MAKEFLAGS += --no-builtin-rules
PROJNAME = usartecho

SRC = echo.c

OBJ = $(patsubst %.c,%.o,$(SRC)) # This creates list of *.o files from *.c
Q ?= @ # This can be overwritten to show commands

.PHONY: all
ifneq ("$(wildcard .config)","") # Checking if configuration exists
all: $(PROJNAME).hex
	@echo Now you can flash $< to your chip.
else
all: .config
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
	$(Q)$(RM) $(OBJ)
	@echo " CLEAN $(PROJNAME).elf $(PROJNAME).hex"
	$(Q)$(RM) $(PROJNAME).elf $(PROJNAME).hex
	$(Q)$(MAKE) -C ../.. clean O=examples/$(PROJNAME)

# Building targets are available only if configuration is generated
ifneq ("$(wildcard .config)","")
-include .config
# If you want change some standard CFLAGS, change them in configuration not here.
# Add here only options that should not be applied to avr-ioe also.
CFLAGS = -I../../include -mmcu=$(MMCU) -imacros build/config.h \
	 $(shell echo $(CONFCFLAGS)) $(shell echo -DF_CPU=$(F_CPU)000L)

$(PROJNAME).elf: libioe.a
$(PROJNAME).elf: $(OBJ)
	@echo " LD       $@"
	@avr-gcc -Os -mmcu=$(MMCU) $(filter %.o,$^) -o $@ -L. -lioe

$(PROJNAME).hex: $(PROJNAME).elf
	@echo " OBJCOPY  $@"
	$(Q)avr-objcopy -O ihex -R .eeprom $< $@

$(OBJ): %.o: %.c libioe.a
	@echo " CC       $@"
	$(Q)avr-gcc $(CFLAGS) -c -o $@ $<

libioe.a: .config
	$(Q)$(MAKE) -C ../.. examples/$(PROJNAME)/libioe.a O=examples/$(PROJNAME)
endif

.config:
	@echo Configuration for this example is missing. Probably deleted...
	@exit 1

config:
	$(Q)$(MAKE) -C ../.. config O=examples/$(PROJNAME)

.PHONY: menuconfig
menuconfig:
	$(Q)$(MAKE) -C ../.. menuconfig O=examples/$(PROJNAME)
