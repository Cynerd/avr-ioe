/*! \defgroup gpio GPIO
 * \brief General-purpose input/output
 *
 * This module defines macros for input/output pins of microcontroller.
 * Pin is specified with SET and PIN. SET is letter and PIN is number. Combination
 * of SET and PIN specifies hardware pin. You can find it in documentation.
 *
 * To use this module:
 *
 *     #include "avr-ioe/GPIO.h"
 */
#include <avr/io.h>
#include <stdint.h>

#ifdef IOE_CONFIG
#include <AVR-IOE-CONFIG.h>
#endif /* IOE_CONFIG */

#ifndef _IOE_GPIO_H_
#define _IOE_GPIO_H_

#define __GPIO_JOIN2(TXT1, TXT2) TXT1##TXT2
#define __GPIO_JOIN3(TXT1, TXT2, TXT3) TXT1##TXT2##TXT3

/*! \ingroup gpio
 * Return direction of specified pin. Pin is set as output if value is nonzero
 * and as input if returned value is zero.
 */
#define gpio_get_mode(SET, PIN)                                                 \
    __GPIO_JOIN2(DDR, SET) & _BV(__GPIO_JOIN3(DD, SET, PIN))

/*! \ingroup gpio
 * Set specified pin as output.
 * \param SET -- pin set (letter)
 * \param PIN -- pin number (number)
 */
#define gpio_set_out(SET, PIN)                                                  \
    __GPIO_JOIN2(DDR, SET) |= _BV(__GPIO_JOIN3(DD, SET, PIN))

/*! \ingroup gpio
 * Set specific pin as input.
 * \param SET -- pin set (letter)
 * \param PIN -- pin number (number)
 */
#define gpio_set_in(SET, PIN)                                                   \
    __GPIO_JOIN2(DDR, SET) &= ~_BV(__GPIO_JOIN3(DD, SET, PIN))

// -- GPIO output section --
/*! \defgroup gpio_out GPIO output
 * \ingroup gpio
 */
/*! \ingroup gpio_out
 * Set pin high. Pin must be set as output. Undefined behavior for non
 * output pins.
 * \param SET -- pin set (letter)
 * \param PIN -- pin number (number)
 */
#define gpio_set_high(SET, PIN)                                                 \
    __GPIO_JOIN2(PORT, SET) |= _BV(__GPIO_JOIN3(PORT, SET, PIN))

/*! \ingroup gpio_out
 * Set pin low. Pin must be set as output. Undefined behavior for non output pins.
 * \param SET -- pin set (letter)
 * \param PIN -- pin number (number)
 */
#define gpio_set_low(SET, PIN)                                                  \
    __GPIO_JOIN2(PORT, SET) &= ~_BV(__GPIO_JOIN3(PORT, SET, PIN))

/*! \ingroup gpio_out
 * Set pin according to \a VALUE. Pin must be set as output. Undefined behavior
 * for non output pins.
 * \warning Use this only if VALUE is runtime variable. For constants are prefered
 * gpio_set_high() and gpio_set_low().
 * \param SET -- pin set (letter)
 * \param PIN -- pin number (number)
 * \param VALUE -- runtime variable or boolean expression used in boolean context.
 */
#define gpio_set(SET, PIN, VALUE)                                               \
    if (VALUE)                                                                  \
        gpio_set_high(SET, PIN);                                                \
    else                                                                        \
        gpio_set_low(SET, PIN);

/*! \ingroup gpio_out
 * Set pin opposite state. If it is set as high it will be low and if it is set
 * as low it will be high. Pin must be set as output. Undefined behavior for non
 * output pins.
 * \param SET -- pin set (letter)
 * \param PIN -- pin number (number)
 */
#define gpio_set_not(SET, PIN)                                                  \
    __GPIO_JOIN2(PORT, SET) ^= _BV(__GPIO_JOIN3(PORT, SET, PIN))

// -- GPIO input section --
/*! \defgroup gpio_in GPIO input
 * \ingroup gpio
 */
// TODO whole output and switching betwen input and output

#endif /* _IOE_GPIO_H_ */
