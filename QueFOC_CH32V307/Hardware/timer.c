/*
 * timer.c
 *
 *  Created on: Dec 25, 2022
 *      Author: 24216
 */

#include "hardware.h"



void hardware_pwm_boot(void){

    TIM_OCInitTypeDef TIM_OCInitStructure={0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};
    TIM_BDTRInitTypeDef TIM_BDTRInitStructure={0};

    /* TIM8 */

    RCC_APB2PeriphClockCmd( TIM_PWM_RCC, ENABLE );

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
    // ARR
    TIM_TimeBaseInitStructure.TIM_Period = HALF_PWM_PERIOD_CYCLES;
    // set CCxIF 1 when counting up
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned2;
    TIM_TimeBaseInit( TIM_PWM, &TIM_TimeBaseInitStructure);

    /* CH 1, 2, 3 */
    // PWM1 Mode: OCxREF set to high when TIMx_CNT < TIMx_CCRx
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    //
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    // duty 0% (CCR)
    TIM_OCInitStructure.TIM_Pulse = 0;
    // CH1,2,3 set to PWM1 mode
    TIM_OC1Init( TIM_PWM, &TIM_OCInitStructure );
    TIM_OC2Init( TIM_PWM, &TIM_OCInitStructure );
    TIM_OC3Init( TIM_PWM, &TIM_OCInitStructure );

    /* CH 4 */
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    // PWM2 Mode: OCxREF set to low when TIMx_CNT < TIMx_CCRx
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    // Trigger for ADC , in order to sense low-side current in the right time
    TIM_OCInitStructure.TIM_Pulse = HALF_PWM_PERIOD_CYCLES-TIM_ADC_SAMPLE_TIMING;
    // CH4 set to PWM2 mode
    TIM_OC4Init( TIM_PWM, &TIM_OCInitStructure );

    /* config Break, DeadTime */
    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStructure.TIM_DeadTime = PWM_DEADTIME;
    TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
    TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig( TIM_PWM, &TIM_BDTRInitStructure );

    TIM_CtrlPWMOutputs(TIM_PWM, ENABLE );
    /* config shadow register */
    TIM_OC1PreloadConfig( TIM_PWM, TIM_OCPreload_Enable );
    TIM_OC2PreloadConfig( TIM_PWM, TIM_OCPreload_Enable );
    TIM_OC3PreloadConfig( TIM_PWM, TIM_OCPreload_Enable );
    TIM_OC4PreloadConfig( TIM_PWM, TIM_OCPreload_Enable );
    TIM_ARRPreloadConfig( TIM_PWM, ENABLE );

    TIM_Cmd( TIM_PWM, ENABLE );
}

void hardware_set_pwm_duty_ch_a(float duty){
    TIM_SetCompare1( TIM_PWM , (u16)(duty*(float)HALF_PWM_PERIOD_CYCLES));
}
void hardware_set_pwm_duty_ch_b(float duty){
    TIM_SetCompare2( TIM_PWM , (u16)(duty*(float)HALF_PWM_PERIOD_CYCLES));
}
void hardware_set_pwm_duty_ch_c(float duty){
    TIM_SetCompare3( TIM_PWM , (u16)(duty*(float)HALF_PWM_PERIOD_CYCLES));
}

void hardware_encoder_IIF_boot(void){
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = {0};
    TIM_ICInitTypeDef TIM_ICInitStructure = {0};

    RCC_APB1PeriphClockCmd(TIM_IIF_RCC,ENABLE);


    TIM_DeInit(TIM_IIF);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_Period = 0xffff;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM_IIF, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(TIM_IIF, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);   // TIM_ICPolarity_Rising/Falling

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter =6;
    TIM_ICInit(TIM_IIF, &TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM_IIF, &TIM_ICInitStructure);

    TIM_SetCounter(TIM_IIF,0);
    TIM_Cmd(TIM_IIF, ENABLE);
}

uint16_t hardware_encoder_IIF_query(void){
    uint16_t res = TIM_GetCounter(TIM_IIF);
    TIM_SetCounter(TIM_IIF,0);
    return res;
}
