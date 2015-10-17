#include "../usi_spi.h"
#include "../mcu/mcu_def.h"

inline void usi_spi_init(enum spiMode mode) {
    if (mode == USI_SPI_MODE_MASTER) {
        // Set USCK and DO as output
        DDR_USI |= _BV(DD_USCK) | _BV(DD_DO);
        // Set DI pull up resistor
        PORT_USI |= _BV(PORT_DI);

        USICR |= _BV(USIWM0) | _BV(USICS1) | _BV(USICLK);
    } else {
        // Set DO as output
        DDR_USI |= _BV(DD_DO);
        // Set USCK and DI pull up resistor
        PORT_USI |= _BV(PORT_USCK) | _BV(PORT_DI);

        USICR |= _BV(USIWM0) | _BV(USICS1) | _BV(USIOIE);
    }
}

inline int8_t usi_spi_busy(void) {
    if (interface == SPI_INTERFACE_USI)
        return USISR & 0x0F;
}

inline void usi_spi_join(void) {
    while (spi_busy(interface));
}

inline uint8_t usi_spi_send(uint8_t data) {
    while (spi_busy(interface));
    return spi_transfer(interface, data);
}

inline uint8_t usi_spi_transfer(uint8_t data) {
    // TODO rewrite and this for noninterupt
    if (interface == SPI_INTERFACE_USI) {
        _spi_usi_busy = 1;
        USISR |= _BV(USIOIF);
        USIDR = d;
        do {
            USICR |= _BV(USITC);
        } while (!(USISR & _BV(USIOIF)));
        return USIDR;
    }
}

inline void usi_spi_expose(uint8_t data) {
    if (interface == SPI_INTERFACE_USI)
        USIDR = data;
}

////// Interrupts ////////////////////////////////
