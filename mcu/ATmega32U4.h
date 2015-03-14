/* This is specific configuration for ATmega32U4.
 * This configuration also applies on ATmega16U4.
 */
#include <avr/io.h>

#define DDR_SPI DDRB
#define DD_SS   DDB0
#define DD_MOSI DDB2
#define DD_MISO DDB3
#define DD_SCLK  DDB5
