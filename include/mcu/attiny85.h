/* This is specific configuration for ATtiny85.
 * This configuration also applies on ATtiny45 and ATtiny25.
 */
#include <avr/io.h>

// IO Ports
#define MCUSUPPORT_IOPORTS
#define IO_B 0
#define IO_PIN(GROUP)  PINB
#define IO_DDR(GROUP)  DDRB
#define IO_PORT(GROUP) PORTB
#define IO_B0 IO_B, (1 << 0)
#define IO_B1 IO_B, (1 << 1)
#define IO_B2 IO_B, (1 << 2)
#define IO_B3 IO_B, (1 << 3)
#define IO_B4 IO_B, (1 << 4)
#define IO_B5 IO_B, (1 << 5)
#define MCUSUPPORT_PCINT0 6
// SPI USI
#define MCUSUPPORT_USI
#define DDR_USI     DDRB
#define DD_DI       DDB0
#define DD_DO       DDB1
#define DD_USCK     DDB2
#define PORT_USI    PORTB
#define PORT_DI     PORTB0
#define PORT_DO     PORTB1
#define PORT_USCK   PORTB2
