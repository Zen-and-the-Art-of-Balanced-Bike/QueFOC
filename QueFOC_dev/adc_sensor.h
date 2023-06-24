//
// Created by 24216 on 2022/12/23.
//

#ifndef QUEFOC_DEV_ADC_SENSOR_H
#define QUEFOC_DEV_ADC_SENSOR_H

#include "pwm.h"
#include "inttypes.h"

/*! @brief ADC Sensor Object */
typedef struct {
    // ADC measure frequency    [Hz]
    uint32_t    measure_freq;
    float       measure_period;
    // ADC resolution
    uint32_t    resolution;

    float       i_scale;
    float       vbus_scale;

    float       gain_a, gain_b, gain_c;
    uint16_t    i_op_amp_offset_theory;
    uint16_t    i_op_amp_offset_a, i_op_amp_offset_b, i_op_amp_offset_c;


    // phase current
    float i_a, i_b, i_c;

    float i_bus;
    // Voltage
    float v_bus, v_gnd;
    float v_bus_raw; // before low pass



    /* Hardware specific */
    void        (*hardware_boot)(void);
    uint16_t    (*hardware_adc_read_phase_a)(void);
    uint16_t    (*hardware_adc_read_phase_b)(void);
    uint16_t    (*hardware_adc_read_phase_c)(void);
    uint16_t    (*hardware_adc_read_vbus)(void);
    uint16_t    (*hardware_adc_read_vgnd)(void);

} ADC_sensor;


void adc_sensor_init(ADC_sensor* adc,
                     uint32_t   measure_freq,
                     uint8_t    resolution_bit,
                     float      i_op_amp_gain,
                     float      i_op_amp_offset,
                     float      v_bus_gain,
                     float      shunt_resistance,
                     void       (*hardware_boot)(void),
                     uint16_t   (*hardware_adc_read_phase_a)(void),
                     uint16_t   (*hardware_adc_read_phase_b)(void),
                     uint16_t   (*hardware_adc_read_phase_c)(void),
                     uint16_t   (*hardware_adc_read_vbus)(void),
                     uint16_t   (*hardware_adc_read_vgnd)(void));

void adc_boot(ADC_sensor* adc);
void adc_update(ADC_sensor* adc);


#endif //QUEFOC_DEV_ADC_SENSOR_H
