//
// Created by 24216 on 2022/12/21.
//

#include "foc.h"
#include "fast_math.h"
#include "math.h"

//float DEBUG_ALPHA, DEBUG_BETA;

void foc_refresh(Motor* motor){
    motor->torque_sp = motor->vel_sp = 0;
    motor->ctrl_i_integral_id = motor->ctrl_i_integral_iq = 0;
    motor->i_d = motor->i_q = 0;
}

static bool foc_d_q_mod_control(Motor* motor, float mod_d, float mod_q, float phase){
    // Inverse park transform
    float mod_alpha, mod_beta;
    inverse_park(mod_d, mod_q, phase, &mod_alpha, &mod_beta);

//    DEBUG_ALPHA = mod_alpha;
//    DEBUG_BETA = mod_beta;

    // SVM
    if(!foc_modulation_svm(mod_alpha, mod_beta, &(motor->pwm->duty_a), &(motor->pwm->duty_b), &(motor->pwm->duty_c))){
        motor->state = MS_ERROR_SVM_RESULT_INVALID;
        return false;
    }
    return true;
}

bool foc_d_q_vec_control(Motor* motor, float vec_len, float vec_angle, float phase){
    if(ABS(vec_len) > 1) return false;
    vec_len = vec_len * SQRT3_BY_2;
    float mod_d = vec_len * fast_cos(vec_angle);
    float mod_q = vec_len * fast_sin(vec_angle);

    return foc_d_q_mod_control(motor, mod_d, mod_q, phase);
}

bool foc_alpha_beta_vec_control(Motor* motor, float vec_len, float vec_angle){
    return foc_d_q_vec_control(motor, vec_len, vec_angle, 0);
}

void foc_update_d_q(Motor* motor){
    // Clarke transform
    clarke_transform(motor->adc->i_a, motor->adc->i_b, motor->adc->i_c, &motor->i_alpha, &motor->i_beta);

    // Park transform
    park_transform(motor->i_alpha, motor->i_beta, motor->encoder->i_phase, &motor->i_d, &motor->i_q);
}

bool foc_voltage_control(Motor* motor, float Vd_set, float Vq_set, float phase)
{

    // Modulation
    float V_to_mod = 1.0f / VBUS_TO_VPHASE_MAX(motor->adc->v_bus);
    float mod_d = V_to_mod * Vd_set;
    float mod_q = V_to_mod * Vq_set;

    // Vector modulation saturation
    float mod_scalefactor = MAX_MODULATION_SCALE * SQRT3_BY_2 / fast_sqrt(SQ(mod_d) + SQ(mod_q));
    if (mod_scalefactor < 1.0f) {
        mod_d *= mod_scalefactor;
        mod_q *= mod_scalefactor;
    }

    return foc_d_q_mod_control(motor, mod_d, mod_q, phase);
}

bool foc_current_control(Motor* motor, float Id_set, float Iq_set, float I_phase, float PWM_phase)
{


    float mod_to_V = VBUS_TO_VPHASE_MAX(motor->adc->v_bus);
    float V_to_mod = 1.0f / mod_to_V;

    // Apply PI control
    float Ierr_d = Id_set - motor->i_d;
    float Ierr_q = Iq_set - motor->i_q;
    float mod_d = V_to_mod * (motor->ctrl_i_integral_id + Ierr_d * motor->ctrl_i_kp);
    float mod_q = V_to_mod * (motor->ctrl_i_integral_iq + Ierr_q * motor->ctrl_i_kp);

    // Vector modulation saturation, lock integrator if saturated
    float mod_scalefactor = MAX_MODULATION_SCALE * SQRT3_BY_2 / fast_sqrt(SQ(mod_d) + SQ(mod_q));
    if (mod_scalefactor < 1.0f) {
        mod_d *= mod_scalefactor;
        mod_q *= mod_scalefactor;
        motor->ctrl_i_integral_id *= 0.99f;
        motor->ctrl_i_integral_iq *= 0.99f;
    } else {
        motor->ctrl_i_integral_id += Ierr_d * motor->ctrl_i_ki * motor->adc->measure_period;
        motor->ctrl_i_integral_iq += Ierr_q * motor->ctrl_i_ki * motor->adc->measure_period;
    }

    motor->adc->i_bus = (mod_d*motor->i_d + mod_q*motor->i_q);

    return foc_d_q_mod_control(motor, mod_d, mod_q, PWM_phase);
}

void clarke_transform(float a, float b, float c, float *alpha, float *beta)
{
    *alpha = a;
    *beta  = (b - c) * ONE_BY_SQRT3;
}

