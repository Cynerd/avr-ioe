#include <usart.h>
#ifdef CONFIG_USART

#define USART_PARITY_NONE 0
#define USART_PARITY_ODD 1
#define USART_PARITY_EVEN 2

#define USART_STOPBIT_SINGLE 1
#define USART_STOPBIT_DOUBLE 2

volatile int8_t _usart_busy;

void usart_init_async(void) {
    _usart_busy = 0;
#define BAUD CONFIG_USART_BAUD
#include <util/setbaud.h>
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~_BV(U2X0);
#endif

    UCSR0C = 0 |
// USART_PARITY_NONE are both UMP01 and UMP00 zero
#if CONFIG_USART_PARITY == USART_PARITY_ODD
        _BV(UPM01) |
#elif CONFIG_USART_PARITY == USART_PARITY_EVEN
        _BV(UPM00) | _BV(UPM01) |
#endif
// USART_STOPBIT_SINGLE is USBS0 zero
#if CONFIG_USART_STOPBIT == USART_STOPBIT_DOUBLE
        _BV(USBS0) |
#endif
// For 5 databits are UCSZ00 and UCSZ01 zero
#if CONFIG_USART_DATABITS == 6
        _BV(UCSZ00)
#elif CONFIG_USART_DATABITS == 7
        _BV(UCSZ01)
#elif CONFIG_USART_DATABITS == 8
        _BV(UCSZ00) | _BV(UCSZ01)
#endif
        ;
    // Enable receiver, transmitter and RX complete,
    // Data register empty interrupts
    UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0) | _BV(UDRIE0);
#ifdef CONFIG_USART_INPUT_BUFFER
    IOEBUFFER_INIT(_ioe_usart_inbuffer, CONFIG_USART_INBUFFER_SIZE);
#endif
#ifdef CONFIG_USART_OUTPUT_BUFFER
    IOEBUFFER_INIT(_ioe_usart_outbuffer, CONFIG_USART_OUTBUFFER_SIZE);
#endif
}

inline void usart_send(uint8_t data) {
#ifdef CONFIG_USART_OUTPUT_BUFFER
    if (!_usart_busy) {
        _usart_busy = 1;
        UDR0 = data;
    } else {
        IOEBUFFER_PUT(_ioe_usart_outbuffer,
                      CONFIG_USART_OUTBUFFER_SIZE, data,
                      CONFIG_USART_OUTBUFFER_MODE);
    }
#else
    _usart_busy = 1;
    UDR0 = data;
#endif /* CONFIG_USART_OUTPUT_BUFFER */
}

#ifdef CONFIG_USART_OUTPUT_BUFFER
inline void usart_send_str(char *str) {
    while (*str != '\0') {
        usart_send((uint8_t) * str);
        str++;
    }
}
#endif /* CONFIG_USART_OUTPUT_BUFFER */

#ifdef CONFIG_USART_INPUT_BUFFER
uint8_t usart_get(void) {
    uint8_t rtn;
    IOEBUFFER_GET(_ioe_usart_inbuffer, CONFIG_USART_INBUFFER_SIZE,
                  rtn);
    return rtn;
}
#endif

#ifdef CONFIG_USART_INPUT_BUFFER
uint8_t usart_inbuffered(void) {
    uint8_t rtn;
    IOEBUFFER_CNT(_ioe_usart_inbuffer, CONFIG_USART_INBUFFER_SIZE,
                  rtn);
    return rtn;
}
#endif

#ifdef CONFIG_USART_OUTPUT_BUFFER
uint8_t usart_outbuffered(void) {
    uint8_t rtn;
    IOEBUFFER_CNT(_ioe_usart_outbuffer, CONFIG_USART_OUTBUFFER_SIZE,
                  rtn);
    return rtn;
}
#endif

#ifdef CONFIG_USART_OUTFILE
static int usartput(char c, FILE * f) {
    usart_send((uint8_t) c);
    return 0;
}
#endif

#ifdef CONFIG_USART_INPUT_BUFFER
static int usartget(FILE * f) {
    uint8_t v;
    while (!(v = usart_get()));
    return v;
}
#endif

#if (defined CONFIG_USART_INFILE) || (defined CONFIG_USART_OUTFILE)
FILE *usart_async_open(void) {
    usart_init_async();
#ifdef CONFIG_USART_OUTFILE
#ifdef CONFIG_USART_INFILE
    return fdevopen(usartput, usartget);
#else
    return fdevopen(usartput, 0);
#endif
#else
    return fdevopen(0, usartget);
#endif
}
#endif

////// Interrupts ////////////////////////////////
void (*usart_receive) (uint8_t data) = 0;
void (*usart_sent) (void) = 0;

SIGNAL(USART_RX_vect) {
#ifdef CONFIG_USART_INPUT_BUFFER
    uint8_t val = UDR0;
    IOEBUFFER_PUT(_ioe_usart_inbuffer, CONFIG_USART_INBUFFER_SIZE,
                  val, CONFIG_USART_INBUFFER_MODE);
#endif /* CONFIG_USART_INPUT_BUFFER */
    if (usart_receive)
        usart_receive(UDR0);
}

SIGNAL(USART_UDRE_vect) {
#ifdef CONFIG_USART_OUTPUT_BUFFER
    uint8_t val;
    IOEBUFFER_GET(_ioe_usart_outbuffer, CONFIG_USART_OUTBUFFER_SIZE,
                  val);
    if (val)
        UDR0 = val;
    else
        _usart_busy = 0;
#else
    _usart_busy = 0;
#endif /* CONFIG_USART_OUTPUT_BUFFER */
    if (usart_sent)
        usart_sent();
}

#endif /* CONFIG_USART */
