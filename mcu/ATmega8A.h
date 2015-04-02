/* This is specific configuration for ATmega8A.
 */
#include <avr/io.h>

// SPI
#define DDR_SPI     DDRB
#define DD_SS       DDB2
#define DD_SCLK     DDB5
#define DD_MOSI     DDB3
#define DD_MISO     DDB4
#define PORT_SPI    PORTB
#define PORT_SS     PORTB2
#define PORT_SCLK   PORTB5
#define PORT_MOSI   PORTB3
#define PORT_MISO   PORTB4
