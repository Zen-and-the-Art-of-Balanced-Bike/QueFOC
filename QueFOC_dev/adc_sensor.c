//
// Created by 24216 on 2022/12/23.
//

#include "adc_sensor.h"
#include "fast_math.h"
#include "string.h"

/*!
 * @brief Initialize an ADC sensor object
 * @param measure_freq                  ADC measure frequency                               [Hz]
 * @param resolution_bit                ADC resolution bit
 * @param i_op_amp_gain                 Phase current OP-AMP gain, hardware specific
 * @param i_op_amp_offset               Phase current OP-AMP offset, hardware specific      [V]
 * @param v_bus_gain                    VBus voltage gain, hardware specific
 * @param shunt_resistance              Shunt resistance                                    [OUM]
 * @param hardware_boot                 Hardware specific
 * @param hardware_adc_read_phase_a     Hardware specific
 * @param hardware_adc_read_phase_b     Hardware specific
 * @param hardware_adc_read_phase_c     Hardware specific
 * @param hardware_adc_read_vbus        Hardware specific
 * @param hardware_adc_read_vgnd        Hardware specific
 */
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
                     uint16_t   (*hardware_adc_read_vgnd)(void)){
    memset(adc, 0, sizeof(ADC_sensor));
    adc->measure_freq                 =   measure_freq;
    adc->measure_period               =   (1 / (float)measure_freq);
    adc->resolution                   =   (1 << (resolution_bit));
    adc->hardware_boot                =   hardware_boot;
    adc->hardware_adc_read_phase_a    =   hardware_adc_read_phase_a;
    adc->hardware_adc_read_phase_b    =   hardware_adc_read_phase_b;
    adc->hardware_adc_read_phase_c    =   hardware_adc_read_phase_c;
    adc->hardware_adc_read_vbus       =   hardware_adc_read_vbus;
    adc->hardware_adc_read_vgnd       =   hardware_adc_read_vgnd;
    adc->i_op_amp_offset_a            =   0;
    adc->i_op_amp_offset_b            =   0;
    adc->i_op_amp_offset_c            =   0;

    adc->i_scale                      =   3.3f / (float)adc->resolution / shunt_resistance / i_op_amp_gain;
    adc->vbus_scale                   =   (v_bus_gain * 3.3f / (float)adc->resolution);
    adc->i_op_amp_offset_theory       =   (uint16_t)(i_op_amp_offset/3.3f*(float)adc->resolution);

    //FIXME
    adc->v_bus_raw = adc->v_bus = 12;
}

void adc_boot(ADC_sensor* adc){
    adc->hardware_boot();

    // wait until v_bus stable
    // FIXME about threshold
    while(ABS(adc->v_bus - adc->v_bus_raw) > 5 * 0.05f){}

}

void adc_update(ADC_sensor* adc){
    adc->i_a = (float)(adc->hardware_adc_read_phase_a() - adc->i_op_amp_offset_a) * adc->i_scale;
    adc->i_b = (float)(adc->hardware_adc_read_phase_b() - adc->i_op_amp_offset_b) * adc->i_scale;
    adc->i_c = (float)(adc->hardware_adc_read_phase_c() - adc->i_op_amp_offset_c) * adc->i_scale;
    adc->v_bus_raw = (float)(adc->hardware_adc_read_vbus()) * adc->vbus_scale;
    LOW_PASS_FAST(adc->v_bus, adc->v_bus_raw, 0.05f);

    // FIXME
    adc->v_bus = adc->v_bus_raw = 12.0f;

    adc->v_gnd = (float)(adc->hardware_adc_read_vgnd());
}
