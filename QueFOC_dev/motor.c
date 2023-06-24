//
// Created by 24216 on 2022/12/23.
//

#include "motor.h"
#include "foc.h"
#include <string.h>

extern Monitor monitor;

void motor_init(Motor* motor,
                uint8_t id, uint32_t KV, float calib_current, float calib_voltage,
                float ctrl_i_bandwidth, float inertia,
                float limit_i_bus_max, float limit_i_leak_max, float limit_v_bus_min, float limit_v_bus_max,
                float limit_vel_max, float limit_i_max,
                Encoder* encoder, ADC_sensor* adc, PWM* pwm, Cmder* cmder,
                void (*hardware_basic_boot)(void)){
    // clean up
    memset(motor, 0, sizeof(Motor));

    motor->id = id;
    motor->calib_current = calib_current;
    motor->calib_voltage = calib_voltage;
    motor->i_ctrl_bandwidth = ctrl_i_bandwidth;
    motor->inertia = inertia;

    motor->limit_i_bus_max = limit_i_bus_max;
    motor->limit_i_leak_max = limit_i_leak_max;
    motor->limit_v_bus_min = limit_v_bus_min;
    motor->limit_v_bus_max = limit_v_bus_max;
    motor->limit_vel_max = limit_vel_max;
    motor->limit_i_max = limit_i_max;


    motor->encoder = encoder;
    motor->adc = adc;
    motor->pwm = pwm;
    motor->cmder = cmder;
    motor->hardware_basic_boot = hardware_basic_boot;

    // A approximation for torque constant (Nm/A) from Odrive
    motor->torque_constant = 8.27f / (float)(KV);


    motor->state = MS_CREATED;
}

void motor_boot(Motor* motor){
    motor->hardware_basic_boot();
    // FIXME
    encoder_boot(motor->encoder);
    adc_boot(motor->adc);
    pwm_boot(motor->pwm);

    motor->state = MS_BOOTED;
}

void motor_stop(Motor* motor){
    foc_refresh(motor);
    pwm_apply_duty(motor->pwm, 0, 0, 0);
}

void motor_shift_state(Motor* motor, Motor_state state){
    motor->state = state;
}

void interrupt_adc_done(Motor* motor){
    motor_loop_main(motor);
}


void motor_loop_main(Motor* motor){
    adc_update(motor->adc);
    foc_update_d_q(motor);
    // FIXME
    if(!encoder_update(motor->encoder)){
        motor->state = MS_ERROR_ENCODER_COMMUNITE_FAIL;
    }


    if(IF_CONTAIN_IN(motor->state, MS_RUN_BEGIN, MS_RUN_END))
        motor_loop_run(motor);
    else if(IF_CONTAIN_IN(motor->state, MS_CALIBRATION_BEGIN, MS_CALIBRATION_END-1))
        motor_loop_calibration(motor);
    else if(IF_CONTAIN_IN(motor->state, MS_ERROR_BEGIN, MS_ERROR_END))
        motor_loop_error(motor);
    else if(motor->state == MS_BOOTED)
        motor->state = MS_CALIBRATION_BEGIN;
    else if(motor->state == MS_CALIBRATION_END)
        // When everything is ready, where to go?
        motor->state = MS_RUN_VELOCITY;
//        motor->state = MS_TEST;
    else if(motor->state == MS_TEST){

//        monitor_prt(&monitor, "%.3f,%.3f\n",
//                //(float)motor->encoder->cnt_raw - (float)motor->encoder->offset,
//                fmodf_real(motor->encoder->i_phase, PIx2),
////                  fmodf_real(0, PIx2)
//                motor->encoder->data_raw
//                );
//        static float pha_set = 0;
//        monitor_prt(&monitor, "%f,%f,%f,%f\n",
//                    //(float)motor->encoder->cnt_raw - (float)motor->encoder->offset,
//                motor->encoder->i_phase, pha_set,
//                        fmodf_real(motor->encoder->i_phase, PIx2),
//                                  fmodf_real(pha_set, PIx2)
//        //            motorQ.encoder->offset
//                    );
//        pha_set += PI/10;
//        if(foc_voltage_control(motor, 1, 0, pha_set))
//            pwm_sync_duty(motor->pwm);
//        hardware_delay_ms(1000);

//
//        monitor_prt(&monitor, "%d\n",
//            //(float)motor->encoder->cnt_raw - (float)motor->encoder->offset,
//                motor->encoder->data_raw
////            motorQ.encoder->offset
//            );



//        if(foc_voltage_control(motor, 0, 5, motor->encoder->i_phase))
//            pwm_sync_duty(motor->pwm);

//          if(foc_voltage_control(motor, 0.5, 0, 0))
//              pwm_sync_duty(motor->pwm);
//          monitor_prt(&monitor, "%.3f,%.3f,%.3f\n", motor->adc->i_a, motor->adc->i_b, motor->adc->i_c);
//          monitor_prt(&monitor, "%d\n", motor->encoder->data_raw);
//          hardware_delay_ms(10);
        if(foc_current_control(motor, 0, 0.5, motor->encoder->i_phase, motor->encoder->i_phase))
            pwm_sync_duty(motor->pwm);

//        if(foc_d_q_vec_control(motor, 0.2, PI_2, motor->encoder->phase))
//            pwm_sync_duty(motor->pwm);

    }
    else if(motor->state == MS_IDLE || motor->state == MS_CREATED)
        return;
    else
        motor->state = MS_ERROR_UNKNOWN_STATE;
}

