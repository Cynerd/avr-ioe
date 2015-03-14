/* This is specific configuration for ATtiny85.
 * This configuration also applies on ATtiny45 and ATtiny25.
 */
#include <avr/io.h>

#define USI_DIR_REG     DDRB
#define USI_OUT_REG     PORTB
#define USI_IN_REG      PINB
#define USI_USCK_PIN    PORTB2
#define USI_DO_PIN      PORTB1
#define USI_DI_PIN      PORTB0
