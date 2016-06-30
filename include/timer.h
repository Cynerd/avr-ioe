// vim:ts=4:sw=4:sts=4:expandtab
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "mcu/mcu_def.h"
#include "utils/narray.h"

#ifndef _IOE_TIMER_H_
#define _IOE_TIMER_H_
#ifdef CONFIG_IOE_TIMERS

enum timerDivider {
    TIMER_DIVIDER_1,
    TIMER_DIVIDER_8,
    TIMER_DIVIDER_64,
    TIMER_DIVIDER_256,
    TIMER_DIVIDER_1024
};

void timer_init(uint8_t timer, enum timerDivider div);
void timer_disable(uint8_t timer);
void timer_reset(uint8_t timer);
uint16_t timer_value(uint8_t timer);
void timer_sethook(uint8_t timer, void (*fnc) (void));
void timer_remhook(uint8_t timer, void (*fnc) (void));

#endif /* CONFIG_IOE_TIMERS */
#endif /* _IOE_TIMER_H_ */
