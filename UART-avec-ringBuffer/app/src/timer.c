#include "timer.h"
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>

#define PRESCALER (84)
// 84_000_000 MHz
#define ARR_VALUE (1000)

// remember to setup your GPIO output in alternate function mode
void timer_setup() {
    rcc_periph_clock_enable(RCC_TIM2);  // enable rcc clock peripheral on TIM2
    // edge alignment chosen, CMS = center-aligned mode selection
    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    // setup PWM mode
    timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);
    // enable counter, after you setup in timer_set_mode
    timer_enable_counter(TIM2);
    // enable output compare, after setup in timer_set_oc_mode
    timer_enable_oc_output(TIM2, TIM_OC1);

    // setup frequency and how many points do you need in the step of PWM?
    // need requirements or specification, 1000 Hz let's say and 1000 division
    // freq = system_freq / ((prescaler-1) * (arr-1))
    // in our case : 84 Mhz / (84 * 1000) = 1000 Hz or steps in PWM
    timer_set_prescaler(TIM2, PRESCALER - 1);
    // set the period = auto reload register
    timer_set_period(TIM2, ARR_VALUE - 1);
}

void timer_pwm_set_duty_cycle(float duty_cycle) {
    // duty_cycle = (ccr / arr) * 100
    // ccr = (duty_cycle * arr) / 100

    const float raw_value = (float) ARR_VALUE * (duty_cycle / 100.0f);
    timer_set_oc_value(TIM2, TIM_OC1, (uint32_t) raw_value);
}
