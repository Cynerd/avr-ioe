#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "mcu/mcu_def.h"

#ifndef _IOE_USI_SPI_H_
#define _IOE_USI_SPI_H_

#ifndef MCUSUPPORT_USI
#error "No USI interface is known on your mcu."
#endif

enum usiSpiMode {
    // Device is initialized as master
    USI_SPI_MODE_MASTER,
    // Device is initialized as slave
    USI_SPI_MODE_SLAVE,
};

/*
 * Initialize SPI on USI device
 *
 *  Parameters:
 *    mode - Specify mode of SPI interface
 */
void usi_spi_init(enum usiSpiMode mode);
/*
 * Returns NULL when device is not busy.
 * When device is busy return values in non-zero.
 */
int8_t usi_spi_busy(void);
/*
 * Blocks processor until device is not busy.
 */
void usi_spi_join(void);
/*
 * Swap bytes with slave over SPI.
 * This function blocks execution until device isn't busy.
 * WARNING: Invoke this only when interface is initialized in MASTER mode.
 */
uint8_t usi_spi_send(uint8_t data);
/*
 * Swaps byte with slave over SPI.
 * This function isn't checking if device is busy, but it's not blocking execution.
 * WARNING: Invoke this only when interface is initialized in MASTER mode.
 */
uint8_t usi_spi_transfer(uint8_t data);
/*
 * Expose data for next master request.
 * Please don't use this when device is busy.
 * Best place to call this is usi_spi_retrieve().
 * WARNING: Invoke this only when interface is initialized in SLAVE mode.
 */
void usi_spi_expose(uint8_t data);

/*
 * This function must be defined by user.
 * This function is called every time transfer is finished.
 * And until return from this function interrupts are disabled.
 * WARNING: Please define this function in your code.
 */
void usi_spi_receive(uint8_t data);


#endif /* _IOE_USI_SPI_H_ */