void motor_loop_calibration(Motor* motor){
    static uint32_t step_loop_cnt = 0;
    static float voltages[3] = {0};
    static float currents_f[3] = {0};
    static uint32_t currents[3] = {0};
    uint32_t phase_resistance_loop_cnt = 3*motor->adc->measure_freq;
    uint32_t phase_inductance_loop_cnt = motor->adc->measure_freq/2;
    static float cur_phase = 0;

    // current step loop cnt
    step_loop_cnt += 1;

    switch (motor->state) {
        case MS_CALIBRATION_BEGIN:
        {
            motor->state = MS_CALIBRATION_PHASE_CURRENT_OFFSET_INIT;
        }
            break;
        /* phase current OP-AMP offset  */
        case MS_CALIBRATION_PHASE_CURRENT_OFFSET_INIT:
        {
            // set phase current to zero
            pwm_apply_duty(motor->pwm, 0, 0, 0);
            step_loop_cnt = 0;
            currents[0] = currents[1] = currents[2] = 0;
            motor->state = MS_CALIBRATION_PHASE_CURRENT_OFFSET_LOOP;

        }
            break;
        case MS_CALIBRATION_PHASE_CURRENT_OFFSET_LOOP:
        {
            currents[0] += motor->adc->hardware_adc_read_phase_a();
            currents[1] += motor->adc->hardware_adc_read_phase_b();
            currents[2] += motor->adc->hardware_adc_read_phase_c();
            if(step_loop_cnt >= 64){
                motor->adc->i_op_amp_offset_a = currents[0] / step_loop_cnt;
                motor->adc->i_op_amp_offset_b = currents[1] / step_loop_cnt;
                motor->adc->i_op_amp_offset_c = currents[2] / step_loop_cnt;
                uint16_t max_error_offset = (uint16_t)(0.1/3.3f*motor->adc->resolution);
                if(IF_CONTAIN_IN2(motor->adc->i_op_amp_offset_a, motor->adc->i_op_amp_offset_theory, max_error_offset) &&
                   IF_CONTAIN_IN2(motor->adc->i_op_amp_offset_b, motor->adc->i_op_amp_offset_theory, max_error_offset) &&
                   IF_CONTAIN_IN2(motor->adc->i_op_amp_offset_c, motor->adc->i_op_amp_offset_theory, max_error_offset) )
                    motor->state = MS_CALIBRATION_MEASURE_PHASE_RESISTANCE_INIT;
                else{
                    // Self-check fail
                    motor->state = MS_ERROR_CALIBRATION_PHASE_CURRENT_OFFSET;
                    cmder_report_prt(motor->cmder, "I_offset_a=%d\nI_offset_b=%d\nI_offset_c=%d\nI_offset_theory=%d\nmax_error_offset=%d\n",
                                    motor->adc->i_op_amp_offset_a, motor->adc->i_op_amp_offset_b, motor->adc->i_op_amp_offset_c,
                                    motor->adc->i_op_amp_offset_theory, max_error_offset);
                }

            }
        }
            break;

        case MS_CALIBRATION_MEASURE_PHASE_RESISTANCE_INIT:
        {
            step_loop_cnt = 0;
            voltages[0] = 0;
            motor->state = MS_CALIBRATION_MEASURE_PHASE_RESISTANCE_LOOP;
        }
            break;
        case MS_CALIBRATION_MEASURE_PHASE_RESISTANCE_LOOP:
        {
            // Integral controller
            float ki = 2;
            voltages[0] += ki * motor->adc->measure_period * (motor->calib_current - motor->adc->i_a);
            if(ABS(voltages[0]) > 5){
                pwm_apply_duty(motor->pwm, 0, 0, 0);
                motor->state = MS_ERROR_PHASE_RESISTANCE_OUT_OF_RANGE;
                //cmder_report_prt(motor->cmder, "%f %f %f\nV=%f\n", motor->adc->i_a, motor->adc->i_b, motor->adc->i_c, voltages[0]);
                break;
            }
            // Phase A
            if(foc_voltage_control(motor, voltages[0], 0, 0))
                pwm_sync_duty(motor->pwm);
            /*
            if(step_loop_cnt % 100 == 0){
                cmder_report_prt(motor->cmder, "%.3f %.3f %.3f\nV=%f\n", motor->adc->i_a, motor->adc->i_b, motor->adc->i_c, voltages[0]);
            }
            */

            if(step_loop_cnt >= phase_resistance_loop_cnt){

                motor->phase_resistance = voltages[0]/motor->calib_current *2.0f/3.0f;
                //cmder_report_prt(motor->cmder, "%f\n", voltages[0]);
                //cmder_report_prt(motor->cmder, "%f\nphase_resistance=%f\n", motor->adc->i_a, motor->phase_resistance);
                motor->state = MS_CALIBRATION_MEASURE_PHASE_INDUCTANCE_INIT;
                pwm_apply_duty(motor->pwm, 0, 0, 0);
            }
        }
            break;
        case MS_CALIBRATION_MEASURE_PHASE_INDUCTANCE_INIT:
        {
            step_loop_cnt = 0;
            voltages[0] = -motor->calib_voltage;
            voltages[1] = +motor->calib_voltage;
            currents_f[0] = currents_f[1] = 0;
            if(foc_voltage_control(motor, voltages[0], 0, 0))
                pwm_sync_duty(motor->pwm);
            motor->state = MS_CALIBRATION_MEASURE_PHASE_INDUCTANCE_LOOP;
        }
            break;
        case MS_CALIBRATION_MEASURE_PHASE_INDUCTANCE_LOOP:
        {
            uint32_t idx = step_loop_cnt & 1;
            currents_f[idx^1] += motor->adc->i_a;
            // Phase A
            if(foc_voltage_control(motor, voltages[idx], 0, 0))
                pwm_sync_duty(motor->pwm);
            if(step_loop_cnt >= phase_inductance_loop_cnt*2){
                //cmder_report_prt(motor->cmder, "%.3f,%.3f\n", currents_f[0], currents_f[1]);
                float dI_by_dt = (currents_f[1] - currents_f[0]) / (float)(phase_inductance_loop_cnt * motor->adc->measure_period);
                motor->phase_inductance = motor->calib_voltage / dI_by_dt *2.0f/3.0f;
                //cmder_report_prt(motor->cmder, "phase_inductance=%f\n", motor->phase_inductance);
                // Update current ctrl param
                motor_update_current_ctrl_param(motor);

                pwm_apply_duty(motor->pwm, 0, 0, 0);
                motor->state = MS_CALIBRATION_ENCODER_OFFSET_INIT;
            }
        }
            break;
        case MS_CALIBRATION_ENCODER_OFFSET_INIT:
        {
            if(foc_voltage_control(motor, 1, 0, 0))
                pwm_sync_duty(motor->pwm);
            step_loop_cnt = 0;
            motor->state = MS_CALIBRATION_ENCODER_OFFSET_LOOP;
        }
        break;
        case MS_CALIBRATION_ENCODER_OFFSET_LOOP:
        {
            if(foc_voltage_control(motor, 1, 0, 0))
                pwm_sync_duty(motor->pwm);
            motor->encoder->offset = motor->encoder->cnt_raw;
            //cmder_report_prt(motor->cmder, "ret=%d offset=%d\n", motor->encoder->hardware_get_abs_pos_cnt(&motor->encoder->offset), motor->encoder->offset);
            if(step_loop_cnt >= 100){
                pwm_apply_duty(motor->pwm, 0, 0, 0);
                // FIXME
                motor->state = MS_CALIBRATION_CHECK_DIRECTION_AND_POLE_PAIRS_INIT;
            }
        }
        break;
        case MS_CALIBRATION_CHECK_DIRECTION_AND_POLE_PAIRS_INIT:
        {
            step_loop_cnt = 0;
            cur_phase = 0;
            motor->state = MS_CALIBRATION_CHECK_DIRECTION_AND_POLE_PAIRS_LOOP;
        }
            break;
        case MS_CALIBRATION_CHECK_DIRECTION_AND_POLE_PAIRS_LOOP:
        {
            if(cur_phase >= PIx2){
                if(motor->encoder->cnt_sum<0){
                    motor->encoder->dir ^= 1;
                }
                float pole_pairs = (float)motor->encoder->cpr/motor->encoder->cnt_sum;
                pole_pairs = ABS(pole_pairs);
                cmder_report_prt(motor->cmder, "Motor pole_pairs %f(set %d)\n", pole_pairs, motor->encoder->motor_pole_pairs);
                encoder_pll_clear(motor->encoder);
                pwm_apply_duty(motor->pwm, 0, 0, 0);
                if(ABS(pole_pairs-(float)motor->encoder->motor_pole_pairs)>1) motor->state = MS_ERROR_CALIBRATION_POLE_PAIRS;
                else motor->state = MS_CALIBRATION_END;
            }
            cur_phase += PI * motor->adc->measure_period;
            if(foc_voltage_control(motor, 1, 0, cur_phase))
                pwm_sync_duty(motor->pwm);

        }
            break;
        case MS_CALIBRATION_END:
        {
            cmder_report_prt(motor->cmder, "Motor %c calibration success\n", (char)motor->id);
            cmder_report_prt(motor->cmder, "torque_constant=%f\n", motor->torque_constant);
            cmder_report_prt(motor->cmder, "I_offset_a=%d\nI_offset_b=%d\nI_offset_c=%d\nI_offset_theory=%d\n",
                                motor->adc->i_op_amp_offset_a, motor->adc->i_op_amp_offset_b, motor->adc->i_op_amp_offset_c,
                                motor->adc->i_op_amp_offset_theory);
            cmder_report_prt(motor->cmder, "phase_resistance=%f(%fA)\n", motor->phase_resistance, motor->calib_current);
            cmder_report_prt(motor->cmder, "phase_inductance=%f(%fV)\n", motor->phase_inductance, motor->calib_voltage);
            cmder_report_prt(motor->cmder, "encoder_offset=%d\n", motor->encoder->offset);
            cmder_report_prt(motor->cmder, "ctrl_i_kp=%.3f, ctrl_i_ki=%.3f\n", motor->ctrl_i_kp, motor->ctrl_i_ki);
            cmder_report_prt(motor->cmder, "dir=%d\n", motor->encoder->dir);
        }
            break;
        default:
            break;
    }

}

