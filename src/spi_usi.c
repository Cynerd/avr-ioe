#include "../spi_usi.h"
#include "../mcu/mcu_def.h"

#ifdef IOE_SPI_USI_MASTER

// TODO counter settings with interups
inline void ioe_spi_usi_init(void) {
    // Set USCK and DO as output
    DDR_USI |= _BV(DD_USCK) | _BV(DD_DO);
    // Set DI pull up resistor
    PORT_USI |= _BV(PORT_DI);

    USICR |= _BV(USIWM0) | _BV(USICS1) | _BV(USICLK);
}

inline int8_t ioe_spi_usi_transfer(int8_t d) {
    USISR |= _BV(USIOIF);
    USIDR = d;
    do {
        USICR |= _BV(USITC);
    } while (!(USISR & _BV(USIOIF)));
    return USIDR;
}

#else /* IOE_SPI_USI_MASTER */

inline void ioe_spi_usi_init(void) {
    // Set DO as output
    DDR_USI |= _BV(DD_DO);
    // Set USCK and DI pull up resistor
    PORT_USI |= _BV(PORT_USCK) | _BV(PORT_DI);

    USICR |= _BV(USIWM0) | _BV(USICS1) | _BV(USIOIE);
}

inline void ioe_spi_usi_expose(int8_t data) {
    USIDR = data;
}

inline uint8_t ioe_spi_usi_busy(void) {
    return USISR & 0x0F;
}

inline void ioe_spi_usi_join(void) {
    while (ioe_spi_usi_busy()) {
    }
}

SIGNAL(USI_OVF_vect) {
    ioe_spi_usi_retrieve(USIDR);
    USISR |= _BV(USIOIF);
}

#endif /* IOE_SPI_USI_MASTER */
