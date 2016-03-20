MAKEFLAGS += --no-builtin-rules
# Change PROJNAME value to you project name
# Care to not make any space at the end!
PROJNAME = template

# Add new source files to this variable
SRC = main.c

OBJ = $(patsubst %.c,%.o,$(SRC)) # This creates list of *.o files from *.c
Q ?= @ # This can be overwritten to show commands

.PHONY: all
ifneq ("$(wildcard ioeconfig)","") # Checking if configuration exists
all: $(PROJNAME).hex
	@echo Now you can flash $< to your chip.
else
all: help .config
endif

# Edit here help like you ever want
.PHONY: help
help:
	@echo  "This is avr-ioe template project"
	@echo  " all         - Build project"
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
	$(Q)$(MAKE) -C avr-ioe clean CONFIG="$$( readlink -f ioeconfig )"

# Building targets are available only if configuration is generated
ifneq ("$(wildcard ioeconfig)","")
include ioeconfig
# If you want change some standard CFLAGS, change them in configuration not here.
# Add here only options that should not be applied to avr-ioe also.
CFLAGS = -Iavr-ioe/include -mmcu=$(MMCU) -imacros avr-ioe/build/config.h \
	 $(shell echo $(CONFCFLAGS)) $(shell echo -DF_CPU=$(F_CPU)000L)

$(PROJNAME).elf: avr-ioe/libioe.a
$(PROJNAME).elf: $(OBJ)
	@echo " LD       $@"
	$(Q)avr-gcc -Os -mmcu=$(MMCU) $^ -o $@ -Lavr-ioe -lioe

$(PROJNAME).hex: $(PROJNAME).elf
	@echo " OBJCOPY  $@"
	$(Q)avr-objcopy -O ihex -R .eeprom $< $@

$(OBJ): %.o: %.c avr-ioe/build/config.h
	@echo " CC       $@"
	$(Q)avr-gcc $(CFLAGS) -c -o $@ $<

avr-ioe/libioe.a: ioeconfig
	$(Q)$(MAKE) -C avr-ioe libioe.a CONFIG="$$( readlink -f ioeconfig )"
avr-ioe/build/config.h: ioeconfig
	$(Q)$(MAKE) -C avr-ioe build/config.h CONFIG="$$( readlink -f ioeconfig )"
endif

.config:
	@echo Please generate configuration first using config or menuconfig target
	@exit 1

.PHONY: config
config:
	$(Q)$(MAKE) -C avr-ioe menuconfig CONFIG="$$( readlink -f ioeconfig )"

.PHONY: menuconfig
menuconfig:
	$(Q)$(MAKE) -C avr-ioe menuconfig CONFIG="$$( readlink -f ioeconfig )"
