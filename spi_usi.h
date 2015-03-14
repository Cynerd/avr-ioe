#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#include "mcu/mcu.h"

#ifndef _IOE_SPI_USI_H_
#define _IOE_SPI_USI_H_

inline void ioe_spi_usi_init(void);
#ifdef IOE_SPI_USI_MASTER
inline int8_t ioe_spi_usi_transfer(int8_t data);
#else
inline void ioe_spi_usi_expose(int8_t data);
inline void ioe_spi_usi_expect(void);
inline int ioe_spi_usi_ready(void);
inline void ioe_spi_usi_join(void);

// Following function must be user defined
inline void ioe_spi_usi_retrieve(int8_t data);
#endif /* IOE_SPI_USI_MASTER */


#endif /* _IOE_SPI_USI_H_ */
