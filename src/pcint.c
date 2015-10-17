/* This file defines and handles Pin change interupts.
 * This interupt can be used in different modules and sensors. Function call can
 * be done from this interrupt handdler.
 */
#include <avr/interrupt.h>

#if (defined CONFIG_IOE_SENSOR_DHT22)

#ifdef CONFIG_IOE_SENSOR_DHT22
extern void dht22_read_pcint(void);
#endif


ISR(PCINT0_vect, ISR_BLOCK) {
#ifdef CONFIG_IOE_SENSOR_DHT22
    void dht22_read_pcint();
#endif
}

ISR(PCINT1_vect, ISR_BLOCK) {
#ifdef CONFIG_IOE_SENSOR_DHT22
    void dht22_read_pcint();
#endif
}

ISR(PCINT2_vect, ISR_BLOCK) {
#ifdef CONFIG_IOE_SENSOR_DHT22
    void dht22_read_pcint();
#endif
}

#endif
