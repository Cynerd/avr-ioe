#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

#include "../tasks.h"

#ifndef _IOE_SYS_MUTEX_H_
#define _IOE_SYS_MUTEX_H_
#ifdef CONFIG_IOE_MUTEX

#define MUTEX_F_TIMED (1<<0)
#define MUTEX_F_TAKEN (1<<7)
#define mutex_t volatile struct Mutex
struct Mutex {
    uint8_t flags;
    Task *_task_took;
};
int8_t mutex_init(struct Mutex * mtx);
int8_t mutex_free(struct Mutex * mtx);
int8_t mutex_take(struct Mutex * mtx, uint16_t timeout);
int8_t mutex_give(struct Mutex * mtx);

#else /* CONFIG_IOE_MUTEX */

#define mutex_t struct { }
#define mutex_init(MTX, FLAGS)
#define mutex_free(MTX)
#define mutex_take(MTX, TIMEOUT)
#define mutex_give(MTX);

#endif /* CONFIG_IOE_MUTEX */
#endif /* _IOE_SYS_MUTEX_H_ */
