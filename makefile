.PHONY: all help clean

IOE_ONLYPATHS = y
include avr-ioe.mk

all:
	$(error This is not library, please include "avr-ioe.mk" to your project makefile. For more informations refer to README.md)

help:
	@echo This makefile only implements these targets:
	@echo  help       - prints this text
	@echo  clean      - removing all object files generated from source files

clean:
	$(RM) $(IOE_OBJ)
	$(RM) $(IOE_DEP)
