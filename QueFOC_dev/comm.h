//
// Created by 24216 on 2022/12/30.
//

#ifndef QUEFOC_DEV_COMM_H
#define QUEFOC_DEV_COMM_H

#include "inttypes.h"
#include "fast_math.h"
#include "motor.h"

#define MAX_CMD_BUF_SIZE 64
#define MAX_PRT_BUF_SIZE 128
#define MAX_MOTOR_TOT 2

typedef struct Motor_struct Motor;

/*! @brief Tuning and Configuration interface (ASCII Protocol) */
typedef struct Cmder_struct{
    // All available motor
    Motor *motor_list[MAX_MOTOR_TOT];
    uint8_t motor_tot;
    // Current selected motor
    Motor *motor;
    bool echo;
    char ch_end_of_cmd;

    uint32_t cmd_char_cnt;
    uint8_t cmd[MAX_CMD_BUF_SIZE+1];

    char prt_buf[MAX_PRT_BUF_SIZE];

    /* Hardware specific */
    void (*hardware_boot)(void);
    void (*hardware_transmit)(const char* str);

} Cmder;

void cmder_init(Cmder* cmder,
                char ch_end_of_cmd, bool echo,
                void (*hardware_boot)(void),
                void (*hardware_transmit)(const char* str));

void cmder_boot(Cmder* cmd);

void cmder_add_motor(Cmder* cmder, Motor* motor);

void interrupt_receive_one_char(Cmder* cmd, uint8_t cmd_char);

void cmder_report_prt(Cmder* cmder, const char *format, ...);

void cmder_report_info(Cmder* cmder, Motor* motor, const char* msg);

void cmder_report_error(Cmder* cmder, Motor* motor, const char* msg);


// TODO Further wrapping Monitor object
/*! @brief Supervision and variable monitoring (ASCII Protocol) */
typedef struct {
    char prt_buf[MAX_PRT_BUF_SIZE];
    /* Hardware specific */
    void (*hardware_boot)(void);
    void (*hardware_transmit)(const char* str);
} Monitor;


void monitor_init(Monitor* monitor,
                  void (*hardware_init)(void),
                  void (*hardware_transmit)(const char* str));

void monitor_boot(Monitor* monitor);

void monitor_prt(Monitor* monitor, const char *format, ...);


#endif //QUEFOC_DEV_COMM_H
