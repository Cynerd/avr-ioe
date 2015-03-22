/* This is specific configuration for ATtiny85.
 * This configuration also applies on ATtiny45 and ATtiny25.
 */
#include <avr/io.h>

// SPI USI
#define DDR_USI     DDRB
#define DD_DI       DDB0
#define DD_DO       DDB1
#define DD_USCK     DDB2
#define PORT_USI    PORTB
#define PORT_DI     PORTB0
#define PORT_DO     PORTB1
#define PORT_USCK   PORTB2
