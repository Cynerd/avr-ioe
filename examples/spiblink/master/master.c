#include <avr/io.h>
#include <util/delay.h>
#include <ioport.h>
#include <spi.h>

int main() {
	io_setin(CONFIG_BUTTON_IO, IO_PULLUP);
	io_setout(CONFIG_LED_IO);

	spi_init(SPI_MODE_MASTER);
	// SREG |= _BV(7); // Enable interrupts TODO I don't think that we need this

	while (1) {
		io_set(CONFIG_LED_IO, io_get(CONFIG_BUTTON_IO));
		spi_send(io_get(CONFIG_BUTTON_IO));
	}
}
