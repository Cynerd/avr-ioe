#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "../../usart.h"

void rec(uint8_t data) {
    if (data)
        usart_send(data);
}

int main() {
    usart_init_uart();
    SREG |= _BV(7);
    usart_send('a');
    usart_send('b');
    usart_send('c');
    usart_send('d');
    usart_send_str("\n\rHello, there is UART echo!\n\r");
    usart_receive = rec;

    while (1);
}


