#include <inttypes.h>

#include "config.h"

#if (defined IOE_NRF_SPI)
#include "../spi.h"
#elif (defined IOE_NRF_USI)
#include "../spi_usi.h"
#elif (defined IOE_NRF_USART)
#include "../spi_usart.h"
#endif

#ifndef _IOE_NRF_H_
#define _IOE_NRF_H_

void ioe_nrf_init(void);

void ioe_nrf_set_address();
int ioe_nrf_ready(void);
void ioe_nrf_joint(void);
void ioe_nrf_transmit(int8_t);
int8_t ioe_nrf_retrieve(void);

#endif /* _IOE_NRF_H_ */
