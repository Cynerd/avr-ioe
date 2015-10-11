#include "../usart.h"

#ifdef MCUSUPPORT_USART

#define USART_PARITY_NONE 0
#define USART_PARITY_ODD 1
#define USART_PARITY_EVEN 2

#define USART_STOPBIT_SINGLE 1
#define USART_STOPBIT_DOUBLE 2

#ifndef CONFIG_IOE_USART_BAUD
#warning "CONFIG_IOE_USART_BAUNDRATE not defined. Setting default 9600."
#define CONFIG_IOE_USART_BAUD 9600
#endif
#ifndef CONFIG_IOE_USART_PARITY
#warning "CONFIG_IOE_USART_PARITY not defined. Using default USART_PARITY_NONE."
#define CONFIG_IOE_USART_PARITY USART_PARITY_NONE
#endif
#ifndef CONFIG_IOE_USART_STOPBIT
#warning "CONFIG_IOE_USART_STOPBIT not defined. Using default USART_STOPBIT_SINGLE."
#define CONFIG_IOE_USART_STOPBIT USART_STOPBIT_SINGLE
#endif
#ifndef CONFIG_IOE_USART_DATABITS
#warning "CONFIG_IOE_USART_DATABITS not defined. Using default 8."
#define CONFIG_IOE_USART_DATABITS 8
#endif

#if !((CONFIG_IOE_USART_PARITY == USART_PARITY_NONE) || \
      (CONFIG_IOE_USART_PARITY == USART_PARITY_ODD) || \
      (CONFIG_IOE_USART_PARITY == USART_PARITY_EVEN))
#error "CONFIG_IOE_USART_PARITY has value, that is not allowed."
#endif

#if !((CONFIG_IOE_USART_STOPBIT == USART_STOPBIT_SINGLE) || \
      (CONFIG_IOE_USART_STOPBIT == USART_STOPBIT_DOUBLE))
#error "CONFIG_IOE_USART_STOPBIT has value, that is not allowed."
#endif

#if !((CONFIG_IOE_USART_DATABITS == 5) || \
      (CONFIG_IOE_USART_DATABITS == 6) || \
      (CONFIG_IOE_USART_DATABITS == 7) || \
      (CONFIG_IOE_USART_DATABITS == 8))
// TODO DATABITS 9 is not supported
#error "CONFIG_IOE_USART_DATABITS has value, that is not allowed."
#endif

#if (defined CONFIG_IOE_USART_INFILE) && (CONFIG_IOE_USART_INBUFFER_SIZE <= 0)
#error "USART Input file can't be enabled without input buffer"
#endif
#if (defined CONFIG_IOE_USART_OUTFILE) && (CONFIG_IOE_USART_OUTBUFFER_SIZE <= 0)
#error "USART Input file can't be enabled without output buffer"
#endif


volatile int8_t _usart_busy;

void usart_init_async(void) {
    _usart_busy = 0;
#define BAUD CONFIG_IOE_USART_BAUD
#include <util/setbaud.h>
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~_BV(U2X0);
#endif

#if CONFIG_IOE_USART_PARITY == USART_PARITY_NONE
    UCSR0C &= ~(_BV(UPM00) | _BV(UPM01));
#elif CONFIG_IOE_USART_PARITY == USART_PARITY_ODD
    UCSR0C &= ~_BV(UPM00);
    UCSR0C |= _BV(UPM01);
#else // USART_PARITY_EVEN
    UCSR0C |= _BV(UPM00) | _BV(UPM01);
#endif

#if CONFIG_IOE_USART_STOPBIT == USART_STOPBIT_SINGLE
    UCSR0C &= ~_BV(USBS0);
#else
    UCSR0C |= _BV(USBS0);
#endif

#if CONFIG_IOE_USART_DATABITS == 5
    UCSR0C &= ~(_BV(UCSZ00) | _BV(UCSZ01));
#elif CONFIG_IOE_USART_DATABITS == 6
    UCSR0C &= ~_BV(UCSZ01);
    UCSR0C |= _BV(UCSZ00);
#elif CONFIG_IOE_USART_DATABITS == 7
    UCSR0C &= ~_BV(UCSZ00);
    UCSR0C |= _BV(UCSZ01);
#elif CONFIG_IOE_USART_DATABITS == 8
    UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);
#endif

    // Enable receiver, transmitter and RX complete,
    // Data register empty interrupts
    UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0) | _BV(UDRIE0);
