#include <avr/io.h>
#include <util/delay.h>
#include <spi.h>

void receive(uint8_t data);

int main() {
    DDRB |= _BV(DDB1);
    spi_receive = receive;
    spi_init(SPI_MODE_SLAVE);
    SREG |= _BV(7);
    while (1) {
    }
}

void receive(uint8_t data) {
    if (data)
        PORTB |= _BV(PORTB1);
    else
        PORTB &= ~_BV(PORTB1);
}
