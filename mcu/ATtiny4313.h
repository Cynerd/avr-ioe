/* This is specific configuration for ATtiny4313.
 * This configuration also applies on ATtiny2313A.
 */
#include <avr/io.h>

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
