#include <spi.h>

#ifdef CONFIG_SPI

volatile int8_t _spi_busy;
volatile Mutex spi_mutex;

void (*spi_receive) (uint8_t data) = 0;

ISR(SPI_STC_vect, ISR_BLOCK) {
    void (*spir_w) (uint8_t data) = spi_receive;
    _spi_busy = 0;
    while (spir_w != NULL) {
        spir_w(SPDR);
        spir_w++;
    }
}

#endif /* CONFIG_SPI */
