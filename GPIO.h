#include <avr/io.h>
#include <stdint.h>

#ifndef _IOE_GPIO_H_
#define _IOE_GPIO_H_

#define __GPIO_JOIN2(TXT1, TXT2) TXT1##TXT2
#define __GPIO_JOIN3(TXT1, TXT2, TXT3) TXT1##TXT2##TXT3

#define gpio_get_mode(SET, PIN)                                                 \
    __GPIO_JOIN2(DDR, SET) & _BV(__GPIO_JOIN3(DD, SET, PIN))

// GPIO output section
#define gpio_set_out(SET, PIN)                                                  \
    __GPIO_JOIN2(DDR, SET) |= _BV(__GPIO_JOIN3(DD, SET, PIN))

#define gpio_set_high(SET, PIN)                                                 \
    __GPIO_JOIN2(PORT, SET) |= _BV(__GPIO_JOIN3(PORT, SET, PIN))

#define gpio_set_low(SET, PIN)                                                  \
    __GPIO_JOIN2(PORT, SET) &= ~_BV(__GPIO_JOIN3(PORT, SET, PIN))

#define gpio_set(SET, PIN, VALUE)                                               \
    if (value)                                                                  \
        gpio_set_high(SET, PIN);                                                \
    else                                                                        \
        gpio_set_low(SET, PIN);

// GPIO input section
#define gpio_set_in(SET, PIN)                                                   \
    __GPIO_JOIN2(DDR, SET) &= ~_BV(__GPIO_JOIN3(DD, SET, PIN))

// TODO whole output and switching betwen input and output

#endif /* _IOE_GPIO_H_ */
