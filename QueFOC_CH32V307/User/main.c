#include "motor.h"
#include "hardware.h"
#include "foc.h"
#include "fast_math.h"
#include "oled.h"

Motor motorQ={0};
Encoder encoderQ={0};
ADC_sensor adcQ={0};
PWM pwmQ={0};

Cmder cmder={0};
Monitor monitor={0};


void hardware_basic_boot(){
    hardware_motor_gpio_boot();
    hardware_nvic_boot();
    hardware_dma_boot();
}

void hardware_encoder_boot(){
    hardware_encoder_gpio_boot();
    hardware_encoder_spi_boot();
}

void hardware_uart4_callback(float data){
    motorQ.vel_input = data;
//    monitor_prt(&monitor, "cmd.vel=%.7f\n", data);
}


int main(void)
{
	//USART_Printf_Init(115200);
    hardware_delay_init();

#if USE_USB_CDC
    monitor_init(&monitor,
            hardware_usb_fs_cdc_boot, hardware_usb_cdc_send);
#else
    monitor_init(&monitor,
            hardware_usart3_boot, hardware_usart3_send_str);
#endif
    monitor_boot(&monitor);
    monitor_prt(&monitor, "SystemClk:%d\r\n", SystemCoreClock);

    encoder_init(&encoderQ, PWM_FREQUENCY, CPR, POLE_PAIRS, hardware_encoder_boot, hardware_encoder_spi_data);

	adc_sensor_init(&adcQ,
	        PWM_FREQUENCY, ADC_RESOLUTION_BIT,
	        I_OP_AMP_GAIN, I_OP_AMP_OFFSET, V_BUS_GAIN, SHUNT_RESISTANCE,
	        hardware_adc_boot,
	        hardware_adc_read_phase_a, hardware_adc_read_phase_b, hardware_adc_read_phase_c,
	        hardware_adc_read_vbus, hardware_adc_read_vgnd);
	pwm_init(&pwmQ,
	        PWM_FREQUENCY,
	        hardware_pwm_boot,
	        hardware_set_pwm_duty_ch_a, hardware_set_pwm_duty_ch_b, hardware_set_pwm_duty_ch_c);
	cmder_init(&cmder,
	        '\n', true,
	        hardware_usart3_boot, hardware_usart3_send_str);
	motor_init(&motorQ,
	        'Q', KV, CALIB_CURRENT, CALIB_VOLTAGE,
	        PWM_FREQUENCY*0.1, INERTIA,
	        2, 5, 12, 28,
	        100, I_MAX,
	        &encoderQ, &adcQ, &pwmQ, &cmder,
	        hardware_basic_boot);



	cmder_boot(&cmder);

	hardware_delay_ms(500);

	//encoder_boot(&encoderQ);

	motor_boot(&motorQ);

	cmder_add_motor(&cmder, &motorQ);

	//hardware_encoder_IIF_boot();


	monitor_prt(&monitor, "SystemClk:%d\nv_bus=%f", SystemCoreClock, motorQ.adc->v_bus);

	hardware_delay_ms(500);

	/* LED Blink */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE );
	GPIO_InitTypeDef GPIO_InitStructure={0};
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_12);

    GPIO_SetBits(GPIOC, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
    //GPIO_ResetBits(GPIOB, GPIO_Pin_12);

    motor_update_vel_ctrl_param(&motorQ, 0.1, 0.01);
    hardware_uart4_boot();

//    OLED_Init();
//    OLED_Clear();
//    OLED_ShowChar(10,20,'B',16);
//    monitor_prt(&monitor, "OLED INIT\n");

//
//    while(1){
//        trans_data_package_float(1.23456f, hardware_uart4_send_u8);
//        hardware_delay_ms(5);
//        trans_data_package_float(6.54321f, hardware_uart4_send_u8);
//        hardware_delay_ms(5);
//    }


	while(1){


//	    led ^= 1; b
//	    if(led)
//	        GPIO_ResetBits(GPIOC, GPIO_Pin_12);
//	    else
//	        GPIO_SetBits(GPIOC, GPIO_Pin_12);
//
//	    monitor_prt(&monitor, "%d\n", motorQ.state);
	    if(motorQ.state == MS_RUN_VELOCITY){
	        GPIO_SetBits(GPIOC, GPIO_Pin_12);
	        trans_data_package_float(motorQ.encoder->vel, hardware_uart4_send_u8);

//	        hardware_delay_ms(5);

//	        monitor_prt(&monitor, "%d %.3f %.3f %.3f\n", encoderQ.data_raw, (encoderQ.data_raw-encoderQ.offset)*1.0f*PIx2*7/16384, encoderQ.phase, encoderQ.phase*360/PIx2);


//	        if(foc_voltage_control(&motorQ, 0, 1, (encoderQ.data_raw-encoderQ.offset)*1.0f*PIx2*7/16384))
//	            pwm_sync_duty(motorQ.pwm);
//	        if(foc_voltage_control(&motorQ, 0, 1, encoderQ.phase))
//	            pwm_sync_duty(motorQ.pwm);
//	        monitor_prt(&monitor, "%.3f %.3f\n", encoderQ.phase, (encoderQ.data_raw-encoderQ.offset)*PIx2*7/16384);

//	        monitor_prt(&monitor, "%.3f,%.3f,%.3f,%.3f\n", motorQ.i_d, 0.0f, motorQ.i_q, motorQ.i_q_set);
//	        monitor_prt(&monitor, "%.3f,%.3f\n", motorQ.vel_sp, motorQ.encoder->vel);



//	        monitor_prt(&monitor, "%.3f,%.3f,%.3f,%.3f\n", motorQ.i_q, debug_id_set, motorQ.encoder->vel, motorQ.encoder->pos);
//	        monitor_prt(&monitor, "%.3f,%.3f\n", motorQ.encoder->vel, motorQ.i_q_set);
//	        monitor_prt(&monitor, "%.3f,%.3f,%.3f,%.3f\n", motorQ.i_q, motorQ.i_q_set, motorQ.encoder->vel, motorQ.vel_input);
	        hardware_delay_ms(5);


	    }else {

	        GPIO_ResetBits(GPIOC, GPIO_Pin_12);
        }



	}

}
