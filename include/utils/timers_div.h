#ifndef _IOE_TIMER_H_
#error Please include time.h before timers_div.h
#endif

#ifndef TIMER_DIV_RESTIME
#error Please define minimal time (us) before include timers_div.h in TIMER_DIV_RESTIME
#endif

// Calculate optimal division
#define _TD_OPTIMAL (TIMER_DIV_RESTIME * F_CPU/1000000L)

// Set minimal and maximal division closest to optimal
#if _TD_OPTIMAL < 8
#define _TD_MIN 1
#define _TD_MAX 8
#elif _TD_OPTIMAL < 64
#define _TD_MIN 8
#define _TD_MAX 64
#elif _TD_OPTIMAL < 256
#define _TD_MIN 64
#define _TD_MAX 256
#elif _TD_OPTIMAL < 1024
#define _TD_MIN 256
#define _TD_MAX 1024
#else
#define _TD_MIN 1024
#define _TD_MAX 1024
#endif

// Calculate time difference between required time and got time resolution
#define _TD_MIN_TIME (TIMER_DIV_RESTIME - (_TD_MIN * 1000000L / F_CPU))
#define _TD_MAX_TIME (TIMER_DIV_RESTIME - (_TD_MAX * 1000000L / F_CPU))

// Do absolute value of calculated numbers
#if _TD_MIN_TIME < 0
#define _TD_MIN_TIMEF (_TD_MIN_TIME * -1)
#else
#define _TD_MIN_TIMEF _TD_MIN_TIME
#endif
#if _TD_MAX_TIME < 0
#define _TD_MAX_TIMEF (_TD_MAX_TIME * -1)
#else
#define _TD_MAX_TIMEF _TD_MAX_TIME
#endif

// Select closest one
#if _TD_MIN_TIMEF < _TD_MAX_TIMEF
#define _TD_TIMER_DIV _TD_MIN
#else
#define _TD_TIMER_DIV _TD_MAX
#endif

// Set macro to enum value
#if _TD_TIMER_DIV == 1
#define TIMER_DIV TIMER_DIVIDER_1
#elif _TD_TIMER_DIV == 8
#define TIMER_DIV TIMER_DIVIDER_8
#elif _TD_TIMER_DIV == 64
#define TIMER_DIV TIMER_DIVIDER_64
#elif _TD_TIMER_DIV == 256
#define TIMER_DIV TIMER_DIVIDER_256
#elif _TD_TIMER_DIV == 1024
#define TIMER_DIV TIMER_DIVIDER_1024
#else
#error Generated unknown timer division. Something is wrong with timers_div.h
#endif

// Undefine all used variables
#undef _TD_OPTIMAL
#undef _TD_MIN
#undef _TD_MAX
#undef _TD_MIN_TIME
#undef _TD_MAX_TIME
#undef _TD_MIN_TIMEF
#undef _TD_MAX_TIMEF
#undef _TD_TIMER_DIV
