/*
 * gpio.c
 *
 *  Created on: Dec 25, 2022
 *      Author: 24216
 */

#include "ch32v30x.h"
#include "hardware.h"

void hardware_motor_gpio_boot(void){
    GPIO_InitTypeDef GPIO_InitStructure={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC , ENABLE );
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /*
     * ADC Pin
     * PA0  ADC0    ADC_CHANNEL_0   Injec   phase A current
     * PA1  ADC1    ADC_CHANNEL_1   Injec   phase B current
     * PA2  ADC1    ADC_CHANNEL_2   Injec   phase C current
     * PA3  ADC0    ADC_CHANNEL_3   Reg     bus voltage
     * PA4  ADC1    ADC_CHANNEL_4   Reg     GND
     */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*  Configure ADCx_ETRGINJ_REMAP */
    GPIO_PinRemapConfig(GPIO_Remap_ADC1_ETRGINJ, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_ADC2_ETRGINJ, ENABLE);

    /*
     * PWM Pin
     * PC6  TIM8_CH1    AH
     * PC7  TIM8_CH2    BH
     * PC8  TIM8_CH3    CH
     * PC9  TIM8_CH4    Trigger for ADC
     * PA7  TIM8_CH1N   AL
     * PB0  TIM8_CH2N   BL
     * PB1  TIM8_CH3N   CL
     */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init( GPIOC, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init( GPIOA, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init( GPIOB, &GPIO_InitStructure );


    /*
     * USART Pin
     * PB10 USART3_TX
     * PB11 USART3_RX
     */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*
     * UART4 Pin
     * PC10 UART4_TX
     * PC11 UART4_RX
     */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /*
     * SPI3
     * PA15 SPI3_NSS
     * PB3  SPI3_SCK
     * PB4  SPI3_MISO
     * PB5  SPI3_MOSI
     */



    /*
     * PC3  ENA
     * PC4  ENB
     * PC5  ENC
     *
     */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /*
     * I2C1
     * PB6  I2C1_SCL
     * PB7  I2C1_SDA
     */

    /*
     * USB
     * PA11 OTG_FS_DM
     * PA12 OTG_FS_DP
     */

    /*
     * CAN1
     * PB8  CAN1_RX
     * PB9  CAN1_TX
     */

}

void hardware_encoder_gpio_boot(void){
    GPIO_InitTypeDef GPIO_InitStructure={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE );

    /*
     * SPI2
     * PB12 SPI2_NSS
     * PB13 SPI2_SCK
     * PB14 SPI2_MISO
     * PB15 SPI2_MOSI
     */
    // NSS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOB, &GPIO_InitStructure );
    GPIO_SetBits(GPIOB, GPIO_Pin_12);

    // CLK
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOB, &GPIO_InitStructure );

    // MISO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init( GPIOB, &GPIO_InitStructure );

    // MOSI
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOB, &GPIO_InitStructure );
}

