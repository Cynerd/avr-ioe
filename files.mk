
IOE_SPI_SRC = $(IOE_PREFIX)/src/avr5/spi.c
IOE_SPI_USI_SRC = $(IOE_PREFIX)/src/avr25/spi_usi.c

IOE_SPI_OBJ = $(patsubst %.c,%.o,$(IOE_SPI_SRC))
IOE_SPI_USI_OBJ = $(patsubst %.c,%.o,$(IOE_SPI_USI_SRC))
