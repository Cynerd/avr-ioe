// vim:ts=4:sw=4:sts=4:expandtab
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#ifndef _IOE_ADC_H_
#define _IOE_ADC_H_
#ifdef CONFIG_IOE_ADC
#ifndef MCUSUPPORT_ADC
#error "No ADC support for your mcu. Probably just not implemented yet."
#endif

int8_t ioe_adc(uint8_t input);

#endif /* CONFIG_IOE_ADC */
#endif /* _IOE_ADC_H_ */
