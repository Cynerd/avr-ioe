#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "mcu/mcu_def.h"
#include "tasks.h"
#include "buffers.h"

#ifndef _IOE_SPI_H_
#define _IOE_SPI_H_
#ifdef CONFIG_IOE_SPI

#ifndef MCUSUPPORT_SPI
#error "No SPI interface is known on your mcu."
#endif

enum spiMode {
    SPI_MODE_MASTER,
    SPI_MODE_SLAVE
};

volatile extern int8_t _spi_busy;

static inline void spi_init(enum spiMode mode) {
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

static inline int8_t spi_busy(void) {
    return _spi_busy;
}

static inline void spi_join(void) {
    taskDelayTill(_spi_busy);
}

static inline uint8_t spi_send(uint8_t data) {
    spi_transfer(data);
    taskDelayTill(_spi_busy);
    return SPDR;
}

static inline void spi_transfer(uint8_t data) {
    _spi_busy = 1;
    SPDR = data;
}

static inline void spi_expose(uint8_t data) {
    SPDR = data;
}

extern void (*spi_receive)(uint8_t data);

#endif /* CONFIG_IOE_SPI */
#endif /* _IOE_SPI_H_ */
