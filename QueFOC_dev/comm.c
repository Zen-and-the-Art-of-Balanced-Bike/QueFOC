//
// Created by 24216 on 2022/12/30.
//

#include "comm.h"
#include "foc.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG_CMD


void cmder_init(Cmder* cmder,
                char ch_end_of_cmd, bool echo,
                void (*hardware_boot)(void),
                void (*hardware_transmit)(const char* str)){
    memset(cmder, 0, sizeof(Cmder));
    cmder->ch_end_of_cmd = ch_end_of_cmd;
    cmder->echo = echo;
    cmder->hardware_boot = hardware_boot;
    cmder->hardware_transmit = hardware_transmit;
    cmder->cmd_char_cnt = 0;
    cmder->motor_tot = 0;
    cmder->motor = NULL;
}

void cmder_boot(Cmder* cmd){
    cmd->hardware_boot();
}

void cmder_add_motor(Cmder* cmder, Motor* motor){
    cmder->motor_list[cmder->motor_tot++] = motor;
}

static void cmder_cmd_error(Cmder* cmder, uint32_t error_pos){
    cmder_report_prt(cmder, "[CMD ERROR]\n%s\n", cmder->cmd);
    for(int i=0;i<=error_pos-1;++i)
        cmder_report_prt(cmder, "-");
    cmder_report_prt(cmder, "^\n");
}

/*! @retval return false if there is no param */
static bool cmder_cmd_get_param_f(Cmder* cmder, uint32_t param_pos, float* val){
    if(cmder->cmd[param_pos] == '\0') return false;
    char *endptr;
    float param = strtof((char*)&cmder->cmd[param_pos], &endptr);
    if(*endptr != '\0')
        cmder_cmd_error(cmder, endptr - (char*) cmder->cmd);
    else
        *val = param;
    return true;
}

/*! @retval return false if there is no param */
static bool cmder_cmd_get_param(Cmder* cmder, uint32_t param_pos, int* val){
    if(cmder->cmd[param_pos] == '\0') return false;
    char *endptr;
    int param = strtol((char*)&cmder->cmd[param_pos], &endptr, 10);
    if(*endptr != '\0')
        cmder_cmd_error(cmder, endptr - (char*) cmder->cmd);
    else
        *val = param;
    return true;
}

static void cmder_cmd_motor(Cmder* cmder, uint32_t cmd_pos){
    switch (cmder->cmd[++cmd_pos]) {
        // state
        case 'S':
        {
            switch (cmder->cmd[++cmd_pos]) {
                // stop
                case 'S':
                    motor_stop(cmder->motor);
                    break;
                case 'T':
                    cmder->motor->state = MS_RUN_TORQUE;
                    break;
                case 'V':
                    cmder->motor->state = MS_RUN_VELOCITY;
                    break;
                // none
                case '\0':
                    cmder_report_prt(cmder, "state=%d\n", cmder->motor->state);
                    break;
                default:
                    cmder_cmd_error(cmder, cmd_pos);
            }
        }
            break;
        // control
        case 'C':
        {
            switch (cmder->cmd[++cmd_pos]) {
                // Torque close loop
                case 'T':
                {
                    if(!cmder_cmd_get_param_f(cmder, cmd_pos+1, &cmder->motor->torque_input))
                        cmder_report_prt(cmder, "torque_sp=%f\n", cmder->motor->torque_sp);
                }
                    break;
                // Vel close loop
                case 'V':
                {
                    if(!cmder_cmd_get_param_f(cmder, cmd_pos+1, &cmder->motor->vel_input))
                        cmder_report_prt(cmder, "vel_sp=%f\n", cmder->motor->vel_sp);
                }
                    break;
                default:
                    cmder_cmd_error(cmder, cmd_pos);
            }
        }
            break;
        // Vel PID
        case 'K':
        {
            switch (cmder->cmd[++cmd_pos]) {
                // kp
                case 'P':
                {
                    if(!cmder_cmd_get_param_f(cmder, cmd_pos+1, &cmder->motor->ctrl_vel_kp))
                        cmder_report_prt(cmder, "ctrl_vel_kp=%f\n", cmder->motor->ctrl_vel_kp);
                }
                    break;
                // kp
                case 'I':
                {
                    if(!cmder_cmd_get_param_f(cmder, cmd_pos+1, &cmder->motor->ctrl_vel_ki))
                        cmder_report_prt(cmder, "ctrl_vel_ki=%f\n", cmder->motor->ctrl_vel_ki);
                }
                    break;
                default:
                    cmder_cmd_error(cmder, cmd_pos);
            }
        }
            break;

        // current control bandwidth
        case 'B':
        {
            if(!cmder_cmd_get_param_f(cmder, cmd_pos+1, &cmder->motor->i_ctrl_bandwidth))
                cmder_report_prt(cmder, "ctrl_i_bandwidth=%.3f\n", cmder->motor->i_ctrl_bandwidth);
        } break;
        default:
            cmder_cmd_error(cmder, cmd_pos);
    }
}

