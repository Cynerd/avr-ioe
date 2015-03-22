#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#include "mcu/mcu.h"

#ifndef _IOE_SPI_USI_H_
#define _IOE_SPI_USI_H_

/*
 * Initialize USI as SPI
 *
 * NOTE: Global interrupt must be enabled for right function.
 * { SREG |= _BV(7) }
 */
inline void ioe_spi_usi_init(void);
#ifdef IOE_SPI_USI_MASTER
/*
 * Swaps byte with slave over SPI.
 */
inline int8_t ioe_spi_usi_transfer(int8_t data);
#else
/*
 * Expose data for next master request.
 * Please don't use this when device is busy.
 * Best place to call this is ioe_spi_usi_retrieve().
 */
inline void ioe_spi_usi_expose(int8_t data);
/*
 * Returns NULL when device is no busy.
 * When device is busy, returned value is number of already send bits.
 */
inline uint8_t ioe_spi_usi_busy(void);
/*
 * Blocks processor until device is not busy.
 */
inline void ioe_spi_usi_join(void);

/*
 * This function must be defined by user.
 * This function is called every time transfer is finished.
 * And until return from this function interrupts are disabled.
 * WARNING: Please define this function in your code.
 */
inline void ioe_spi_usi_retrieve(int8_t data);
#endif /* IOE_SPI_USI_MASTER */

#if !(__MCU_ATtiny4313__ || __MCU_ATtiny85__)
#error "USI is not probably supported by your MCU."
#endif

#endif /* _IOE_SPI_USI_H_ */
