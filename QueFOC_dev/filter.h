//
// Created by 24216 on 2022/12/21.
//

#ifndef QUEFOC_DEV_FILTER_H
#define QUEFOC_DEV_FILTER_H

/*!
 * @brief A simple low pass filter in marco
 * @param value Filtered value
 * @param sample ADC_sensor sample value
 * @param filter_constant Filter constant. Range 0.0 to 1.0, where 1.0 gives the unfiltered value.
 */
#define filter_low_pass_fast(value, sample, filter_constant) (value -= (filter_constant) * ((value) - (sample)))

#endif //QUEFOC_DEV_FILTER_H
