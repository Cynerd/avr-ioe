#include <avr/io.h>
#include <util/delay.h>
#include "../../spi.h"

int main() {
    DDRB |= _BV(DDB1) | _BV(DDB2);
    PORTC |= _BV(PORTC1);
    spi_init(SPI_MODE_MASTER);
    SREG |= _BV(7);
    while (1) {
        if (PINC & _BV(PINC1)) {
            PORTB &= ~_BV(PORTB1);
        } else {
            PORTB |= _BV(PORTB1);
        }
        PORTB &= ~_BV(PORTB2);
        spi_send(!(PINC & _BV(PINC1)));
        PORTB |= _BV(PORTB2);
    }
}
