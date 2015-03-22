#include "../nrf.h"

#if (defined IOE_NRF_SPI)
#define SPI_EXP
#elif (defined IOE_NRF_USI)
#define SPI_EXP usi_
#elif (defined IOE_NRF_USART)
#define SPI_EXP usart_
#endif

void rw_nrf(

void ioe_nrf_init(void) {
}


void ioe_nrf_set_address() {
}

int ioe_nrf_ready(void) {
}

void ioe_nrf_joint(void) {
}

void ioe_nrf_transmit(int8_t d) {
}

int8_t ioe_nrf_retrieve(void) {
}
