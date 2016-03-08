#include <sensors/dht22.h>

#ifdef CONFIG_IOE_SENSOR_DHT22

#define PP dht22_ports[pi]
#define PPP dht22_ports[dht22_measurement.pi]

#define TIMEOUT F_CPU/40000

#define STATUS_NONE 0
#define STATUS_COMPLETE 1
#define STATUS_TIMEOUT 2

#define PORT_SENSORW 4
#define PORT_SENSORRESP_L 3
#define PORT_SENSORRESP_H 2
#define PORT_H 1
#define PORT_L 0

struct {
    uint8_t index;
    uint8_t data[5];
    volatile uint8_t status;
    uint8_t pi;
    uint8_t port_status;
} dht22_measurement;

inline void dht22_init(uint8_t pi) {
    // Set port as output and set level hight
    *(PP.DDR) |= PP.MASK;
    *(PP.PORT) |= PP.MASK;
    // Enable all pin change interrupts
    PCIFR = 0xff;
}


inline void dht22_read_deac(uint8_t status) {
    dht22_measurement.status = status;
    // Disable pin change interrupt
    *(PPP.PCMSK) &= ~PPP.PCMSK_MASK;
    timer_disable(CONFIG_IOE_SENSOR_DHT22_TIMER);
}

// This is called from pcint.c
void dht22_read_pcint(void) {
    switch (dht22_measurement.port_status) {
    case PORT_L:
        if (!(*(PPP.PIN) & PPP.MASK))
            return;
        dht22_measurement.port_status = PORT_H;
        break;
    case PORT_H:
        if (*(PPP.PIN) & PPP.MASK)
            return;
        dht22_measurement.port_status = PORT_L;
        register uint16_t val;
        val = timer_value(CONFIG_IOE_SENSOR_DHT22_TIMER);
        // TODO compare value
        if (val < 1) {
            dht22_measurement.data[dht22_measurement.index / 8]
        }
        if (++(dht22_measurement.index) == 40) {
            dht22_read_deac(STATUS_COMPLETE);
            return;
        }
        break;
    default:
        if (((*(PPP.PIN) & PPP.MASK) && dht22_measurement.port_status == 3)
            || !(*(PPP.PIN & PPP.MASK)))
            return;
        dht22_measurement.port_status--;
    }
    timer_reset(CONFIG_IOE_SENSOR_DHT22_TIMER);
}

void dht22_read_timer_overflow(void) {
    dht22_read_deac(STATUS_TIMEOUT);
}

int8_t dht22_read(uint8_t pi, struct dht22_value *rh,
                  struct dht22_value *t) {
    dht22_measurement.index = 0;
    dht22_measurement.status = STATUS_NONE;
    dht22_measurement.pi = pi;
    dht22_measurement.port_status = PORT_SENSORW;

    // Pull port down for 500us
    *(PP.PORT) &= ~PP.MASK;
    _delay_us(500);
    // Initialize timer
    timer_init(CONFIG_IOE_SENSOR_DHT22_TIMER, TIMER_DIVIDER_64);
    timer_sethook(CONFIG_IOE_SENSOR_DHT22_TIMER,
                  dht22_read_timer_overflow);
    // Set pin change interrupt
    *(PP.PCMSK) |= PP.PCMSK_MASK;
    // Set port as output and pull-up resistor
    *(PP.DDR) &= ~PP.MASK;
    *(PP.PORT) |= PP.MASK;
    // Delay till reading is done
    taskDelayTill(&(dht22_measurement.status));

    // Copy data
    rh->integral = dht22_measurement.data[0];
    rh->decimal = dht22_measurement.data[1];
    t->integral = dht22_measurement.data[2];
    t->decimal = dht22_measurement.data[3];
    // Check sum
    uint8_t sum = dht22_measurement.data[0];
    sum += dht22_measurement.data[1];
    sum += dht22_measurement.data[2];
    sum += dht22_measurement.data[3];
    if (sum != dht22_measurement.data[4])
        return 1;
    return dht22_measurement.status - 1;
}

#endif /* CONFIG_IOE_SENSOR_SHT22 */
