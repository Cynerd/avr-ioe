#include <util/setbaud.h>
UBRR0H = UBRRH_VALUE;
UBRR0L = UBRRL_VALUE;
#if USE_2X
UCSR0A |= _BV(U2X0);
#else
UCSR0A &= ~_BV(U2X0);
#endif
#undef BAUD
#undef UBRRH_VALUE
#undef UBRRL_VALUE
#undef USE_2X
