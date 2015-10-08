#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "mcu/mcu_def.h"
#include "buffers.h"

#ifndef _IOE_USART_H_
#define _IOE_USART_H_

#ifndef MCUSUPPORT_USART
#error "No USART interface is known on your mcu."
#endif

enum usartBaudrate {
    USART_BAUDRATE_2400,
    USART_BAUDRATE_4800,
    USART_BAUDRATE_9600,
    USART_BAUDRATE_19200,
    USART_BAUDRATE_38400,
    USART_BAUDRATE_57600,
    USART_BAUDRATE_115200
};

enum usartParity {
    USART_PARITY_NONE,
    USART_PARITY_ODD,
    USART_PARITY_EVEN
};

enum usartStopBit {
    USART_STOPBIT_SINGLE = 1,
    USART_STOPBIT_DOUBLE = 2
};

enum usartDataBits {
    USART_DATABITS_5 = 5,
    USART_DATABITS_6 = 6,
    USART_DATABITS_7 = 7,
    USART_DATABITS_8 = 8,
    // USART_DATABITS_9 = 9 // Not supported yet
};

// Not supported yet. This is for synchronous mode only
//enum usartClockPolarity {
    //USART_CLOCKPOLARITY_FALLING,
    //USART_CLOCKPOLARITY_RISING
//};

#define USART_FRAMEERROR  _BV(FE0)
#define USART_DATAOVERRUN _BV(DOR0)
#define USART_PARITYERROR _BV(UPE0)

#if CONFIG_IOE_USART_INBUFFER_SIZE > 0
#define _IOE_USART_INBUFFER
volatile IOEBUFFER(_ioe_usart_inbuffer, CONFIG_IOE_USART_INBUFFER_SIZE);
#endif
#if CONFIG_IOE_USART_OUTBUFFER_SIZE > 0
#define _IOE_USART_OUTBUFFER
volatile IOEBUFFER(_ioe_usart_outbuffer, CONFIG_IOE_USART_OUTBUFFER_SIZE);
#endif


/*
 * Initialize USART device with 115200 baud rate, no parity, single stop bit,
 * and 8 data bits.
 * This function serves as fast default initialization.
 */
void usart_init_uart(void);
void usart_init_async(enum usartBaudrate,
                      enum usartParity, enum usartStopBit,
                      enum usartDataBits);
void usart_send(uint8_t data);
#ifdef _IOE_USART_OUTBUFFER
void usart_send_str(char *str);
#endif
#ifdef _IOE_USART_INBUFFER
uint8_t usart_get(void);
#endif
uint8_t usart_queryerror(void);
int8_t usart_busy(void);
#ifdef _IOE_USART_INBUFFER
uint8_t usart_inbuffered(void);
#endif
#ifdef _IOE_USART_OUTBUFFER
uint8_t usart_outbuffered(void);
#endif

// Following function must be user defined if relevant buffers not used.
extern void (*usart_receive)(uint8_t data);
extern void (*usart_sent)(void);

#endif /* _IOE_USART_H_ */
