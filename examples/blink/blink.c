#include <avr/io.h>
#include <util/delay.h>
#include <ioport.h>

int main() {
    io_setout(IO_B3);

    while (1) {
        io_hight(IO_B3);
        _delay_ms(500);
        io_low(IO_B3);
        _delay_ms(500);
    }
}
