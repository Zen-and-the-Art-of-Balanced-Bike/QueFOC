cmake_minimum_required(VERSION 3.17)
project(QueFOC_dev C)

set(CMAKE_C_STANDARD 99)

add_executable(QueFOC_dev test.c foc.c filter.c filter.h encoder.c encoder.h pid.c pid.h fast_math.c fast_math.h motor.c motor.h pwm.c pwm.h adc_sensor.c adc_sensor.h comm.c comm.h)