//
// Created by 24216 on 2022/12/21.
//

#include "encoder.h"

void encoder_init(Encoder *encoder, uint32_t freq, uint32_t cpr, int motor_pole_pairs, void (*hardware_boot)(void), bool (*hardware_get_abs_pos_cnt)(uint16_t*)){
    encoder->measure_period = 1.0f/freq;
    encoder->cpr = cpr;
    encoder->motor_pole_pairs = motor_pole_pairs;
    encoder->hardware_boot = hardware_boot;
    encoder->hardware_get_abs_pos_cnt = hardware_get_abs_pos_cnt;
    encoder->dir = 0;
    encoder_pll_param_update(encoder, 1200);
}

void encoder_boot(Encoder *encoder){
    encoder->hardware_boot();
}

static inline int std_delta_cnt(Encoder *encoder, int delta_cnt){
    int res = mod_real(delta_cnt, encoder->cpr);
    if(res > encoder->cpr/2)
        res -= encoder->cpr;
    return res;
}

bool encoder_update(Encoder *encoder){
    while(encoder->hardware_get_abs_pos_cnt(&encoder->cnt_raw)!=1){
        LOW_PASS_FAST(encoder->cnt_rx_error, 1, 0.1);
        if(encoder->cnt_rx_error>0.8) return false;
    }
    LOW_PASS_FAST(encoder->cnt_rx_error, 0, 0.1);
    int32_t data_raw_offset = (int32_t)encoder->cnt_raw-(int32_t)encoder->offset;
    if(encoder->dir > 0)
        encoder->cnt = data_raw_offset;
    else
        encoder->cnt = (int32_t)encoder->cpr - data_raw_offset;


    encoder->cnt_delta = std_delta_cnt(encoder, encoder->cnt - encoder->cnt_pre);
    // note that cnt_sum may overflow
    encoder->cnt_sum += encoder->cnt_delta;
    // update cnt_raw_pre
    encoder->cnt_pre = encoder->cnt;

    /* PLL algorithm to estimate velocity */

    // estimate position
    encoder->cnt_pos_estimate += encoder->measure_period * encoder->cnt_vel_estimate;
    // calc estimate error
    int32_t cnt_pos_estimate_error = std_delta_cnt(encoder, encoder->cnt - (int)(encoder->cnt_pos_estimate));

    encoder->cnt_pos_estimate += encoder->measure_period * encoder->pll_kp * (float)cnt_pos_estimate_error;
    encoder->cnt_pos_estimate = fmodf_real(encoder->cnt_pos_estimate, (float)encoder->cpr);
    encoder->cnt_vel_estimate += encoder->measure_period * encoder->pll_ki * (float)cnt_pos_estimate_error;

    encoder->vel = encoder->cnt_vel_estimate / (float)encoder->cpr;
    encoder->pos = (float)(encoder->cnt_sum/encoder->cpr) + (float)(encoder->cnt_sum%encoder->cpr)/(float)encoder->cpr;

    bool snap_to_zero_vel = false;
    if (ABS(encoder->cnt_vel_estimate) < 0.5f * encoder->measure_period * encoder->pll_ki) {
        encoder->cnt_vel_estimate = 0.0f;  //align delta-sigma on zero to prevent jitter
        snap_to_zero_vel = true;
    }

    /* Encoder count interpolation */

    // if we are stopped, make sure we don't randomly drift
    if (snap_to_zero_vel) {
        encoder->interpolation = 0.5f;
    // reset interpolation if encoder edge comes
    } else if (encoder->cnt_delta > 0) {
        encoder->interpolation = 0.0f;
    } else if (encoder->cnt_delta < 0) {
        encoder->interpolation = 1.0f;
    } else {
        // Interpolate (predict) between encoder counts using vel_estimate,
        encoder->interpolation += encoder->measure_period * encoder->cnt_vel_estimate;
        // don't allow interpolation indicated position outside of [enc, enc+1)
        encoder->interpolation = CONTAIN_IN(encoder->interpolation, 0, 1);
    }
    //float real_interpolated_pos_cnt = ((float)encoder->cnt_raw - (float)encoder->offset) + encoder->interpolation;
    encoder->interpolated_cnt = (float)encoder->cnt + encoder->interpolation;
    //real_interpolated_pos_cnt = fmodf_real(real_interpolated_pos_cnt, (float)encoder->cpr);


    encoder->i_phase = (encoder->interpolated_cnt * PIx2 * (float)encoder->motor_pole_pairs)/(float)encoder->cpr;
    encoder->i_phase_vel = encoder->vel * PIx2 * (float)encoder->motor_pole_pairs;

    return true;
}

void encoder_pll_clear(Encoder *encoder){
    encoder->cnt_sum = encoder->cnt_pre = 0;
    encoder->cnt_pos_estimate = encoder->cnt_vel_estimate = 0;
    encoder->interpolation = encoder->interpolated_cnt = 0;
    encoder->vel = encoder->pos = 0;
}

void encoder_pll_param_update(Encoder *encoder, float bandwidth){
    encoder->pll_kp = 2.0f * bandwidth;
    encoder->pll_ki = 0.25f * encoder->pll_kp * encoder->pll_kp;
}
