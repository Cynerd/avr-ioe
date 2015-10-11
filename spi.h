#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "mcu/mcu_def.h"
#include "buffers.h"

#ifndef _IOE_SPI_H_
#define _IOE_SPI_H_

#ifndef MCUSUPPORT_SPI
#error "No SPI interface is known on your mcu."
#endif

enum spiMode {
    SPI_MODE_MASTER,
    SPI_MODE_SLAVE
};


/*
 * Initialize SPI
 *
 *  Parameters:
 *    mode - Specify mode of SPI interface
 *
 * NOTE: Global interrupt must be enabled for right function of SPI.
 * { SREG |= _BV(7) }
 */
void spi_init(enum spiMode mode);
/*
 * Returns NULL when device is not busy.
 * When device is busy return values in non-zero.
 */
int8_t spi_busy(void);
/*
 * Blocks processor until device is not busy.
 */
void spi_join(void);
/*
 * Swap bytes with slave over SPI.
 * This function blocks execution until device isn't busy (transfer completed).
 * WARNING: Invoke this only when interface is initialized in MASTER mode.
 */
uint8_t spi_send(uint8_t data);
/*
 * Transfer byte to slave over SPI.
 * This function isn't blocking execution until transfer is complete.
 * Always call spi_join before this function when called outside of spi_receive().
 * WARNING: Invoke this only when interface is initialized in MASTER mode.
 */
void spi_transfer(uint8_t data);
/*
 * Expose data for next master request.
 * Please don't use this when device is busy.
 * Best place to call this is spi_receive().
 * WARNING: Invoke this only when interface is initialized in SLAVE mode.
 */
void spi_expose(uint8_t data);

/*
 * This function is called every time transfer is finished.
 * And until return from this function interrupts are disabled.
 */
extern void (*spi_receive)(uint8_t data);

#endif /* _IOE_SPI_H_ */
