/*
 * hardware.h
 *
 *  Created on: Dec 31, 2022
 *      Author: 24216
 */

#ifndef HARDWARE_HARDWARE_H_
#define HARDWARE_HARDWARE_H_

#include "ch32v30x.h"

#define bool            int
#define false           0
#define true            1

#define USE_USB_CDC                 0

/* SYSTEM */
#define PWM_FREQUENCY               20000


/* ADC */
/* ADC_CLK = PCLK2 / ADC_CLK_DIV
 * Note that CH32V30x ADCCLLK < 14 MHz
 */
#define ADC_CLK_DIV RCC_PCLK2_Div6
//#define ADC_CLK_DIV RCC_PCLK2_Div8
// FIXME
// SAMPLE_TIME_CLK + 12.5 * ADC_CLK
// 14 * (1/12)MHz = 1.16us
#define ADC_SAMPLE_TIME             ADC_SampleTime_7Cycles5
#define ADC_TRIGGER                 ADC_ExternalTrigInjecConv_Ext_IT15_TIM8_CC4

/* TIM */
/* PWM */
#define TIM_PWM                     TIM8
#define TIM_PWM_RCC                 RCC_APB2Periph_TIM8
#define TIM_PWM_CLK                 SystemCoreClock
#define PWM_PERIOD_CYCLES           (uint16_t)((TIM_PWM_CLK/((uint32_t)(PWM_FREQUENCY)))&0xFFFE)
#define HALF_PWM_PERIOD_CYCLES      (uint16_t)(PWM_PERIOD_CYCLES/2U)
#define TIM_ADC_SAMPLE_TIMING       5
/* IIF(ABZ) */
#define TIM_IIF                     TIM4
#define TIM_IIF_RCC                 RCC_APB1Periph_TIM4


/* User configuration */
#define KV                          500
#define POLE_PAIRS                  7
#define INERTIA                     0
#define CPR                         (1<<14)
#define ADC_RESOLUTION_BIT          12
#define V_BUS_GAIN                  15
#define SHUNT_RESISTANCE            0.001f
#define I_OP_AMP_OFFSET             1.65f
#define I_OP_AMP_GAIN               30.0f
#define CALIB_CURRENT               1.0f
#define CALIB_VOLTAGE               1.0f
#define I_MAX                       10.0f
// FIXME
// IR2136 290ns
#define DEAD_TIME_NS                0
#define PWM_DEADTIME                (int)(DEAD_TIME_NS/(1.0f*1000/(TIM_PWM_CLK/1000000)))

#define ENCODER_SPIx                SPI2
#define ENCODER_SPI_RCC             RCC_APB1Periph_SPI2



/* GPIO */
void hardware_motor_gpio_boot();
void hardware_encoder_gpio_boot();

/* NVIC */
void hardware_nvic_boot();

/* DMA */
void hardware_dma_boot();

/* DELAY */
void hardware_delay_init(void);
void hardware_delay_us(uint32_t n);
void hardware_delay_ms(uint32_t n);

/* ADC */
void hardware_adc_boot();
u16 hardware_adc_read_phase_a();
u16 hardware_adc_read_phase_b();
u16 hardware_adc_read_phase_c();
u16 hardware_adc_read_vbus(void);
u16 hardware_adc_read_vgnd(void);

/* PWM */
void hardware_pwm_boot(void);
void hardware_set_pwm_duty_ch_a(float duty);
void hardware_set_pwm_duty_ch_b(float duty);
void hardware_set_pwm_duty_ch_c(float duty);

/* USART */
void hardware_usart3_boot(void);
void hardware_usart3_send_str(const char* data);

void trans_data_package_float(const float data, void (*send)(uint8_t));
void rec_data_package_float(const uint8_t rec, void (*callback)(float));

void hardware_uart4_boot(void);
void hardware_uart4_send_u8(const u8 data);
void hardware_uart4_callback(float data);

/* USB */
void hardware_usb_fs_cdc_boot(void);
void hardware_usb_cdc_send(const char* data);

/* IIF(ABZ) */
void hardware_encoder_IIF_boot(void);
uint16_t hardware_encoder_IIF_query(void);

/* SPI */
void hardware_encoder_spi_boot();
bool hardware_encoder_spi_data(u16 *data);

#endif /* HARDWARE_HARDWARE_H_ */
