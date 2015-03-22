#include "../spi.h"
#include "mcu/mcu_def.h"

inline void ioe_spi_join(void) {
    // TODO
}

inline int ioe_spi_bussy(void) {
}

#ifdef IOE_SPI_MASTER
inline void ioe_spi_init(void) {
    // Set MOSI and SCK output
    DDR_SPI |= _BV(DD_MOSI) | _BV(DD_SCLK);
    // Set MISO pull up resistor
    PORT_SPI |= _BV(PORT_MISO);
    // Enable SPI interrupt
    SPCR |= _BV(SPIE);
    // Enable SPI master and set clock rate fck/16
    SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0);
}

inline void ioe_spi_transfer(int8_t data) {
    SPDR = data;
}

#else /* IOE_SPI_MASTER */
inline void ioe_spi_init(void) {
    // Set MISO as output
    DDR_SPI = _BV(DD_MISO);
    // Set SCLK and MOSI pull up resistor
    PORT_SPI |= _BV(PORT_SCLK) | _BV(PORT_MOSI);
    // Enable SPI interrupt
    SPCR |= _BV(SPIE);
    // Enable SPI
    SPCR = _BV(SPE);
}

inline void ioe_spi_expose(int8_t data) {
    SPDR = data;
}

#endif /* IOE_SPI_MASTER */

SIGNAL(SPI_STC_vect) {
    ioe_spi_retrieve(SPDR);
}
