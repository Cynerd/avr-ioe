#include <spi.h>

#ifdef CONFIG_SPI

volatile int8_t _spi_busy;
volatile Mutex spi_mutex;

void (*spi_receive) (uint8_t data) = 0;

ISR(SPI_STC_vect, ISR_BLOCK) {
    _spi_busy = 0;
    if (spi_receive != NULL) {
        spir_w(SPDR);
    }
}

#endif /* CONFIG_SPI */