static void cmder_cmd_adc(Cmder* cmder, uint32_t cmd_pos){
    switch (cmder->cmd[++cmd_pos]) {
        // Current
        case 'I':
        {
            cmder_report_prt(cmder, "%f %f %f\n", cmder->motor->adc->i_a, cmder->motor->adc->i_b, cmder->motor->adc->i_c);
        }
            break;
        // Voltage
        case 'V':
        {
            switch (cmder->cmd[++cmd_pos]) {
                // VBus
                case 'B':
                    cmder_report_prt(cmder, "Vbus=%.3f\n", cmder->motor->adc->v_bus);
                    break;
                // VGND
                case 'G':
                    cmder_report_prt(cmder, "VGND=%.3f\n", cmder->motor->adc->v_gnd);
                    break;
                default:
                    cmder_cmd_error(cmder, cmd_pos);
            }
        }
            break;
        // Hardware
        case 'H':
        {
            switch (cmder->cmd[++cmd_pos]) {
                // IA
                case 'A':
                    cmder_report_prt(cmder, "IA=%d\n", cmder->motor->adc->hardware_adc_read_phase_a());
                    break;
                // IB
                case 'B':
                    cmder_report_prt(cmder, "IB=%d\n", cmder->motor->adc->hardware_adc_read_phase_b());
                    break;
                // IC
                case 'C':
                    cmder_report_prt(cmder, "IC=%d\n", cmder->motor->adc->hardware_adc_read_phase_c());
                    break;
                default:
                    cmder_cmd_error(cmder, cmd_pos);
            }
        }
            break;
        default:
            cmder_cmd_error(cmder, cmd_pos);
    }
}

static void cmder_cmd_encoder(Cmder* cmder, uint32_t cmd_pos){

}

#ifdef DEBUG_CMD
float debug_id_set=0.3;
static void cmder_cmd_debug(Cmder* cmder, uint32_t cmd_pos){
    switch (cmder->cmd[++cmd_pos]) {
        // PWM output
        case 'P':
            switch (cmder->cmd[++cmd_pos]){
                case 'A':
                {
                    if(!cmder_cmd_get_param_f(cmder, cmd_pos+1, &cmder->motor->pwm->duty_a))
                        cmder_report_prt(cmder, "pwm_a=%.3f\n", cmder->motor->pwm->duty_a);
                    pwm_sync_duty(cmder->motor->pwm);
                }
                break;
                case 'B':
                {
                    if(!cmder_cmd_get_param_f(cmder, cmd_pos+1, &cmder->motor->pwm->duty_b))
                        cmder_report_prt(cmder, "pwm_b=%.3f\n", cmder->motor->pwm->duty_b);
                    pwm_sync_duty(cmder->motor->pwm);
                }
                break;
                case 'C':
                {
                    if(!cmder_cmd_get_param_f(cmder, cmd_pos+1, &cmder->motor->pwm->duty_c))
                        cmder_report_prt(cmder, "pwm_c=%.3f\n", cmder->motor->pwm->duty_c);
                    pwm_sync_duty(cmder->motor->pwm);
                }
                break;
                default:
                    cmder_cmd_error(cmder, cmd_pos);
            }
            break;
        // FOC control test
        case 'F':
            switch (cmder->cmd[++cmd_pos]){

                // R
                case 'A':
                {
                    int t=1;
                    cmder_cmd_get_param(cmder, cmd_pos+1, &t);
                    float phase=0;
                    motor_stop(cmder->motor);
                    for(int i=0;i<t*20;++i){
                        if(foc_d_q_vec_control(cmder->motor, 0.1, 0, phase))
                            pwm_sync_duty(cmder->motor->pwm);
                        hardware_delay_ms(100);
                        //encoder_update(cmder->motor->encoder);
                        //cmder_report_prt(cmder, "%d %.3f\n", ret, (cmder->motor->encoder->data_raw-cmder->motor->encoder->offset)*1.0f*PIx2*7/16384);
                        phase += PI/10;
                        //phase += PI/10;
                    }
                    motor_stop(cmder->motor);
                    cmder_report_prt(cmder, "DONE\n");
                } break;
                // Hold position
                case 'H':
                {
                    float angel=0;
                    cmder_cmd_get_param_f(cmder, cmd_pos+1, &angel);
                    motor_stop(cmder->motor);
                    if(foc_d_q_vec_control(cmder->motor, 0.1, 0, ANG2RAD(angel)))
                        pwm_sync_duty(cmder->motor->pwm);
                    cmder_report_prt(cmder, "DONE\n");
                } break;
                // Hold vector length
                case 'L':
                {
                    float len=0;
                    cmder_cmd_get_param_f(cmder, cmd_pos+1, &len);
                    motor_stop(cmder->motor);
                    if(foc_d_q_vec_control(cmder->motor, MIN(len, MAX_MODULATION_SCALE), 0, 0))
                        pwm_sync_duty(cmder->motor->pwm);
                    cmder_report_prt(cmder, "DONE\n");
                } break;
                // Current control
                case 'I':
                {
                    float i=0;
                    cmder_cmd_get_param_f(cmder, cmd_pos+1, &i);
                    debug_id_set = i;
                    cmder_report_prt(cmder, "DONE\n");
                } break;
                // Torque control
                case 'T':
                {
                    float torque=0;
                    cmder_cmd_get_param_f(cmder, cmd_pos+1, &torque);
                    motor_stop(cmder->motor);
                    cmder->motor->torque_input = torque;
                    motor_shift_state(cmder->motor, MS_RUN_TORQUE);
                    cmder_report_prt(cmder, "DONE\n");
                } break;
            }
            break;
        default:
            cmder_cmd_error(cmder, cmd_pos);
    }
}
#endif

