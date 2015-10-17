#include "../tasks.h"

#ifdef CONFIG_IOE_TASKS

#else /* CONFIG_IOE_TASKS */

int8_t taskDelayTillT(int8_t *condition, uint8_t timeout_10us) {
    while(*condition == 0) {
        if (timeout_10us == 0)
            return 1;
        timeout_10us--;
        _delay_us(10);
    }
    return 0;
}

#endif /* CONFIG_IOE_TASKS */
