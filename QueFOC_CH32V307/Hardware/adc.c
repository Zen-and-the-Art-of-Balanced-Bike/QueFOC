/*
 * adc.c
 *
 *  Created on: Dec 25, 2022
 *      Author: 24216
 */

#include "ch32v30x.h"
#include "adc_sensor.h"

#include "hardware.h"


static s16 ADC1_calibrattion, ADC2_calibrattion;

// DMA
u16 vbus_DMA;
u16 vgnd_DMA;

void hardware_adc_boot(void){
    /*
     * ADC Pin
     * PA0  ADC1    ADC_CHANNEL_0   Injec   phase C current
     * PA1  ADC1    ADC_CHANNEL_1   Injec   phase B current
     * PA2  ADC2    ADC_CHANNEL_2   Injec   phase A current
     * PA3  ADC1    ADC_CHANNEL_3   Reg     bus voltage
     * PA4  ADC2    ADC_CHANNEL_4   Reg     GND
     */

    ADC_InitTypeDef ADC_InitStructure={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1 , ENABLE );
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC2 , ENABLE );

    RCC_ADCCLKConfig( ADC_CLK_DIV );


    ADC_DeInit(ADC1);
    ADC_DeInit(ADC2);

    /* ADC 1 */

    // see CH32V30x EVT code example: DualADC_Combined_RegInjectionSimul
    ADC_InitStructure.ADC_Mode = ADC_Mode_RegInjecSimult;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    // Enable continuous mode
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    // Regular software trigger
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_InitStructure.ADC_OutputBuffer = ADC_OutputBuffer_Disable;
    ADC_InitStructure.ADC_Pga = ADC_Pga_1;

    ADC_Init(ADC1, &ADC_InitStructure);

    // VBus ADC_CHANNEL_3   Regular
    // FIXME ADC Sample time
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SAMPLE_TIME );


    ADC_InjectedSequencerLengthConfig(ADC1, 3);
    // FIXME ADC Sample time
    // IC   ADC_CHANNEL_0   Injected
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SAMPLE_TIME );
    // IB   ADC_CHANNEL_1
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SAMPLE_TIME );

    ADC_InjectedChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SAMPLE_TIME );



    // Set TIM CH4 as external trigger
    ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_TRIGGER );
    // Enable external trigger injected conversion
    ADC_ExternalTrigInjectedConvCmd(ADC1, ENABLE);

    // ADC_IT_JEOC - End of injected conversion interrupt
    ADC_ITConfig( ADC1, ADC_IT_JEOC, ENABLE);

    // Enable DMA for VBus, GND
    ADC_DMACmd(ADC1, ENABLE);

    ADC_Cmd(ADC1, ENABLE);

    /* Calibration */
    // Disable buffer when calibrating
    ADC_BufferCmd(ADC1, DISABLE);   //disable buffer
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    ADC1_calibrattion = Get_CalibrationValue(ADC1);
    ADC_BufferCmd(ADC1, ENABLE);   //enable buffer


    /* ADC 2 */

    ADC_Init(ADC2, &ADC_InitStructure);
    // GND  ADC_CHANNEL_4
    ADC_RegularChannelConfig(ADC2, ADC_Channel_4, 1, ADC_SAMPLE_TIME );

    //ADC_InjectedSequencerLengthConfig(ADC2, 1);

    // IA   ADC_CHANNEL_2
    //ADC_InjectedChannelConfig(ADC2, ADC_Channel_2, 1, ADC_SAMPLE_TIME );
    //ADC_InjectedChannelConfig(ADC2, ADC_Channel_1, 1, ADC_SAMPLE_TIME );

    //ADC_ExternalTrigInjectedConvConfig(ADC2,ADC_ExternalTrigInjecConv_None );
    //ADC_SoftwareStartConvCmd(ADC2, ENABLE);
    //ADC_ExternalTrigInjectedConvConfig(ADC2, ADC_ExternalTrigInjecConv_None );
    //ADC_ExternalTrigInjectedConvCmd(ADC2, ENABLE);

    // ADC_IT_JEOC - End of injected conversion interrupt
    //ADC_ITConfig(ADC2, ADC_IT_JEOC, ENABLE);

    ADC_Cmd(ADC2, ENABLE);

    ADC_BufferCmd(ADC2, DISABLE);   //disable buffer
    ADC_ResetCalibration(ADC2);
    while(ADC_GetResetCalibrationStatus(ADC2));
    ADC_StartCalibration(ADC2);
    while(ADC_GetCalibrationStatus(ADC2));
    ADC2_calibrattion = Get_CalibrationValue(ADC2);
    ADC_BufferCmd(ADC2, ENABLE);   //enable buffer


    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);
    // Note that we have ENABLED ADC1, ADC2 and their calibration
}

// CH32V30x EVT ADC code example
static inline u16 get_conversion_val_ADC1(s16 raw){
    // CH32V30x ADC resolution 12bit, 2^12-1 = 4095
    s16 t = raw + ADC1_calibrattion;
    if(t<0) return 0;
    if(t>4095||raw==4095) return 4095;
    return t;
}

static inline u16 get_conversion_val_ADC2(s16 raw){
    // CH32V30x ADC resolution 12bit, 2^12-1 = 4095
    s16 t = raw + ADC2_calibrattion;
    if(t<0) return 0;
    if(t>4095||raw==4095) return 4095;
    return t;
}

/*
u16 hardware_adc_read_phase_c(void){
    u16 raw = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
    return get_conversion_val_ADC1(raw);
}
u16 hardware_adc_read_phase_b(void){
    u16 raw = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2);
    return get_conversion_val_ADC1(raw);
}
u16 hardware_adc_read_phase_a(void){
    u16 raw = ADC_GetInjectedConversionValue(ADC2, ADC_InjectedChannel_1);
    return get_conversion_val_ADC2(raw);
}
*/
u16 hardware_adc_read_phase_c(void){
    u16 raw = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
    return get_conversion_val_ADC1(raw);
}
u16 hardware_adc_read_phase_b(void){
    u16 raw = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2);
    return get_conversion_val_ADC1(raw);
}
u16 hardware_adc_read_phase_a(void){
    u16 raw = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_3);
    return get_conversion_val_ADC1(raw);
}

u16 hardware_adc_read_vbus(void){
    return get_conversion_val_ADC1(vbus_DMA);
}
u16 hardware_adc_read_vgnd(void){
    return get_conversion_val_ADC2(vgnd_DMA);
}
