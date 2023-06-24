//
// Created by 24216 on 2022/12/21.
//

#ifndef QUEFOC_DEV_FAST_MATH_H
#define QUEFOC_DEV_FAST_MATH_H


#define bool                    int
#define true                    1
#define false                   0

#define PI                      (3.1415927f)
#define PI_2                    (1.5707963f)
#define PIx3_2                  (4.7123890f)
#define PIx2                    (6.2831854f)

#define ONE_BY_SQRT3			(0.5773502692f)
#define TWO_BY_SQRT3			(1.1547005384f)
#define SQRT3_BY_2				(0.8660254038f)

#define SQ(X)                   ((X)*(X))
#define ABS(X)                  ((X)<0?(-(X)):(X))
#define MIN(A, B)               ((A)<(B)?(A):(B))
#define MAX(A, B)               ((A)>(B)?(A):(B))

#define RAD2ANG(R)              ((R)*180.0f/PI)
#define ANG2RAD(A)              ((A)/180.0f*PI)


#define CONTAIN_IN(X, L, R)     ((X)<(L)?(L):((X)>(R)?(R):(L)))

/*!
 * @brief Check if [L, R] contains value X
 */
#define IF_CONTAIN_IN(X, L, R)     ((X>=L)&&(X<=R))
/*!
 * @brief Check if [Y-D, Y+D] contains value X
 */
#define IF_CONTAIN_IN2(X, Y, D)       IF_CONTAIN_IN((X), (Y)-(D), (Y)+(D))

/*!
 * @brief Just like fmodf
 */
#define REM(X, Y) ((X) - Y * (int)(X / Y))

/*!
 * @brief A simple low pass filter in marco
 * @param value             Filtered value
 * @param sample            Current sample
 * @param filter_constant   Range 0.0 to 1.0, where 1.0 gives the unfiltered value.
 */
#define LOW_PASS_FAST(value, sample, filter_constant)   (value -= (filter_constant) * ((value) - (sample)))

float fmodf_real(float dividend, float divisor);

int mod_real(int dividend, int divisor);

float fast_cos(float theta);

float fast_sin(float theta);

float fast_sqrt(const float x);



#endif //QUEFOC_DEV_FAST_MATH_H
