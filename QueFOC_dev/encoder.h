//
// Created by 24216 on 2022/12/21.
//

#ifndef QUEFOC_DEV_ENCODER_H
#define QUEFOC_DEV_ENCODER_H

#include "fast_math.h"
#include "inttypes.h"

/*! @brief ABS Encoder Object */
typedef struct {
    float measure_period;
    uint32_t cpr;
    uint16_t motor_pole_pairs;
    //
    float i_phase;        //  [rad]
    float i_phase_vel;    //  [rad/s]
    float vel;          //  [turn/s]
    float pos;          //  [turn]
    //
    bool dir;
    uint16_t offset;
    //
    uint16_t cnt_raw;
    int32_t cnt;
    int32_t cnt_pre;
    int32_t cnt_sum;
    int32_t cnt_delta;

    float cnt_rx_error;

    // PLL algorithm
    float pll_kp, pll_ki;
    float cnt_pos_estimate;
    float cnt_vel_estimate;

    float interpolation;
    float interpolated_cnt;

    /* Hardware specific */
    void        (*hardware_boot)(void);
    bool        (*hardware_get_abs_pos_cnt)(uint16_t*);

} Encoder;

void encoder_init(Encoder *encoder, uint32_t freq, uint32_t cpr, int motor_pole_pairs, void (*hardware_boot)(void), bool (*hardware_get_abs_pos_cnt)(uint16_t*));

void encoder_boot(Encoder *encoder);

bool encoder_update(Encoder *encoder);

void encoder_pll_clear(Encoder *encoder);

void encoder_pll_param_update(Encoder *encoder, float bandwidth);

#endif //QUEFOC_DEV_ENCODER_H