void interrupt_receive_one_char(Cmder* cmder, uint8_t cmd_char){
    // Skip \r
    if(cmd_char == '\r')
        return;
    if(cmd_char != cmder->ch_end_of_cmd){
        cmder->cmd[cmder->cmd_char_cnt++] = cmd_char;
        if(cmder->cmd_char_cnt >= MAX_CMD_BUF_SIZE) cmder->cmd_char_cnt = 0;
        return;
    }
    cmder->cmd[cmder->cmd_char_cnt++] = '\0';
    // echo
    if(cmder->echo)
        cmder_report_prt(cmder, "%s\n", cmder->cmd);
    // reset cmd
    cmder->cmd_char_cnt = 0;
    // reset current motor
    cmder->motor = NULL;
    // find the right motor
    for(uint8_t i=0;i<cmder->motor_tot;++i)
        if(cmder->cmd[0]==cmder->motor_list[i]->id){
            cmder->motor = cmder->motor_list[i];
            break;
        }
    if(cmder->motor == NULL){
        cmder_report_prt(cmder, "[CMD ERROR] MOTOR ID UNIDENTIFIED\n");
        return;
    }
    uint32_t cmd_pos = 0;
    switch (cmder->cmd[++cmd_pos]) {
        // Motor command
        case 'M':
            cmder_cmd_motor(cmder, cmd_pos);
            break;
        // ADC sensor command
        case 'A':
            cmder_cmd_adc(cmder, cmd_pos);
            break;
        // Encoder command
        case 'E':
            cmder_cmd_encoder(cmder, cmd_pos);
            break;
#ifdef DEBUG_CMD
        // Debug command
        case 'D':
            cmder_cmd_debug(cmder, cmd_pos);
            break;
#endif
        default:
            cmder_cmd_error(cmder, cmd_pos);
    }
}

void cmder_report_prt(Cmder* cmder, const char *format, ...){
    va_list ap;
    va_start(ap, format);
    vsnprintf(cmder->prt_buf, MAX_PRT_BUF_SIZE, format, ap);
    va_end(ap);
    cmder->hardware_transmit(cmder->prt_buf);
}


void cmder_report_info(Cmder* cmder, Motor* motor, const char* msg){
    cmder_report_prt(cmder, "[Motor%c INFO] %s\n", (char)motor->id, msg);
}

void cmder_report_error(Cmder* cmder, Motor* motor, const char* msg){
    cmder_report_prt(cmder, "[Motor%c ERROR] %s\n", (char)motor->id, msg);
}

void monitor_init(Monitor* monitor,
                  void (*hardware_init)(void),
                  void (*hardware_transmit)(const char* str)){
    memset(monitor, 0, sizeof(Monitor));
    monitor->hardware_boot = hardware_init;
    monitor->hardware_transmit = hardware_transmit;
}

void monitor_boot(Monitor* monitor){
    monitor->hardware_boot();
}

void monitor_prt(Monitor* monitor, const char *format, ...){
    static bool blocked = false;
//    while(blocked);
    if(blocked) return;
    blocked = true;
    va_list ap;
    va_start(ap, format);
    vsnprintf(monitor->prt_buf, MAX_PRT_BUF_SIZE, format, ap);
    va_end(ap);
    monitor->hardware_transmit(monitor->prt_buf);
    blocked = false;
}