void motor_loop_run(Motor* motor){
    switch (motor->state) {
        case MS_RUN_TORQUE:
        {
            motor->torque_sp = motor->torque_input;
        }
            break;
        case MS_RUN_VELOCITY:
        {
            float delta_vel = motor->vel_input - motor->vel_sp;
            // T = a * J
            motor->torque_sp = (delta_vel / motor->adc->measure_period) * motor->inertia;
            motor->vel_sp += delta_vel;
        }
            break;
        default:
            break;
    }

    float torque = motor->torque_sp;
    float vel_error = motor->vel_sp - motor->encoder->vel;

    if(motor->state >= MS_RUN_VELOCITY)
        torque += vel_error * motor->ctrl_vel_kp + motor->ctrl_vel_integral;

    float max_torque = motor->torque_constant * motor->limit_i_max;
    bool torque_limited = false;
    if(torque > max_torque){
        torque = max_torque;
        torque_limited = true;
    }else if(torque < -max_torque){
        torque = -max_torque;
        torque_limited = true;
    }

    if(motor->state < MS_RUN_VELOCITY){
        motor->ctrl_vel_integral = 0;
    }else{
        if(torque_limited)
            motor->ctrl_vel_integral *= 0.99f;
        else
            motor->ctrl_vel_integral += (motor->ctrl_vel_ki * motor->encoder->measure_period) * vel_error;
    }

    motor->i_q_set = torque / motor->torque_constant;
    float I_phase = motor->encoder->i_phase;
    // 1.5 T_measure delay ?
    float PWM_phase = I_phase + 1.5f*motor->adc->measure_period*motor->encoder->i_phase_vel;
    if(foc_current_control(motor, 0, motor->i_q_set, I_phase, PWM_phase))
        pwm_sync_duty(motor->pwm);
}

