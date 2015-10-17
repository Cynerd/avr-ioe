#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "mcu/mcu_def.h"
#include "buffers.h"

#ifndef _IOE_TWI_H_
#define _IOE_TWI_H_

#ifndef MCUSUPPORT_TWI
#error "No TWI interface is known on your mcu."
#endif

enum twiMode {
    TWI_MODE_MASTER,
    TWI_MODE_SLAVE
};

void twi_init(enum twiMode);
int8_t twi_busy(void);
void twi_join(void);
void twi_send(uint8_t data);

#endif /* _IOE_TWI_H_ */
