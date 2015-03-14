#include "../../spi_usi.h"

#if __AVR_ARCH__ == 25

#ifdef IOE_SPI_USI_MASTER

// TODO counter settings with interups
inline void ioe_spi_usi_init(void) {
    USI_DIR_REG |= _BV(USI_USCK_PIN) | _BV(USI_DO_PIN);
    USI_OUT_REG |= _BV(USI_DI_PIN);

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
    USI_DIR_REG |= _BV(USI_DO_PIN);
    USI_OUT_REG |= _BV(USI_USCK_PIN) | _BV(USI_DI_PIN);

    USICR |= _BV(USIWM0) | _BV(USICS1) | _BV(USIOIE);
}

inline void ioe_spi_usi_expose(int8_t data) {
    USIDR = data;
}

inline void ioe_spi_usi_expect(void) {
    USISR |= _BV(USIOIF);
}

inline int ioe_spi_usi_busy(void) {
    return USISR & 0x0F;
}

inline void ioe_spi_usi_join(void) {
    while (ioe_spi_usi_busy()) {
    }
}

SIGNAL(USI_OVF_vect) {
    ioe_spi_usi_retrieve(USIDR);
}

#endif /* IOE_SPI_USI_MASTER */

#endif /* __AVR_ARCH__ == 25 */
