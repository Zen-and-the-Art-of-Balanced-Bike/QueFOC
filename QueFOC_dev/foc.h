//
// Created by 24216 on 2022/12/21.
//

#ifndef QUEFOC_DEV_FOC_H
#define QUEFOC_DEV_FOC_H

#include "fast_math.h"
#include "motor.h"

#define CLARK_TO_NOR(X)         ((X)*2.0f/3.0f)
#define NOR_TO_CLARK(X)         ((X)*3.0f/2.0f)
#define VBUS_TO_VPHASE_MAX(X)   ((X)*2.0f/3.0f)
#define MAX_MODULATION_SCALE    0.9

void foc_refresh(Motor* motor);

bool foc_d_q_vec_control(Motor* motor, float vec_len, float vec_angle, float phase);
bool foc_alpha_beta_vec_control(Motor* motor, float vec_len, float vec_angle);

void foc_update_d_q(Motor* motor);

bool foc_voltage_control(Motor* motor, float Vd_set, float Vq_set, float phase);
bool foc_current_control(Motor* motor, float Id_set, float Iq_set, float I_phase, float PWM_phase);

void clarke_transform(float a, float b, float c, float *Ialpha, float *Ibeta);
void park_transform(float alpha, float beta, float theta, float *Id, float *Iq);
void inverse_park(float d, float q, float theta, float *alpha, float *beta);


bool foc_modulation_svm(float alpha, float beta, float* tA, float* tB, float* tC);

#endif //QUEFOC_DEV_FOC_H
