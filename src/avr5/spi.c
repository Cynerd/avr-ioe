#include "../../spi.h"

#if __AVR_ARCH__ == 5

inline void ioe_spi_join(void) {
    // TODO
}

#ifdef IOE_SPI_MASTER
inline void ioe_spi_init(void) {
    // Set MOSI and SCK output, all other input
    DDR_SPI = _BV(DD_MOSI) | _BV(DD_SCLK);
    // Enable interrupt
    SPCR |= _BV(SPIE);
    // Enable SPI master and set clock rate fck/16
    SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0);
}

inline int ioe_spi_ready(void) {
    // TODO
}

inline void ioe_spi_transfer(int8_t data) {
    SPDR = data;
}

#else /* IOE_SPI_MASTER */
inline void ioe_spi_init(void) {
    // Set MISO as output, all other input
    DDR_SPI = _BV(DD_MISO);
    // Enable interrupt
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

#endif /* __AVR_ARCH__ == 5 */
