ifndef IOE_PREFIX
	IOE_PREFIX = .
endif

IOE_SRC_SPI = $(IOE_PREFIX)/src/spi.c
IOE_SRC_USART = $(IOE_PREFIX)/src/usart.c
IOE_SRC = $(IOE_SRC_SPI) $(IOE_SRC_USART)

IOE_OBJ_SPI = $(patsubst %.c,%.o,$(IOE_SRC_SPI))
IOE_OBJ_USART = $(patsubst %.c,%.o,$(IOE_SRC_USART))
IOE_OBJ = $(patsubst %.c,%.o,$(IOE_SRC))

IOE_DEP_SPI = $(patsubst %.c,%.d,$(IOE_SRC_SPI))
IOE_DEP_USART = $(patsubst %.c,%.d,$(IOE_SRC_USART))
IOE_DEP = $(patsubst %.c,%.d,$(IOE_SRC))


ifndef IOE_ONLYPATHS # Following section can be suppressed by defining this variable

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),help)
-include $(IOE_DEP)
endif
endif

ifndef F_CPU
	$(error Please define F_CPU variable in makefile before including avr-ioe.mk)
endif
ifndef MMCU
	$(error Pleade define MMCU variable in makefile before including avr-ioe.mk)
endif
IOE_CFLAGS ?= -Os -ffunction-sections -fdata-sections -fshort-enums -Wall
IOE_CFLAGS += -DF_CPU=$(F_CPU) -mmcu=$(MMCU)
IOE_GCC ?= avr-gcc

$(IOE_OBJ): %.o: %.c
	$(IOE_GCC) $(IOE_CFLAGS) -c -o $@ $<

$(IOE_DEP): %.d: %.c
	$(IOE_GCC) -MM -MG -MT '$*.o $@' $(IOE_CFLAGS) -c -o $@ $<

.PHONY: ioeclean
ioeclean:
	$(RM) $(IOE_OBJ)
	$(RM) $(IOE_DEP)

endif
