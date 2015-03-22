#include <avr/io.h>
#include <stdint.h>

#ifndef _IOE_SPI_H_
#define _IOE_SPI_H_

inline void ioe_spi_init(void);
inline int ioe_spi_bussy(void);
inline void ioe_spi_join(void);
#ifdef IOE_SPI_MASTER
inline int8_t ioe_spi_transfer(int8_t data);
#else /* IOE_SPI_MASTER */
inline void ioe_spi_expose(int8_t data);
#endif /* IOE_SPI_MASTER */

// Following function must be user defined
inline void ioe_spi_retrieve(int8_t);

#if !(__MCU_ATmega328p__ || __MCU_ATmega32U4p__)
#error "SPI is not probably supported by your hardware."
#endif

#endif /* _IOE_SPI_H_ */
