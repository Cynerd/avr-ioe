#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#ifndef _IOE_SPI_USART_H_
#define _IOE_SPI_USART_H_

inline void ioe_spi_usart_init(void);
inline int8_t ioe_spi_usart_transfer(int8_t);
inline int ioe_spi_usart_bussy(void);
inline void ioe_spi_usart_join(void);

#endif /* _IOE_SPI_USART_H_ */
