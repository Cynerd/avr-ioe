#include "../spi.h"

volatile int8_t _spi_busy;

inline void spi_init(enum spiMode mode) {
    _spi_busy = 0;
    if (mode == SPI_MODE_MASTER) {
        // Set MOSI and SCK output
        DDR_SPI |= _BV(DD_MOSI) | _BV(DD_SCLK);
        // Set MISO pull up resistor
        PORT_SPI |= _BV(PORT_MISO);
        // Enable SPI master, set clock rate fck/16 and enable SPI interrupt
        SPCR = _BV(SPE) | _BV(SPIE) | _BV(MSTR) | _BV(SPR0);
    } else {
        // Set MISO as output
        DDR_SPI |= _BV(DD_MISO);
        // Set SCLK and MOSI pull up resistor
        PORT_SPI |= _BV(PORT_SCLK) | _BV(PORT_MOSI);
        // Enable SPI and interrupt
        SPCR = _BV(SPE) | _BV(SPIE);
    }
}

inline int8_t spi_busy(void) {
    return _spi_busy;
}

inline void spi_join(void) {
    while (spi_busy());
}

inline uint8_t spi_send(uint8_t data) {
    spi_transfer(data);
    while (spi_busy());
    return SPDR;
}

inline void spi_transfer(uint8_t data) {
    _spi_busy = 1;
    SPDR = data;
}

inline void spi_expose(uint8_t data) {
    SPDR = data;
}

////// Interrupts ////////////////////////////////
void (*spi_receive)(uint8_t data) = 0;

SIGNAL(SPI_STC_vect) {
    _spi_busy = 0;
    if (spi_receive)
        spi_receive(SPDR);
}
