#if (defined __AVR_ATmega328P__ || defined __AVR_ATmega328__ || \
        defined __AVR_ATmega1688PA__ || defined __AVR_ATmega168A__ || \
        defined __AVR_ATmega88PA__ || defined __AVR_ATmega88A__ || \
        defined __AVR_ATmega48PA__ || defined AVR_ATmega48A__)
#include "ATmega328P.h"
#endif

#if (defined __AVR_ATmega328U4__ || defined __AVR_ATmega16U4)
#include "ATmega32U4.h"
#endif

#if (defined __AVR_ATtiny4313__ || defined __AVR_ATtiny2313A__)
#include "ATtiny4313.h"
#endif

#if (defined __AVR_ATtiny85__ || defined __AVR_ATtiny45__ || \
        defined __AVR_ATtiny25__)
#include "ATtiny85.h"
#endif
