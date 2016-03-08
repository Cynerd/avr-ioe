/* This is specific configuration for ATmega328P.
 * Also applies on ATmega48A, ATmega48PA, ATmega88A, ATmega88PA, ATmega168A and
 * ATmega168PA.
 */
#include <avr/io.h>

// IO Ports
#define MCUSUPPORT_IOPORTS
#define IO_B 0
#define IO_C 1
#define IO_D 2
#define IO_PIN(GROUP)  (* (volatile uint8_t *)(PINB + 0x3*GROUP))
#define IO_DDR(GROUP)  (* (volatile uint8_t *)(DDRB + 0x3*GROUP))
#define IO_PORT(GROUP) (* (volatile uint8_t *)(PORTB + 0x3*GROUP))
#define IO_B0 IO_B, (1 << 0)
#define IO_B1 IO_B, (1 << 1)
#define IO_B2 IO_B, (1 << 2)
#define IO_B3 IO_B, (1 << 3)
#define IO_B4 IO_B, (1 << 4)
#define IO_B5 IO_B, (1 << 5)
#define IO_B6 IO_B, (1 << 6)
#define IO_B7 IO_B, (1 << 7)
#define IO_C0 IO_C, (1 << 0)
#define IO_C1 IO_C, (1 << 1)
#define IO_C2 IO_C, (1 << 2)
#define IO_C3 IO_C, (1 << 3)
#define IO_C4 IO_C, (1 << 4)
#define IO_C5 IO_C, (1 << 5)
#define IO_C6 IO_C, (1 << 6)
#define IO_D0 IO_D, (1 << 0)
#define IO_D1 IO_D, (1 << 1)
#define IO_D2 IO_D, (1 << 2)
#define IO_D3 IO_D, (1 << 3)
#define IO_D4 IO_D, (1 << 4)
#define IO_D5 IO_D, (1 << 5)
#define IO_D6 IO_D, (1 << 6)
#define IO_D7 IO_D, (1 << 7)
#define MCUSUPPORT_PCINT0 8
#define MCUSUPPORT_PCINT1 8
#define MCUSUPPORT_PCINT2 8
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
// TWI
#define MCUSUPPORT_TWI
// TIMERS
#define MCUSUPPORT_TIMER_0
#define MCUSUPPORT_TIMER_1
#define MCUSUPPORT_TIMER_2
#define COUNTER0_PWM 0
#define COUNTER1_16PWM 1
#define COUNTER2_PWM_ASYNC 2
