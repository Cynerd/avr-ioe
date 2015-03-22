ifndef IOE_PREFIX
	IOE_PREFIX = .
endif

include charLCD/files.mk
include dht22/files.mk
include nrf24l01p/files.mk

IOE_SPI_SRC = $(IOE_PREFIX)/src/spi.c
IOE_SPI_USI_SRC = $(IOE_PREFIX)/src/spi_usi.c
IOE_SPI_USART_SRC = $(IOE_PREFIX)/src/spi_usart.c

IOE_SPI_OBJ = $(patsubst %.c,%.o,$(IOE_SPI_SRC))
IOE_SPI_USI_OBJ = $(patsubst %.c,%.o,$(IOE_SPI_USI_SRC))
IOE_SPI_USART_OBJ = $(patsubst %.c,%.o,$(IOE_SPI_USART_SRC))
