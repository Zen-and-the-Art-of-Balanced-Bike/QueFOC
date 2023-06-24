#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fast_math.h"
#include "foc.h"
#include "motor.h"

/*!
 * @brief This file contains tests
 *
 */
#define TEST_CNT 1000

void test_sin_cos(){
    puts("TEST SIN_FAST AND COS_FAST");
    srand(time(NULL));
    for(int i=0;i<TEST_CNT;++i){
        double t = ((double)rand()/RAND_MAX)*4.0*M_PI-2*M_PI;
        //printf("%f\n", t);
        float eps = 0.002f;
        float e_sin = sin(t)-fast_sin(t), e_cos = cos(t)-fast_cos(t);
        if(ABS(e_sin)>eps)
            puts("[FAIL]");
        if(ABS(e_cos)>eps)
            puts("[FAIL]");
    }
    puts("[DONE]");
}

void test_foc(){
    puts("TEST FOC ALGORITHM");
    Motor motor={0};
    ADC_sensor adcSensor={0};
    PWM pwm={0};
    float vbus = fast_sqrt(2);
    adcSensor.v_bus = vbus;
    motor.adc = &adcSensor;
    motor.pwm = &pwm;
    float ta, tb, tc;
    // (1, 0) -> 0,1,1
    foc_modulation_svm(1, 0, &ta, &tb, &tc);
    printf("%f %f %f\n", ta, tb, tc);
    // (1/2, sqrt(3)/2) -> 0,0,1
    foc_modulation_svm(0.5f, 0.5f*fast_sqrt(3), &ta, &tb, &tc);
    printf("%f %f %f\n", ta, tb, tc);
    // (-1/2, sqrt(3)/2) -> 1,0,1
    foc_modulation_svm(-0.5f, 0.5f*fast_sqrt(3), &ta, &tb, &tc);
    printf("%f %f %f\n", ta, tb, tc);
    // (-1, 0) -> 1,0,0
    foc_modulation_svm(-1, 0, &ta, &tb, &tc);
    printf("%f %f %f\n", ta, tb, tc);


    foc_voltage_control(&motor, VBUS_TO_VPHASE_MAX(vbus), 0, 0);
    printf("%f %f %f\n", pwm.duty_a, pwm.duty_b, pwm.duty_c);
    foc_alpha_beta_vec_control(&motor, MAX_MODULATION_SCALE, 0);
    printf("%f %f %f\n", pwm.duty_a, pwm.duty_b, pwm.duty_c);

    foc_voltage_control(&motor, 0, -VBUS_TO_VPHASE_MAX(vbus), 0);
    printf("%f %f %f\n", pwm.duty_a, pwm.duty_b, pwm.duty_c);
    foc_alpha_beta_vec_control(&motor, MAX_MODULATION_SCALE, ANG2RAD(270));
    printf("%f %f %f\n", pwm.duty_a, pwm.duty_b, pwm.duty_c);
    foc_d_q_vec_control(&motor, MAX_MODULATION_SCALE, 0, ANG2RAD(270));
    printf("%f %f %f\n", pwm.duty_a, pwm.duty_b, pwm.duty_c);

    // 0
    foc_d_q_vec_control(&motor, MAX_MODULATION_SCALE, 0, ANG2RAD(0));
    printf("%f %f %f\n", pwm.duty_a, pwm.duty_b, pwm.duty_c);
    // 60
    foc_d_q_vec_control(&motor, MAX_MODULATION_SCALE, 0, ANG2RAD(60));
    printf("%f %f %f\n", pwm.duty_a, pwm.duty_b, pwm.duty_c);
    // 240
    foc_d_q_vec_control(&motor, MAX_MODULATION_SCALE, 0, ANG2RAD(240));
    printf("%f %f %f\n", pwm.duty_a, pwm.duty_b, pwm.duty_c);

}

int main() {
    printf("START TEST\n");
    test_sin_cos();
    test_foc();
    return 0;
}