void park_transform(float alpha, float beta, float theta, float *d, float *q)
{
    float s = fast_sin(theta);
    float c = fast_cos(theta);
    *d =   alpha * c + beta * s;
    *q = - alpha * s + beta * c;
}

void inverse_park(float d, float q, float theta, float *alpha, float *beta)
{
    float s = fast_sin(theta);
    float c = fast_cos(theta);
    *alpha = d * c - q * s;
    *beta  = d * s + q * c;
}

/*!
 * @brief calculate the pwm duty by alpha and beta
 * @note the sign of alpha and beta depends on current direction,
 * here the positive direction is defined as the direction from the positive DC link to the negative DC link,
 * rather than defining the direction of flow into the motor winding as the positive direction
 * @param[in]   alpha alpha
 * @param[in]   beta beta
 * @param[out]  tA pwm duty of channel A
 * @param[out]  tB pwm duty of channel B
 * @param[out]  tC pwm duty of channel C
 * @retval  return 0 if result invalid
*/
bool foc_modulation_svm(float alpha, float beta, float* tA, float* tB, float* tC)
{
    int Sextant;

    if (beta >= 0.0f) {
        if (alpha >= 0.0f) {
            //quadrant I
            if (ONE_BY_SQRT3 * beta > alpha)
                Sextant = 2; //sextant v2-v3
            else
                Sextant = 1; //sextant v1-v2

        } else {
            //quadrant II
            if (-ONE_BY_SQRT3 * beta > alpha)
                Sextant = 3; //sextant v3-v4
            else
                Sextant = 2; //sextant v2-v3
        }
    } else {
        if (alpha >= 0.0f) {
            //quadrant IV
            if (-ONE_BY_SQRT3 * beta > alpha)
                Sextant = 5; //sextant v5-v6
            else
                Sextant = 6; //sextant v6-v1
        } else {
            //quadrant III
            if (ONE_BY_SQRT3 * beta > alpha)
                Sextant = 4; //sextant v4-v5
            else
                Sextant = 5; //sextant v5-v6
        }
    }

    switch (Sextant) {
        // sextant v1-v2
        case 1: {
            // Vector on-times
            float t1 = alpha - ONE_BY_SQRT3 * beta;
            float t2 = TWO_BY_SQRT3 * beta;

            // PWM timings
            *tA = (1.0f - t1 - t2) * 0.5f;
            *tB = *tA + t1;
            *tC = *tB + t2;
        } break;

        // sextant v2-v3
        case 2: {
            // Vector on-times
            float t2 = alpha + ONE_BY_SQRT3 * beta;
            float t3 = -alpha + ONE_BY_SQRT3 * beta;

            // PWM timings
            *tB = (1.0f - t2 - t3) * 0.5f;
            *tA = *tB + t3;
            *tC = *tA + t2;
        } break;

        // sextant v3-v4
        case 3: {
            // Vector on-times
            float t3 = TWO_BY_SQRT3 * beta;
            float t4 = -alpha - ONE_BY_SQRT3 * beta;

            // PWM timings
            *tB = (1.0f - t3 - t4) * 0.5f;
            *tC = *tB + t3;
            *tA = *tC + t4;
        } break;

        // sextant v4-v5
        case 4: {
            // Vector on-times
            float t4 = -alpha + ONE_BY_SQRT3 * beta;
            float t5 = -TWO_BY_SQRT3 * beta;

            // PWM timings
            *tC = (1.0f - t4 - t5) * 0.5f;
            *tB = *tC + t5;
            *tA = *tB + t4;
        } break;

        // sextant v5-v6
        case 5: {
            // Vector on-times
            float t5 = -alpha - ONE_BY_SQRT3 * beta;
            float t6 = alpha - ONE_BY_SQRT3 * beta;

            // PWM timings
            *tC = (1.0f - t5 - t6) * 0.5f;
            *tA = *tC + t5;
            *tB = *tA + t6;
        } break;

        // sextant v6-v1
        case 6: {
            // Vector on-times
            float t6 = -TWO_BY_SQRT3 * beta;
            float t1 = alpha + ONE_BY_SQRT3 * beta;

            // PWM timings
            *tA = (1.0f - t6 - t1) * 0.5f;
            *tC = *tA + t1;
            *tB = *tC + t6;
        } break;
        default:
            return false;
    }

    return (*tA >= 0.0f && *tA <= 1.0f
           && *tB >= 0.0f && *tB <= 1.0f
           && *tC >= 0.0f && *tC <= 1.0f);
}
