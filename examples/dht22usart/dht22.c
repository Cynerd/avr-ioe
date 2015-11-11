#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "../../usart.h"
//#include "../../sensor_dht22.h"

void rec(uint8_t data) {
    if (data == '\r') {
        // TODO read sensor and send data
    }
}

const struct dht22_port dht22_ports[] = {
    {&DDRC, &PORTC, &PINC, _BV(PORTC4), NULL, 0}
};

int main() {
    //usart_async_open();
    //sei();
    //usart_receive = rec;
    //dht22_init(0);

    timer_init(COUNTER0_PWM);
    while (1);
}
