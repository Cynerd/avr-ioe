#include <tasks.h>
#ifdef CONFIG_IOE_TASKS

void tasks_run(void) {
}

void task_init(Task * t, void (*func) (void)) {
}
void task_start(Task * t) {
}

void task_delay(uint16_t us) {
}
void task_delay_ms(uint16_t ms) {
}
void task_delay_till(volatile int8_t * boolean, uint16_t timeout) {
}

int8_t task_stack_init(TaskStack * ts, uint8_t stack_size, uint8_t flags) {
    ts->stack = malloc(stack_size * sizeof(uint8_t));
    ts->flags = flags;
    ts->running = NULL;
    ts->pending = NULL;
}

void task_stack_free(TaskStack * ts) {
    free(ts->stack);
}

void task_stack_reg(TaskStack * ts, Task * t) {
}

void task_stack_unreg(TaskStack * ts, Task * t) {
}

#else /* CONFIG_IOE_TASKS */

int8_t task_delay_till(volatile int8_t * boolean, uint16_t timeout) {
    if (timeout == 0)
        while (!*boolean)
            _delay_us(100);
    else
        // TODO this implementation should be improved to check boolean as often
        // as possible
        while (*boolean == 0) {
            if (timeout == 0)
                return 1;
            timeout--;
            _delay_ms(1);
        }
    return 0;
}

#endif /* CONFIG_IOE_TASKS */
