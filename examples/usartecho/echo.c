#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <usart.h>

void rec(uint8_t data) {
    if (data == '\r') {
        usart_send_str("\n\r"); // Send new line character with carriage return
    } else if (data)
        usart_send(data);
}

int main() {
    DDRB = _BV(DDB1);
    usart_init_async();
    SREG |= _BV(7);
    usart_send('a');
    usart_send('b');
    usart_send('c'); // This character is not printed for some reason TODO
    usart_send('d');
    usart_send_str("\n\rHello, there is UART echo!\n\r");
    usart_receive = rec;

    while (1);
}


