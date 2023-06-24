//
// Created by 24216 on 2022/12/23.
//

#ifndef QUEFOC_DEV_PWM_H
#define QUEFOC_DEV_PWM_H

// #define PWM_FREQUENCY 20000

#include "inttypes.h"

/*! @brief PWM Output Object */
typedef struct {
    // PWM frequency [Hz]
    uint32_t freq;
    // PWM duty
    float duty_a, duty_b, duty_c;

    /* Hardware specific */
    void (*hardware_boot)(void);
    void (*hardware_set_ch_a_duty)(float duty);
    void (*hardware_set_ch_b_duty)(float duty);
    void (*hardware_set_ch_c_duty)(float duty);
} PWM;

void pwm_init(PWM* pwm,
              uint32_t freq,
              void (* hardware_boot)(void),
              void (* hardware_set_ch_a_duty)(float),
              void (* hardware_set_ch_b_duty)(float),
              void (* hardware_set_ch_c_duty)(float));


void pwm_boot(PWM* pwm);
void pwm_apply_duty(PWM* pwm, float duty_a, float duty_b, float duty_c);
void pwm_sync_duty(PWM* pwm);


#endif //QUEFOC_DEV_PWM_H
