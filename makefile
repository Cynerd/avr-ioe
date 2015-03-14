.PHONY: all help clean

include files.mk

all:
	$(error This is not library, please include "files.mk" to your project makefile. For more informations refer to README.md)

help:
	@echo This makefile only implements these targets:
	@echo  help  - prints this text
	@echo  clean - removing all object files generated from source files

clean:
	$(RM) $(IOE_SPI_OBJ)
	$(RM) $(IOE_SPI_USI_OBJ)
