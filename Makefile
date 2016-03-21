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

### Source files list ###########################
SRC = base.c
ifeq (y,$(CONFIG_IOPORTS))
SRC += ioport.c
endif
ifeq (y,$(CONFIG_SPI))
SRC += spi.c
endif
ifeq (y,$(CONFIG_USART))
SRC += usart.c
endif
### End of source files list ####################

OBJ = $(patsubst %.c,$(O)/build/%.o,$(SRC))
DEP = $(patsubst %.c,$(O)/build/%.d,$(SRC))

-include $(DEP)

CFLAGS = $(shell echo $(CONFCFLAGS)) $(shell echo -DF_CPU=$(F_CPU)000L) \
		 -mmcu=$(MMCU) -Iinclude -imacros $(O)/build/config.h
GCC = $(GNUTOOLCHAIN_PREFIX)gcc
AR = $(GNUTOOLCHAIN_PREFIX)ar
CPP = $(GNUTOOLCHAIN_PREFIX)cpp

$(O)/libioe.a: $(OBJ)
	@echo " AR   $@"
	$(Q)$(AR) -crs $@ $^

$(OBJ): $(O)/build/%.o: src/%.c
	$(Q)mkdir -p "$(@D)"
	@echo " CC   $@"
	$(Q)$(GCC) $(CFLAGS) -c -o $@ $<

$(DEP): $(O)/build/%.d: src/%.c $(O)/build/config.h
	$(Q)mkdir -p "$(@D)"
	@echo " DEP  $@"
	$(Q)$(CPP) -MM -MG -MT '$(O)/build/$*.o $@' $(CFLAGS) -o $@ $<

$(O)/build/config.h: $(CONFIG)
	$(Q)mkdir -p "$(@D)"
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
	$(Q)$(RM) -r site

.PHONY: distclean
distclean: clean clean-docs
	@echo " CLEAN CONFIG"
	$(Q)$(RM) $(CONFIG) $(CONFIG).orig

.PHONY: help
help:
	@echo  "all/libioe.a - Build library"
	@echo  "config       - Start configuration program"
	@echo  "menuconfig   - NCurses based configuration program"
	@echo  "docs         - Build documentation"
	@echo  "server-docs  - Start temporally http server with documentation"
	@echo  "help         - Prints this text"
	@echo  "clean        - Removing all object files generated from source files"
	@echo  "clean-docs   - Remove generated documentation"

$(CONFIG):
	@echo Please generate configuration first using config or menuconfig target
	@exit 1

# We don't wont pass any variable to Kconfig. This is workaround for that.
MAKEOVERRIDES =

callconfig = $(Q)\
	[ ! -f "$(CONFIG)" ] || mv "$(CONFIG)" config; \
	IOEROOT=. $(MAKE) -f tools/kconfig/GNUmakefile --no-print-directory \
		TOPDIR=. SRCDIR=tools/kconfig $(1); \
	[ ! -f config ] || mv config "$(CONFIG)"; \
	[ ! -f config.old ] || mv config.old "$(CONFIG).old"
# Note about this file moving madness:
# avr-ioe is using Kconfig for configuration and it is not prepared too well for
# nested projects (at least I don't know way). This unfortunately means that to
# have configuration in parent project, We have to move it every time we are
# generating it. Also upper projects can't use Kconfig for its self configuration.

.PHONY: oldconfig
oldconfig:
	$(call callconfig, oldconfig)

.PHONY: config
config:
	$(call callconfig, config)

.PHONY: menuconfig
menuconfig:
	$(call callconfig, menuconfig)

.PHONY: allyesconfig
allyesconfig:
	$(call callconfig, allyesconfig)
