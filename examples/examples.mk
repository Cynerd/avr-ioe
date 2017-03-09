# vim:ts=4:sw=4:sts=4:noexpandtab
MAKEFLAGS += --no-builtin-rules
# Note this file is included to Makefiles in lower directories so all paths here
# are like thy would be from lower directory.

ifndef IOEROOT
$(error Before including examples.mk define IOEROOT)
endif
ifndef EXAMPLE_NAME
$(error Before including examples.mk define EXAMPLE_NAME)
endif
ifndef SRC
$(error Before including examples.mk define SRC)
endif
EXAMPLE_PATH ?= $(EXAMPLE_NAME)

OBJ = $(patsubst %.c,%.o,$(SRC)) # This creates list of *.o files from *.c
Q ?= @ # This can be overwritten to show commands

CONFIG = .config

.PHONY: all
ifneq ("$(wildcard $(CONFIG))","") # Checking if configuration exists
all: $(EXAMPLE_NAME).hex
	@echo Now you can flash $< to your chip.
else
all: $(CONFIG)
endif

# Edit here help like you ever want
.PHONY: help
help:
	@echo  "AVR-IOE $(EXAMPLE_NAME) example"
	@echo  " all         - Build example"
	@echo  " config      - Start configuration program"
	@echo  " menuconfig  - NCurses based configuration program"
	@echo  " help        - Prints this text"
	@echo  " clean       - Removing all object files generated from source files"

.PHONY: clean
clean:
	@echo " CLEAN OBJ"
	$(Q)$(RM) $(OBJ)
	@echo " CLEAN $(EXAMPLE_NAME).elf $(EXAMPLE_NAME).hex"
	$(Q)$(RM) $(EXAMPLE_NAME).elf $(EXAMPLE_NAME).hex
	$(Q)$(MAKE) -C "$(IOEROOT)" clean O=examples/$(EXAMPLE_PATH)

# Building targets are available only if configuration is generated
ifneq ("$(wildcard $(CONFIG))","")
-include $(CONFIG)
# If you want change some standard CFLAGS, change them in configuration not here.
# Add here only options that should not be applied to avr-ioe also.
CFLAGS = -I"$(IOEROOT)/include" -mmcu=$(MMCU) -imacros build/config.h \
	 $(shell echo $(CCFLAGS)) $(shell echo -DF_CPU=$(F_CPU)000L)
CC = $(CHOST)gcc
OBJCOPY = $(CHOST)objcopy

$(EXAMPLE_NAME).elf: libioe.a
$(EXAMPLE_NAME).elf: $(OBJ)
	@echo " LD       $@"
	$(Q)$(CC) -Os -mmcu=$(MMCU) $(filter %.o,$^) -o $@ -L. -lioe

$(EXAMPLE_NAME).hex: $(EXAMPLE_NAME).elf
	@echo " OBJCOPY  $@"
	$(Q)$(OBJCOPY) -O ihex -R .eeprom $< $@

$(OBJ): %.o: %.c libioe.a
	@echo " CC       $@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

libioe.a: $(CONFIG)
	$(Q)$(MAKE) -C "$(IOEROOT)" examples/$(EXAMPLE_PATH)/libioe.a O=examples/$(EXAMPLE_PATH)
endif

TOOL_PATH="$(IOEROOT)/tools"
include $(IOEROOT)/tools/kconfig.mk
