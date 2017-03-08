# vim:ts=4:sw=4:sts=4:noexpandtab
MAKEFLAGS += --no-builtin-rules

# Default output path. Can be changed by enviroment to compile to different folder
# than default.
O ?= .
# This variable can be overwritten to show executed commands
Q ?= @
# This variable can be used if you want to have configuration file for you project
# in different location than default. You should use absolute path.
CONFIG ?= $(O)/.config

.PHONY: all
# Check if we have configuration"
ifneq ("$(wildcard $(CONFIG))","")
all: libioe.a
else
all: help $(CONFIG)
endif

ifneq ("$(wildcard $(CONFIG))","") # Check if we have configuration
ifeq (,$(filter clean help docs serve-docs clean-docs config oldconfig \
	allyesconfig menuconfig, \
	$(MAKECMDGOALS))) # Ignore build targets if goal is not building

include $(CONFIG) # include configuration
include src/sources.mk

OBJ = $(patsubst %.c,$(O)/build/%.o,$(SRC))
DEP = $(patsubst %.c,$(O)/build/%.d,$(SRC))

-include $(DEP)

CFLAGS = $(shell echo $(CCFLAGS)) $(shell echo -DF_CPU=$(F_CPU)000L) \
		 -mmcu=$(MMCU) -Iinclude -imacros $(O)/build/config.h
CC = $(CHOST)gcc
AR = $(CHOST)ar
CPP = $(CHOST)cpp

$(O)/libioe.a: $(OBJ)
	@echo " AR   $@"
	$(Q)$(AR) -crs $@ $^

$(OBJ): $(O)/build/%.o: src/%.c
	@mkdir -p "$(@D)"
	@echo " CC   $@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

$(DEP): $(O)/build/%.d: src/%.c $(O)/build/config.h
	@mkdir -p "$(@D)"
	@echo " DEP  $@"
	$(Q)$(CPP) -MM -MG -MT '$(O)/build/$*.o $@' $(CFLAGS) -o $@ $<

$(O)/build/config.h: $(CONFIG)
	@mkdir -p "$(@D)"
	@echo " GEN  $@"
	$(Q)grep -v "^#" $(CONFIG) | grep "CONFIG_" | sed -e 's/="\(.*\)"/=\1/;s/=/ /;s/^/#define /' > $@

else
$(O)/libioe.a:
	@echo Please execute non-building target separate from building ones
	@exit 1
endif
else
$(O)/libioe.a: $(CONFIG) # Print error message for missing config file
endif

.PHONY: clean
clean:
	@echo " CLEAN BUILD"
	$(Q)$(RM) -r $(O)/build
	@echo " CLEAN libioe.a"
	$(Q)$(RM) $(O)/libioe.a

.PHONY: docs
docs:
	@echo " DOC $@"
	$(Q)mkdocs build


.PHONY: serve-docs
serve-docs:
	$(Q)mkdocs serve

.PHONY: clean-docs
clean-docs:
	@echo " CLEAN docs"
	$(Q)$(RM) -r html

.PHONY: proper
proper: clean clean-docs
	@echo " CLEAN CONFIG"
	$(Q)$(RM) $(CONFIG) $(CONFIG).orig .config.cmd

.PHONY: help
help:
	@echo  "all/libioe.a - Build library"
	@echo  "config       - Start configuration program"
	@echo  "menuconfig   - NCurses based configuration program (Kconfig)"
	@echo  "docs         - Build documentation"
	@echo  "server-docs  - Start temporally http server with documentation"
	@echo  "help         - Prints this text"
	@echo  "clean        - Removing all object files generated from source files"
	@echo  "clean-docs   - Remove generated documentation"
	@echo  "proper       - Cleans everything including configuration"

TOOL_PATH=tools
IOEROOT=.
include tools/kconfig.mk
