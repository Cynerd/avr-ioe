#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "tasks.h"
#include "timer.h"

#ifndef _IOE_SENSOR_DHT22_H_
#define _IOE_SENSOR_DHT22_H_

struct dht22_value {
    uint8_t integral;
    uint8_t decimal;
};

struct dht22_port {
    volatile uint8_t *DDR;  // Address of DDR register
    volatile uint8_t *PORT; // Address of PORT register
    volatile uint8_t *PIN;  // Address of PIN register
    uint8_t MASK;   // _BV() of index of port
    volatile uint8_t *PCMSK;    // Address of relevant PCMSK register
    uint8_t PCMSK_MASK; // _BV() of index of PCMSK
};

extern const struct dht22_port dht22_ports[];

/*
 * Initialize port for sensor
 */
void dht22_init(uint8_t port);
/*
 * Read values from dht22
 * rh - relative
 * t  - temperature
 */
int8_t dht22_read(uint8_t portindex, struct dht22_value *rh,
                  struct dht22_value *t);

#endif /* _IOE_SENSOR_DHT22_H_ */
