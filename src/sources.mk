# vim:ts=4:sw=4:sts=4:noexpandtab

# Essential sources
SRC = base.c

# IO ports
ifeq (y,$(CONFIG_IOPORTS))
SRC += ioport.c
endif

# SPI
ifeq (y,$(CONFIG_SPI))
SRC += spi.c
endif

# UART
ifeq (y,$(CONFIG_USART))
SRC += usart.c
endif
