MAKEFLAGS += --no-builtin-rules
# Change PROJNAME value to your project name
# Care to not make any space at the end!
PROJNAME = template

# Add new source files to this variable
SRC = main.c

OBJ = $(patsubst %.c,%.o,$(SRC)) # This creates list of *.o files from *.c
Q ?= @ # This can be overwritten to show commands

IOEROOT = avr-ioe
CONFIG = ioeconfig

.PHONY: all
ifneq ("$(wildcard $(CONFIG))","") # Checking if configuration exists
all: $(PROJNAME).hex
	@echo Now you can flash $< to your chip.
else
all: $(CONFIG)
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
	$(Q)+$(MAKE) -C "$(IOEROOT)" clean CONFIG="$$( readlink -f $(CONFIG) )"

# Building targets are available only if configuration is generated
ifneq ("$(wildcard $(CONFIG))","")
include $(CONFIG)
# If you want change some standard CFLAGS, change them in configuration not here.
# Add here only options that should not be applied to avr-ioe also.
CFLAGS = -I"$(IOEROOT)/include" -mmcu=$(MMCU) -imacros "$(IOEROOT)/build/config.h" \
	 $(shell echo $(CCFLAGS)) $(shell echo -DF_CPU=$(F_CPU)000L)
CC = $(CHOST)gcc
AR = $(CHOST)ar
CPP = $(CHOST)cpp
OBJCOPY = $(CHOST)objcopy

$(PROJNAME).elf: $(IOEROOT)/libioe.a
$(PROJNAME).elf: $(OBJ)
	@echo " LD       $@"
	$(Q)$(CC) -Os -mmcu=$(MMCU) $^ -o $@ -L"$(IOEROOT)" -lioe

$(PROJNAME).hex: $(PROJNAME).elf
	@echo " OBJCOPY  $@"
	$(Q)$(OBJCOPY) -O ihex -R .eeprom $< $@

$(OBJ): %.o: %.c $(IOEROOT)/build/config.h
	@echo " CC       $@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

$(IOEROOT)/libioe.a: $(CONFIG)
	$(Q)+$(MAKE) -C $(IOEROOT) libioe.a CONFIG="$$( readlink -f $(CONFIG) )"
$(IOEROOT)/build/config.h: $(CONFIG)
	$(Q)+$(MAKE) -C $(IOEROOT) build/config.h CONFIG="$$( readlink -f $(CONFIG) )"
endif

TOOL_PATH="$(IOEROOT)/tools"
include $(IOEROOT)/tools/kconfig.mk