#ifdef _IOE_USART_INBUFFER
    IOEBUFFER_INIT(_ioe_usart_inbuffer, CONFIG_IOE_USART_INBUFFER_SIZE);
#endif
#ifdef _IOE_USART_OUTBUFFER
    IOEBUFFER_INIT(_ioe_usart_outbuffer, CONFIG_IOE_USART_OUTBUFFER_SIZE);
#endif
}

inline void usart_send(uint8_t data) {
#ifdef _IOE_USART_OUTBUFFER
    if (!_usart_busy) {
        _usart_busy = 1;
        UDR0 = data;
    } else {
        IOEBUFFER_PUT(_ioe_usart_outbuffer,
                      CONFIG_IOE_USART_OUTBUFFER_SIZE, data,
                      CONFIG_IOE_USART_OUTBUFFER_MODE);
    }
#else
    _usart_busy = 1;
    UDR0 = data;
#endif /* _IOE_USART_OUTBUFFER */
}

#ifdef _IOE_USART_OUTBUFFER
void usart_send_str(char *str) {
    while (*str != '\0') {
        usart_send((uint8_t) * str);
        str++;
    }
}
#endif /* _IOE_USART_OUTBUFFER */

#ifdef _IOE_USART_INBUFFER
uint8_t usart_get(void) {
    uint8_t rtn;
    IOEBUFFER_GET(_ioe_usart_inbuffer, CONFIG_IOE_USART_INBUFFER_SIZE,
                  rtn);
    return rtn;
}
#endif

inline uint8_t usart_queryerror(void) {
    return UCSR0A & (_BV(FE0) | _BV(DOR0) | _BV(UPE0));
}

inline int8_t usart_busy(void) {
    return _usart_busy;
}

#ifdef _IOE_USART_INBUFFER
uint8_t usart_inbuffered(void) {
    uint8_t rtn;
    IOEBUFFER_CNT(_ioe_usart_inbuffer, CONFIG_IOE_USART_INBUFFER_SIZE,
                  rtn);
    return rtn;
}
#endif

#ifdef _IOE_USART_OUTBUFFER
uint8_t usart_outbuffered(void) {
    uint8_t rtn;
    IOEBUFFER_CNT(_ioe_usart_outbuffer, CONFIG_IOE_USART_OUTBUFFER_SIZE,
                  rtn);
    return rtn;
}
#endif

#ifdef CONFIG_IOE_USART_OUTFILE
static int usartput(char c, FILE * f) {
    usart_send((uint8_t) c);
    return 0;
}
#endif

#ifdef CONFIG_IOE_USART_INBUFFER
static int usartget(FILE * f) {
    uint8_t v;
    while (!(v = usart_get()));
    return v;
}
#endif

#if (defined CONFIG_IOE_USART_INFILE) || (defined CONFIG_IOE_USART_OUTFILE)
FILE *usart_async_open(void) {
    usart_init_async();
#ifdef CONFIG_IOE_USART_OUTFILE
#ifdef CONFIG_IOE_USART_INFILE
    return fdevopen(spiput, spiget);
#else
    return fdevopen(spiput, 0);
#endif
#else
    return fdevopen(0, spiget);
#endif
}
#endif

////// Interrupts ////////////////////////////////
void (*usart_receive) (uint8_t data) = 0;
void (*usart_sent) (void) = 0;

SIGNAL(USART_RX_vect) {
#ifdef _IOE_USART_INBUFFER
    uint8_t val = UDR0;
    IOEBUFFER_PUT(_ioe_usart_inbuffer, CONFIG_IOE_USART_INBUFFER_SIZE,
                  val, CONFIG_IOE_USART_INBUFFER_MODE);
#endif /* _IOE_USART_INBUFFER */
    if (usart_receive)
        usart_receive(UDR0);
}

SIGNAL(USART_UDRE_vect) {
#ifdef _IOE_USART_OUTBUFFER
    uint8_t val;
    IOEBUFFER_GET(_ioe_usart_outbuffer, CONFIG_IOE_USART_OUTBUFFER_SIZE,
                  val);
    if (val)
        UDR0 = val;
    else
        _usart_busy = 0;
#else
    _usart_busy = 0;
#endif /* _IOE_USART_OUTBUFFER */
    if (usart_sent)
        usart_sent();
}

#endif
