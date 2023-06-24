//
// Created by 24216 on 2022/12/23.
//

#ifndef QUEFOC_DEV_MOTOR_H
#define QUEFOC_DEV_MOTOR_H

#include "encoder.h"
#include "pwm.h"
#include "adc_sensor.h"
#include "pid.h"
#include "comm.h"

typedef enum {
    MS_CREATED,
    MS_BOOTED,

    /* States of calibration */
    MS_CALIBRATION_BEGIN,

    MS_CALIBRATION_CURRENT_DIR_INIT,
    MS_CALIBRATION_CURRENT_DIR_LOOP,

    MS_CALIBRATION_PHASE_CURRENT_OFFSET_INIT,
    MS_CALIBRATION_PHASE_CURRENT_OFFSET_LOOP,

    MS_CALIBRATION_MEASURE_PHASE_RESISTANCE_INIT,
    MS_CALIBRATION_MEASURE_PHASE_RESISTANCE_LOOP,

    MS_CALIBRATION_MEASURE_PHASE_INDUCTANCE_INIT,
    MS_CALIBRATION_MEASURE_PHASE_INDUCTANCE_LOOP,

    MS_CALIBRATION_ENCODER_OFFSET_INIT,
    MS_CALIBRATION_ENCODER_OFFSET_LOOP,

    MS_CALIBRATION_CHECK_DIRECTION_AND_POLE_PAIRS_INIT,
    MS_CALIBRATION_CHECK_DIRECTION_AND_POLE_PAIRS_LOOP,

    MS_CALIBRATION_CHECK_ENCODER_INIT,
    MS_CALIBRATION_CHECK_ENCODER_LOOP,

    MS_CALIBRATION_END,

    MS_IDLE,
    MS_TEST,
    /* States of run */
    MS_RUN_BEGIN,
    MS_RUN_TORQUE,
    MS_RUN_VELOCITY,
    MS_RUN_END,
    /* States of error */
    MS_ERROR_BEGIN,
    MS_ERROR_PHASE_RESISTANCE_OUT_OF_RANGE,
    MS_ERROR_UNKNOWN_STATE,
    MS_ERROR_CALIBRATION_PHASE_CURRENT_OFFSET,
    MS_ERROR_CALIBRATION_POLE_PAIRS,
    MS_ERROR_SVM_RESULT_INVALID,
    MS_ERROR_ENCODER_COMMUNITE_FAIL,
    MS_ERROR_END,

} Motor_state;

typedef struct Cmder_struct Cmder;

/*! @brief BLDC Motor Object */
typedef struct Motor_struct{
    // Motor object ID
    uint8_t id;
    // KT [N*m/A]
    float torque_constant;
    // Calibration current [A]
    float calib_current;
    // Calibration current [V]
    float calib_voltage;
    // Current control bandwidth, perhaps 10% sample frequency
    float i_ctrl_bandwidth;
    // Rotational inertia [Nm/(turn/s^2)]
    float inertia;

    float limit_i_bus_max;
    float limit_i_leak_max;
    float limit_v_bus_min, limit_v_bus_max;

    float limit_vel_max;
    float limit_i_max;

    // motor's encoder
    Encoder* encoder;
    // motor's adc sensor
    ADC_sensor* adc;
    // motor's pwm settings
    PWM* pwm;

    Cmder* cmder;

    // Current PI controller, auto set
    float ctrl_i_kp, ctrl_i_ki;
    // Integral of current PI controller
    float ctrl_i_integral_id, ctrl_i_integral_iq;

    // Velocity controller
    float ctrl_vel_kp, ctrl_vel_ki;
    float ctrl_vel_integral;

    Motor_state state;

    // user input set point
    float torque_input, vel_input;
    // Torque set point [Nm]
    float torque_sp;
    // Velocity set point [turn/s]
    float vel_sp;

    float phase_resistance, phase_inductance;
    float i_d, i_q;
    float i_q_set;
    float i_alpha, i_beta;

    /* Hardware specific */
    void (*hardware_basic_boot)(void);

} Motor;


void motor_init(Motor* motor,
                uint8_t id, uint32_t KV, float calib_current, float calib_voltage,
                float ctrl_i_bandwidth, float inertia,
                float limit_i_bus_max, float limit_i_leak_max, float limit_v_bus_min, float limit_v_bus_max,
                float limit_vel_max, float limit_i_max,
                Encoder* encoder, ADC_sensor* adc, PWM* pwm, Cmder* cmder,
                void (*hardware_basic_boot)(void));

void motor_boot(Motor* motor);

void motor_stop(Motor* motor);

void motor_shift_state(Motor* motor, Motor_state state);

void interrupt_adc_done(Motor* motor);

void motor_loop_main(Motor* motor);

void motor_loop_calibration(Motor* motor);

void motor_loop_run(Motor* motor);

void motor_loop_error(Motor* motor);

void motor_update_current_ctrl_param(Motor* motor);

void motor_update_vel_ctrl_param(Motor* motor, float kp, float ki);

#endif //QUEFOC_DEV_MOTOR_H
