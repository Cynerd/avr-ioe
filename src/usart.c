#include "../usart.h"

#ifdef MCUSUPPORT_USART

volatile int8_t _usart_busy;

inline void usart_init_uart(void) {
    usart_init_async(USART_BAUDRATE_115200, USART_PARITY_NONE,
                     USART_STOPBIT_SINGLE, USART_DATABITS_8);
}

void usart_init_async(enum usartBaudrate baudrate,
                      enum usartParity parity, enum usartStopBit stopbit,
                      enum usartDataBits databits) {
    _usart_busy = 0;
    switch (baudrate) {
    case USART_BAUDRATE_2400:
#define BAUD 2400
#include "usart_baundrate_helper.h"
        break;
    case USART_BAUDRATE_4800:
#define BAUD 4800
#include "usart_baundrate_helper.h"
        break;
    case USART_BAUDRATE_9600:
#define BAUD 9600
#include "usart_baundrate_helper.h"
        break;
    case USART_BAUDRATE_19200:
#define BAUD 19200
#include "usart_baundrate_helper.h"
        break;
    case USART_BAUDRATE_38400:
#define BAUD 38400
#include "usart_baundrate_helper.h"
        break;
    case USART_BAUDRATE_57600:
#define BAUD 57600
#include "usart_baundrate_helper.h"
        break;
    case USART_BAUDRATE_115200:
#define BAUD 115200
#include "usart_baundrate_helper.h"
        break;
    }
    switch (parity) {
    case USART_PARITY_NONE:
        UCSR0C &= ~(_BV(UPM00) | _BV(UPM01));
        break;
    case USART_PARITY_ODD:
        UCSR0C &= ~_BV(UPM00);
        UCSR0C |= _BV(UPM01);
        break;
    case USART_PARITY_EVEN:
        UCSR0C |= _BV(UPM00) | _BV(UPM01);
        break;
    }
    switch (stopbit) {
    case USART_STOPBIT_SINGLE:
        UCSR0C &= ~_BV(USBS0);
        break;
    case USART_STOPBIT_DOUBLE:
        UCSR0C |= _BV(USBS0);
        break;
    }
    switch (databits) {
    case USART_DATABITS_5:
        UCSR0C &= ~(_BV(UCSZ00) | _BV(UCSZ01));
        break;
    case USART_DATABITS_6:
        UCSR0C &= ~_BV(UCSZ01);
        UCSR0C |= _BV(UCSZ00);
        break;
    case USART_DATABITS_7:
        UCSR0C &= ~_BV(UCSZ00);
        UCSR0C |= _BV(UCSZ01);
        break;
    case USART_DATABITS_8:
        UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);
        break;
    }
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
    uint8_t rtn = 0;
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
