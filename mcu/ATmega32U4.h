/* This is specific configuration for ATmega32U4.
 * This configuration also applies on ATmega16U4.
 */
#include <avr/io.h>

// SPI
#define MCUSUPPORT_SPI
#define DDR_SPI     DDRB
#define DD_SS       DDB0
#define DD_SCLK     DDB1
#define DD_MOSI     DDB2
#define DD_MISO     DDB3
#define PORT_SPI    PORTB
#define PORT_SS     PORTB0
#define PORT_SCLK   PORTB1
#define PORT_MOSI   PORTB2
#define PORT_MISO   PORTB3
// USART
#define MCUSUPPORT_USART0
