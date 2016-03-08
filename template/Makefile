MAKEFLAGS += --no-builtin-rules
# Change PROJNAME value to you project name
# Care to not make any space at the end!
PROJNAME = template

# Add new source files to this variable
SRC = main.c

OBJ = $(patsubst %.c,%.o,$(SRC)) # This creates list of *.o files from *.c

.PHONY: all
ifneq ("$(wildcard .config)","") # Checking if configuration exists
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
	@$(RM) $(OBJ)
	@echo " CLEAN $(PROJNAME).elf $(PROJNAME).hex"
	@$(RM) $(PROJNAME).elf $(PROJNAME).hex
	@$(MAKE) -C avr-ioe clean

# Building targets are available only if configuration is generated
ifneq ("$(wildcard .config)","")
-include .config
# If you want change some standard CFLAGS, change them in configuration not here.
# Add here only options that should not be applied to avr-ioe also.
CFLAGS = -Iavr-ioe/include -mmcu=$(MMCU) -imacros avr-ioe/.config.h \
	 $(shell echo $(CONFCFLAGS)) $(shell echo -DF_CPU=$(F_CPU)000L)

$(PROJNAME).elf: avr-ioe/libioe.a
$(PROJNAME).elf: $(OBJ)
	@echo " LD       $@"
	@avr-gcc -Os -mmcu=$(MMCU) $^ -o $@ -Lavr-ioe -lioe

$(PROJNAME).hex: $(PROJNAME).elf
	@echo " OBJCOPY  $@"
	@avr-objcopy -O ihex -R .eeprom $< $@

$(OBJ): %.o: %.c avr-ioe/libioe.a
	@echo " CC       $@"
	@avr-gcc $(CFLAGS) -c -o $@ $<

avr-ioe/libioe.a: .config
	@CONFIG=$$(readlink -f .config) $(MAKE) -C avr-ioe libioe.a
endif

.config:
	@echo Please generate configuration first using config or menuconfig target
	@exit 1

.PHONY: config
config:
	@CONFIG=$$(readlink -f .config) $(MAKE) -C avr-ioe menuconfig

.PHONY: menuconfig
menuconfig:
	@CONFIG=$$(readlink -f .config) $(MAKE) -C avr-ioe menuconfig
