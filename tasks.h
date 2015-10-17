#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "mcu/mcu_def.h"
#include "timer.h"

#ifndef _IOE_TASKS_H_
#define _IOE_TASKS_H_
#ifdef CONFIG_IOE_TASKS

#ifndef CONFIG_IOE_TIMERS
#error "To use tasks you must enable timers (CONFIG_IOE_TIMERS)."
#endif

struct Task {

};

void taskDelay(uint16_t us);
void taskDelayMS(uint16_t ms);
void taskDelayTill(int8_t *boolean);
int8_t taskDelayTillT(int8_t *boolean, uin16_t us);
void taskDelayTillF(int8_t (*fnc)(void));
void taskDelayTillFT(int8_t (*fnc)(void), uint16_t us);

#else /* CONFIG_IOE_TASKS */

#define taskDelay(US) _delay_us(US)
#define taskDelayTill(BOOL) while(*BOOL == 0)
int8_t taskDelayTillT(int8_t *condition, uint8_t timeout_10us);

#endif /* CONFIG_IOE_TASKS */
#endif /* _IOE_TASKS_H_ */
