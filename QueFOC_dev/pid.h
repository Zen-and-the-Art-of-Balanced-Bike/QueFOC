//
// Created by 24216 on 2022/12/21.
//

#ifndef QUEFOC_DEV_PID_H
#define QUEFOC_DEV_PID_H

typedef struct {
    float kp, ki, kd;

    float set_point;
}PID;

#endif //QUEFOC_DEV_PID_H
