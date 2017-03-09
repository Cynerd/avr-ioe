#include <avr/io.h>
#include <util/delay.h>
#include <ioport.h>

int main() {
	io_setout(CONFIG_BLINK_IO);

	while (1) {
		io_high(CONFIG_BLINK_IO);
		_delay_ms(500);
		io_low(CONFIG_BLINK_IO);
		_delay_ms(500);
	}
}
