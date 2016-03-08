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
typedef struct {
    uint8_t flags;
    void (*func) (void *data);
    void *data;
    uint8_t _rflags;
    uint8_t _stack_size;
    union StackPointer _sp;
} Task;
int8_t task_spawn(Task * t, uint8_t stack_size);
void taks_exit(void);
int8_t task_kill(Task * t);
int8_t task_safe(void);
int8_t task_unsafe(void);

int8_t task_delay(uint16_t cycles);
int8_t task_delay_ms(uint16_t ms);
int8_t task_delay_till(volatile int8_t * boolean, uint16_t ms);

#define MUTEX_F_TIMED (1<<0)
#define MUTEX_F_TAKEN (1<<7)
typedef struct {
    uint8_t flags;
    Task *_task_took;
} Mutex;
int8_t mutex_init(Mutex * mtx);
int8_t mutex_free(Mutex * mtx);
int8_t mutex_take(Mutex * mtx, uint16_t timeout);
int8_t mutex_give(Mutex * mtx);

typedef struct {
    uint8_t flags;
    uint8_t _count;
    Task **_tasks;
    uint8_t _tasks_len;
} Semaphore;
int8_t semaphore_init(Semaphore * sem, uint8_t count);
int8_t semaphore_free(Semaphore * sem);
int8_t semaphore_take(Semaphore * sem, uint16_t timeout);
int8_t semaphore_give(Semaphore * sem);

#else /* CONFIG_IOE_TASKS */

typedef struct {
} Task;
#define task_spawn(T, STACK_SIZE)
#define task_exit()
#define task_kill(T)
#define task_safe()
#define task_unsafe()

#define task_delay(US) _delay_us(US) // TODO this should be cycles
#define task_delay_ms(MS) _delay_ms(MS)
int8_t task_delay_till(volatile int8_t * boolean, uint16_t ms);

typedef struct {
} Mutex;
#define mutex_init(MTX, FLAGS)
#define mutex_free(MTX)
#define mutex_take(MTX, TIMEOUT)
#define mutex_give(MTX);

typedef struct {
} Semaphore;
#define semaphore_init(SEM, FLAGS, COUNT)
#define semaphore_free(SEM)
#define semaphore_take(SEM, TIMEOUT)
#define semaphore_give(SEM)

#endif /* CONFIG_IOE_TASKS */
#endif /* _IOE_TASKS_H_ */