void motor_loop_error(Motor* motor){
    switch (motor->state) {
        case MS_ERROR_CALIBRATION_PHASE_CURRENT_OFFSET:
        {
            cmder_report_error(motor->cmder, motor, "CALIBRATION PHASE CURRENT OFFSET SELF CHECK FAIL");
        }
            break;
        case MS_ERROR_SVM_RESULT_INVALID:
        {
            cmder_report_error(motor->cmder, motor, "SVM RESULT INVALID");
        }
            break;
        case MS_ERROR_UNKNOWN_STATE:
        {
            cmder_report_error(motor->cmder, motor, "UNKNOWN MOTOR STATE");
        }
            break;
        case MS_ERROR_PHASE_RESISTANCE_OUT_OF_RANGE:
        {
            cmder_report_error(motor->cmder, motor, "PHASE RESISTANCE OUT OF RANGE");
        } break;
        case MS_ERROR_CALIBRATION_POLE_PAIRS:
        {
            cmder_report_error(motor->cmder, motor, "MOTOR POLE PAIRS UNMATCH");
            break;
        }
        case MS_ERROR_ENCODER_COMMUNITE_FAIL:
        {
            cmder_report_error(motor->cmder, motor, "ENCODER COMMUNITE FAIL");
            break;
        }
        default:
        {
            cmder_report_error(motor->cmder, motor, "UNKNOWN ERROR");
        }
            break;
    }
    motor_stop(motor);
    //while(1){}
}
void motor_update_current_ctrl_param(Motor* motor){
    motor->ctrl_i_kp = motor->phase_inductance * motor->i_ctrl_bandwidth;
    //float plant_pole = motor->phase_resistance / motor->phase_inductance;
//    motor->i_ctrl_ki = plant_pole * motor->i_ctrl_kp;
    motor->ctrl_i_ki = motor->phase_resistance * motor->i_ctrl_bandwidth;

    motor->ctrl_i_integral_id = motor->ctrl_i_integral_iq = 0;
}

void motor_update_vel_ctrl_param(Motor* motor, float kp, float ki){
    motor->ctrl_vel_kp = kp;
    motor->ctrl_vel_ki = ki;
    motor->ctrl_vel_integral = 0;
}
