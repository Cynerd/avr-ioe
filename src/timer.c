#include <timer.h>
#ifdef CONFIG_IOE_TIMERS

void timer_init(uint8_t timer, enum timerDivider div) {
	switch (timer) {
#ifdef COUNTER0_PWM
	case COUNTER0_PWM:
		// Null counting register
		TCNT0 = 0;
		// Set interrupt flag
		TIMSK0 = _BV(TOIE0);
		// Set division and start counting
		switch (div) {
			case TIMER_DIVIDER_1:
				TCCR0B = _BV(CS00);
				break;
			case TIMER_DIVIDER_8:
				TCCR0B = _BV(CS01);
				break;
			case TIMER_DIVIDER_64:
				TCCR0B = _BV(CS01) | _BV(CS00);
				break;
			case TIMER_DIVIDER_256:
				TCCR0B = _BV(CS02);
				break;
			case TIMER_DIVIDER_1024:
				TCCR0B = _BV(CS02) | _BV(CS01);
				break;
			default:
				return;
		}
		break;
#endif /* COUNTER0_PWM */
#ifdef COUNTER1_16PWM
	case COUNTER1_16PWM:
		break;
#endif /* COUNTER1_16PWM */
#ifdef COUNTER2_PWM_ASYNC
	case COUNTER2_PWM_ASYNC:
		break;
#endif /* COUNTER2_PWM_ASYNC */
	}
}

void timer_disable(uint8_t timer) {
	switch (timer) {
#ifdef COUNTER0_PWM
	case COUNTER0_PWM:
		TCCR0B = 0;
		break;
#endif /* COUNTER0_PWM */
#ifdef COUNTER1_16PWM
	case COUNTER1_16PWM:
		break;
#endif /* COUNTER1_16PWM */
#ifdef COUNTER2_PWM_ASYNC
	case COUNTER2_PWM_ASYNC:
		break;
#endif /* COUNTER2_PWM_ASYNC */
	}
}

void timer_reset(uint8_t timer) {
	switch (timer) {
#ifdef COUNTER0_PWM
	case COUNTER0_PWM:
		TCNT0 = 0;
		break;
#endif /* COUNTER0_PWM */
#ifdef COUNTER1_16PWM
	case COUNTER1_16PWM:
		break;
#endif /* COUNTER1_16PWM */
#ifdef COUNTER2_PWM_ASYNC
	case COUNTER2_PWM_ASYNC:
		break;
#endif /* COUNTER2_PWM_ASYNC */
	}
}

uint16_t timer_value(uint8_t timer) {
	switch (timer) {
#ifdef COUNTER0_PWM
	case COUNTER0_PWM:
		return TCNT0;
		break;
#endif /* COUNTER0_PWM */
#ifdef COUNTER1_16PWM
	case COUNTER1_16PWM:
		break;
#endif /* COUNTER1_16PWM */
#ifdef COUNTER2_PWM_ASYNC
	case COUNTER2_PWM_ASYNC:
		break;
#endif /* COUNTER2_PWM_ASYNC */
	default:
		return 0;
	}
}

#ifdef COUNTER0_PWM
static void *(*timer_0_pwm_overflow) (void);
#endif /* COUNTER0_PWM */
#ifdef COUNTER1_16PWM
static void (*timer_1_16pwm_overflow) (void);
#endif /* COUNTER1_16PWM */
#ifdef COUNTER2_PWM_ASYNC
static void (*timer_2_pwm_overflow) (void);
#endif /* COUNTER2_PWM_ASYNC */

void timer_sethook(uint8_t timer, void (*fnc) (void)) {
	switch (timer) {
#ifdef COUNTER0_PWM
	case COUNTER0_PWM:
		timer_0_pwm_overflow = fnc;
		break;
#endif /* COUNTER0_PWM */
#ifdef COUNTER1_16PWM
	case COUNTER1_16PWM:
		timer_1_16pwm_overflow = fnc;
		break;
#endif /* COUNTER1_16PWM */
#ifdef COUNTER2_PWM_ASYNC
	case COUNTER2_PWM_ASYNC:
		timer_2_pwm_overflow = fnc;
		break;
#endif /* COUNTER2_PWM_ASYNC */
	}
}

#ifdef COUNTER0_PWM
ISR(TIMER0_OVF_vect, ISR_BLOCK) {
	if (timer_0_pwm_overflow)
	timer_0_pwm_overflow();
}
#endif /* COUNTER0_PWM */

#ifdef COUNTER0_PWM
ISR(TIMER1_OVF_vect, ISR_BLOCK) {
	if (timer_1_16pwm_overflow)
	timer_1_16pwm_overflow();
}
#endif /* COUNTER0_PWM */

#ifdef COUNTER0_PWM
ISR(TIMER2_OVF_vect, ISR_BLOCK) {
	if (timer_2_pwm_overflow)
	timer_2_pwm_overflow();
}
#endif /* COUNTER0_PWM */

#endif /* CONFIG_IOE_TIMERS */
