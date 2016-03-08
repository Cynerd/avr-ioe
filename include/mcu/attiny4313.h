/* This is specific configuration for ATtiny4313.
 * This configuration also applies on ATtiny2313A.
 */
#include <avr/io.h>

// IO Ports
#define MCUSUPPORT_IOPORTS
#define IO_A 0
#define IO_B 1
#define IO_D 3
#define IO_PIN(GROUP)  (* (volatile uint8_t *)(PINB + 0x3*GROUP))
#define IO_DDR(GROUP)  (* (volatile uint8_t *)(DDRB + 0x3*GROUP))
#define IO_PORT(GROUP) (* (volatile uint8_t *)(PORTB + 0x3*GROUP))
#define IO_A0 IO_A, (1 << 0)
#define IO_A1 IO_A, (1 << 1)
#define IO_A2 IO_A, (1 << 2)
#define IO_B0 IO_B, (1 << 0)
#define IO_B1 IO_B, (1 << 1)
#define IO_B2 IO_B, (1 << 2)
#define IO_B3 IO_B, (1 << 3)
#define IO_B4 IO_B, (1 << 4)
#define IO_B5 IO_B, (1 << 5)
#define IO_B6 IO_B, (1 << 6)
#define IO_B7 IO_B, (1 << 7)
#define IO_D0 IO_D, (1 << 0)
#define IO_D1 IO_D, (1 << 1)
#define IO_D2 IO_D, (1 << 2)
#define IO_D3 IO_D, (1 << 3)
#define IO_D4 IO_D, (1 << 4)
#define IO_D5 IO_D, (1 << 5)
#define IO_D6 IO_D, (1 << 6)
#define MCUSUPPORT_PCINT0 8 // TODO this is B
#define MCUSUPPORT_PCINT1 7 // But this is D
#define MCUSUPPORT_PCINT2 3 // And this is A, this is not expected in ioport.c
// SPI USI
#define MCUSUPPORT_USI
#define DDR_USI     DDRB
#define DD_DI       DDB5
#define DD_DO       DDB6
#define DD_USCK     DDB7
#define PORT_USI    PORTB
#define PORT_DI     PORTB5
#define PORT_DO     PORTB6
#define PORT_USCK   PORTB7
// USART
#define MCUSUPPORT_USART0
