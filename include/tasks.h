#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>

#include "mcu/mcu_def.h"
#include "timer.h"

#ifndef _IOE_TASKS_H_
#define _IOE_TASKS_H_

#ifdef CONFIG_IOE_TASKS

#ifndef CONFIG_IOE_TIMERS
#error "To use tasks you must enable timers (CONFIG_IOE_TIMERS)."
#endif

int8_t tasks_run(void);

union StackPointer {
    uint8_t lh8[2];
    uint16_t lh16;
};

struct Task {
    uint8_t flags;
    void (*func) (void *data);
    void *data;
    uint8_t _rflags;
    uint8_t _stack_size;
    union StackPointer _sp;
};
typedef task_t volatile struct Task;

int8_t task_spawn(struct Task * t, uint8_t stack_size);
Task *tasks_self(void);
void taks_exit(void);
int8_t task_kill(struct Task * t);
int8_t task_safe(void);
int8_t task_unsafe(void);

int8_t task_delay(uint16_t cycles);
int8_t task_delay_ms(uint16_t ms);
int8_t task_delay_till(volatile int8_t * boolean, uint16_t ms);

#else /* CONFIG_IOE_TASKS */

#define task_safe()
#define task_unsafe()
#define task_delay(CC) _delay_us(CC) // TODO this should be cycles
#define task_delay_ms(MS) _delay_ms(MS)
int8_t task_delay_till(volatile int8_t * boolean, uint16_t ms);

#endif /* CONFIG_IOE_TASKS */
#endif /* _IOE_TASKS_H_ */
