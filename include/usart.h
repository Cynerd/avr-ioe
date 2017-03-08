#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>

#include "mcu/mcu_def.h"
#include "utils/buffer.h"

#ifndef _USART_H_
#define _USART_H_
#ifdef CONFIG_USART

// TODO clock polarity and synchronous mode

#define USART_FRAMEERROR  _BV(FE0)
#define USART_DATAOVERRUN _BV(DOR0)
#define USART_PARITYERROR _BV(UPE0)

#ifdef CONFIG_USART_INPUT_BUFFER
volatile IOEBUFFER(uint8_t, _ioe_usart_inbuffer, CONFIG_USART_INBUFFER_SIZE);
#endif
#ifdef CONFIG_USART_OUTPUT_BUFFER
volatile IOEBUFFER(uint8_t, _ioe_usart_outbuffer, CONFIG_USART_OUTBUFFER_SIZE);
#endif

extern volatile int8_t _usart_busy;


/*
 * Initialize USART device.
 */
void usart_init_async(void);
void usart_send(uint8_t data);
#ifdef CONFIG_USART_OUTPUT_BUFFER
void usart_send_str(char *str);
#endif
#ifdef CONFIG_USART_INPUT_BUFFER
uint8_t usart_get(void);
#endif
static inline uint8_t usart_queryerror(void) {
	return UCSR0A & (_BV(FE0) | _BV(DOR0) | _BV(UPE0));
}
static inline int8_t usart_busy(void) {
	return _usart_busy;
}
#ifdef CONFIG_USART_INPUT_BUFFER
uint8_t usart_inbuffered(void);
#endif
#ifdef CONFIG_USART_OUTPUT_BUFFER
uint8_t usart_outbuffered(void);
#endif
#if (defined CONFIG_USART_INFILE) || (defined CONFIG_USART_OUTFILE)
FILE *usart_async_open(void);
#endif

// Following function must be user defined if relevant buffers not used.
extern void (*usart_receive)(uint8_t data);
extern void (*usart_sent)(void);

#endif /* CONFIG_USART */
#endif /* _USART_H_ */
