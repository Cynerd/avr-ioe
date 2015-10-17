#include "../timer.h"

#ifdef CONFIG_IOE_TIMERS

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
