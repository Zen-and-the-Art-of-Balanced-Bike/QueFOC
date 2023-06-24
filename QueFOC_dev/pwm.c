//
// Created by 24216 on 2022/12/23.
//

#include "pwm.h"
#include <string.h>

/*!
 * Initialize a PWM output object
 * @param freq                      PWM frequency       [Hz]
 * @param hardware_boot             Hardware specific
 * @param hardware_enable_pwm       Hardware specific
 * @param hardware_set_ch_a_duty    Hardware specific
 * @param hardware_set_ch_b_duty    Hardware specific
 * @param hardware_set_ch_c_duty    Hardware specific
 */
void pwm_init(PWM* pwm,
              uint32_t freq,
              void (* hardware_boot)(void),
              void (* hardware_set_ch_a_duty)(float),
              void (* hardware_set_ch_b_duty)(float),
              void (* hardware_set_ch_c_duty)(float)) {
    memset(pwm, 0, sizeof(PWM));
    pwm->freq                    =   freq;
    pwm->duty_a                  =   0;
    pwm->duty_b                  =   0;
    pwm->duty_c                  =   0;
    pwm->hardware_boot           =   hardware_boot;
    pwm->hardware_set_ch_a_duty  =   hardware_set_ch_a_duty;
    pwm->hardware_set_ch_b_duty  =   hardware_set_ch_b_duty;
    pwm->hardware_set_ch_c_duty  =   hardware_set_ch_c_duty;
}

void pwm_boot(PWM* pwm){
    pwm->hardware_boot();
    pwm_apply_duty(pwm, 0, 0, 0);
}

void pwm_apply_duty(PWM* pwm, float duty_a, float duty_b, float duty_c){
    pwm->duty_a = duty_a;
    pwm->duty_b = duty_b;
    pwm->duty_c = duty_c;
    pwm->hardware_set_ch_a_duty(duty_a);
    pwm->hardware_set_ch_b_duty(duty_b);
    pwm->hardware_set_ch_c_duty(duty_c);
}

void pwm_sync_duty(PWM* pwm){
    pwm->hardware_set_ch_a_duty(pwm->duty_a);
    pwm->hardware_set_ch_b_duty(pwm->duty_b);
    pwm->hardware_set_ch_c_duty(pwm->duty_c);
}
