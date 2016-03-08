MAKEFLAGS += --no-builtin-rules

SRC = src/spi.c \
      src/usart.c \
      src/timer.c \
      src/tasks.c \
      src/ioport.c \
      src/sensors/dht22.c \

OBJ = $(patsubst %.c,%.o,$(SRC))
DEP = $(patsubst %.c,%.d,$(SRC))

# default configuration path. Can be changed by enviroment to build with
# separate configuration files.
CONFIG ?= .config

.PHONY: all
# Check if we have configuration"
ifneq ("$(wildcard $(CONFIG))","")
all: libioe.a
else
all: help $(CONFIG)
endif

$(CONFIG):
	@echo Please generate configuration first using config or menuconfig target
	@exit 1

.PHONY: oldconfig
oldconfig:
	@[ ! -f "$(CONFIG)" ] || [ ! -f "$(CONFIG).orig" ] || mv "$(CONFIG).orig" config
	@$(MAKE) -f kconfig/GNUmakefile --no-print-directory \
		TOPDIR=. SRCDIR=kconfig oldconfig
	@[ ! -f config ] || sed 's/="\(.*\)"/=\1/' config > "$(CONFIG)"
	@[ ! -f config ] || mv config "$(CONFIG).orig"
	@[ ! -f config.old ] || mv config.old "$(CONFIG).old"

.PHONY: config
config:
	@[ ! -f "$(CONFIG)" ] || [ ! -f "$(CONFIG).orig" ] || mv "$(CONFIG).orig" config
	@$(MAKE) -f kconfig/GNUmakefile --no-print-directory \
		TOPDIR=. SRCDIR=kconfig config
	@[ ! -f config ] || sed 's/="\(.*\)"/=\1/' config > "$(CONFIG)"
	@[ ! -f config ] || mv config "$(CONFIG).orig"
	@[ ! -f config.old ] || mv config.old "$(CONFIG).old"

.PHONY: menuconfig
menuconfig:
	@[ ! -f "$(CONFIG)" ] || [ ! -f "$(CONFIG).orig" ] || mv "$(CONFIG).orig" config
	@$(MAKE) -f kconfig/GNUmakefile --no-print-directory \
		TOPDIR=. SRCDIR=kconfig menuconfig
	@[ ! -f config ] || sed 's/="\(.*\)"/=\1/' config > "$(CONFIG)"
	@[ ! -f config ] || mv config "$(CONFIG).orig"
	@[ ! -f config.old ] || mv config.old "$(CONFIG).old"
# Note about this file moving madness:
# avr-ioe is using Kconfig for configuration and it is not prepared too well for
# nested projects (at least I don't know way). This unfortunately means that to
# have configuration in parent project, We have to move it every time we are
# generating it. Also upper projects can't use Kconfig for its self configuration.

# Check if we have configuration"
ifneq ("$(wildcard $(CONFIG))","")
ifeq (,$(findstring clean,$(MAKECMDGOALS)))
ifeq (,$(findstring help,$(MAKECMDGOALS)))
ifeq (,$(findstring docs,$(MAKECMDGOALS)))
ifeq (,$(findstring serve-docs,$(MAKECMDGOALS)))
ifeq (,$(findstring clean-docs,$(MAKECMDGOALS)))

include $(CONFIG)
-include $(DEP)

CFLAGS = $(shell echo $(CONFCFLAGS)) $(shell echo -DF_CPU=$(F_CPU)000L) \
		 -mmcu=$(MMCU) -Iinclude -imacros .config.h
GCC = $(GNUTOOLCHAIN_PREFIX)gcc
AR = $(GNUTOOLCHAIN_PREFIX)ar

libioe.a: $(OBJ)
	@echo " AR   $@"
	@$(AR) -crs $@ $^

$(OBJ): %.o: %.c .config.h
	@echo " CC   $@"
	@$(GCC) $(CFLAGS) -c -o $@ $<

$(DEP): %.d: %.c .config.h
	@echo " DEP  $@"
	@$(GCC) -MM -MG -MT '$*.o $@' $(CFLAGS) -c -o $@ $<

.config.h: $(CONFIG)
	@echo " GEN  .config.h"
	@grep -v "^#" $(CONFIG) | grep "CONFIG_" | sed 's/=/ /;s/^/#define /' > $@
# This is not optimal because configuration change results to complete project
# rebuild instead of only rebuilding required files.

endif
endif
endif
endif
endif
else

libioe.a:
	@echo Please generate configuration first using config or menuconfig target

endif

.PHONY: clean
clean:
	@echo " CLEAN OBJ"
	@$(RM) $(OBJ)
	@echo " CLEAN DEP"
	@$(RM) $(DEP) .config.h
	@echo " CLEAN libioe.a"
	@$(RM) libioe.a

.PHONY: docs
docs:
	@echo " DOC $@"
	@mkdocs build


.PHONY: serve-docs
serve-docs:
	@mkdocs serve

.PHONY: clean-docs
clean-docs:
	@echo " CLEAN docs"
	@$(RM) -r site

.PHONY: distclean
distclean: clean clean-docs
	@echo " CLEAN CONFIG"
	@$(RM) $(CONFIG) $(CONFIG).orig

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
