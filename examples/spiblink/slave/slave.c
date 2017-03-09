#include <avr/io.h>
#include <util/delay.h>
#include <ioport.h>
#include <spi.h>

void receive(uint8_t data);

int main() {
	io_setout(CONFIG_BLINK_IO);

	spi_receive = receive;
	spi_init(SPI_MODE_SLAVE);
	SREG |= _BV(7); // Enable global interrupts
	while (1);  // Busy loop
}

void receive(uint8_t data) {
	io_set(CONFIG_BLINK_IO, data);
}
