/* This is specific configuration for ATmega328P.
 * Also applies on ATmega48A, ATmega48PA, ATmega88A, ATmega88PA, ATmega168A and
 * ATmega168PA.
 */
#include <avr/io.h>

// SPI
#define MCUSUPPORT_SPI
#define DDR_SPI     DDRB
#define DD_SS       DDB2
#define DD_MOSI     DDB3
#define DD_MISO     DDB4
#define DD_SCLK     DDB5
#define PORT_SPI    PORTB
#define PORT_SS     PORTB2
#define PORT_MOSI   PORTB3
#define PORT_MISO   PORTB4
#define PORT_SCLK   PORTB5
// USART
#define MCUSUPPORT_USART
