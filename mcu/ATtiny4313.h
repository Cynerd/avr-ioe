/* This is specific configuration for ATtiny4313.
 * This configuration also applies on ATtiny2313A.
 */
#include <avr/io.h>

#define USI_DIR_REG     DDRB
#define USI_OUT_REG     PORTB
#define USI_IN_REG      PINB
#define USI_USCK_PIN    PORTB7
#define USI_DO_PIN      PORTB6
#define USI_DI_PIN      PORTB5
