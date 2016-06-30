#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef _IOE_SYS_SEMAPHORE_H_
#define _IOE_SYS_SEMAPHORE_H_
#ifdef CONFIG_IOE_SEMAPHORE

#define semaphore_t volatile struct Semaphore
struct Semaphore {
    uint8_t flags;
    uint8_t _count;
    Task **_tasks;
    uint8_t _tasks_len;
};
int8_t semaphore_init(struct Semaphore * sem, uint8_t count);
int8_t semaphore_free(struct Semaphore * sem);
int8_t semaphore_take(struct Semaphore * sem, uint16_t timeout);
int8_t semaphore_give(Semaphore * sem);

#else /* CONFIG_IOE_SEMAPHORE */

#define semaphore_t struct { }
// TODO implement for single processor
#define semaphore_init(SEM, FLAGS, COUNT)
#define semaphore_free(SEM)
#define semaphore_take(SEM, TIMEOUT)
#define semaphore_give(SEM)

#endif /* CONFIG_IOE_SEMAPHORE */
#endif /* _IOE_SYS_SEMAPHORE_H_ */
