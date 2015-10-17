ifndef IOE_PREFIX
	IOE_PREFIX = .
endif

IOE_SRC = $(IOE_PREFIX)/src/spi.c \
		  $(IOE_PREFIX)/src/usart.c \
		  $(IOE_PREFIX)/src/timer.c \
		  $(IOE_PREFIX)/src/tasks.c \
		  $(IOE_PREFIX)/src/pcint.c \
		  $(IOE_PREFIX)/src/sensor_dht22.c \

IOE_OBJ = $(patsubst %.c,%.o,$(IOE_SRC))
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
IOE_CFLAGS ?= -Os -ffunction-sections -fdata-sections -fshort-enums -Wall \
			  -DF_CPU=$(F_CPU) -mmcu=$(MMCU)
IOE_GCC ?= avr-gcc

ifndef IOE_SHORTOUTPUT
$(IOE_OBJ): %.o: %.c
	$(IOE_GCC) $(IOE_CFLAGS) -c -o $@ $<

$(IOE_DEP): %.d: %.c
	$(IOE_GCC) -MM -MG -MT '$*.o $@' $(IOE_CFLAGS) -c -o $@ $<

.PHONY: ioeclean
ioeclean::
	$(RM) $(IOE_OBJ)
	$(RM) $(IOE_DEP)
else
$(IOE_OBJ): %.o: %.c
	@echo " IOE CC   $@"
	@$(IOE_GCC) $(IOE_CFLAGS) -c -o $@ $<

$(IOE_DEP): %.d: %.c
	@echo " IOE DEP  $@"
	@$(IOE_GCC) -MM -MG -MT '$*.o $@' $(IOE_CFLAGS) -c -o $@ $<

.PHONY: ioeclean
ioeclean::
	@echo " IOE CLEAN OBJ"
	@$(RM) $(IOE_OBJ)
	@echo " IOE CLEAN DEP"
	@$(RM) $(IOE_DEP)
endif

endif
