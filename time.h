#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "mcu/mcu_def.h"

#ifndef _IOE_TIME_H_
#define _IOE_TIME_H_

#ifndef CONFIG_IOE_TIME_TIMER
#error "To use Time you must specify CONFIG_IOE_TIME_TIMER macro."
#endif


#endif /* _IOE_TIME_H_ */
