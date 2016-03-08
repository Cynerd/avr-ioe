#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "mcu/mcu_def.h"

#ifndef _IOE_IOPORT_H_
#define _IOE_IOPORT_H_
#ifdef CONFIG_IOPORTS

enum ioInResistor {
    IO_PULLUP,
    IO_PULLDOWN
};

static inline void io_setout(uint8_t group, uint8_t mask) {
    IO_DDR(group) |= mask;
}
static inline void io_hight(uint8_t group, uint8_t mask) {
    IO_PORT(group) |= mask;
}
static inline void io_low(uint8_t group, uint8_t mask) {
    IO_PORT(group) &= ~mask;
}
static inline void io_set(uint8_t group, uint8_t mask, int8_t val) {
    if (val)
        io_hight(group, mask);
    else
        io_low(group, mask);
}

static inline void io_setin(uint8_t group, uint8_t mask,
                            enum ioInResistor resistor) {
    IO_DDR(group) &= ~mask;
    if (resistor == IO_PULLUP)
        IO_PORT(group) |= mask;
    else
        IO_PORT(group) &= ~mask;
}
static inline int8_t io_get(uint8_t group, uint8_t mask) {
    return (int8_t) IO_PIN(group) & mask;
}

#ifdef CONFIG_PCINT

#define IO_RISING (1 << 0)
#define IO_FALLING (1 << 1)
void io_change_sethook(uint8_t group, uint8_t mask, uint8_t edge,
                         void (*change) (uint8_t group, uint8_t mask));
void io_change_remhook(void (*change) (uint8_t group, uint8_t mask));
void io_change_clearhooks(void);

#endif /* CONFIG_PCINT */
#endif /* CONFIG_IOPORTS */
#endif /* _IOE_IOPORT_H_ */
