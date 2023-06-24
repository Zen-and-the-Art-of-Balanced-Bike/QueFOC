/*
 * it.c
 *
 *  Created on: Dec 26, 2022
 *      Author: 24216
 */

#include "ch32v30x.h"
#include "motor.h"
#include "hardware.h"

extern Cmder cmder;
extern Monitor monitor;
extern Motor motorQ;

void ADC1_2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      ADC1_2_IRQHandler
 *
 * @brief   ADC1_2 Interrupt Service Function.
 *
 * @return  none
 */
void ADC1_2_IRQHandler()
{

    /*if(ADC_GetITStatus( ADC1, ADC_IT_JEOC) == SET && ADC_GetITStatus(ADC2, ADC_IT_JEOC ) == SET){
        interrupt_adc_done(&motorQ);
        ADC_ClearITPendingBit( ADC1, ADC_IT_JEOC);
        ADC_ClearITPendingBit( ADC2, ADC_IT_JEOC);
    }*/
    if(ADC_GetITStatus(ADC1, ADC_IT_JEOC ) == SET){
        interrupt_adc_done(&motorQ);

    }
    ADC_ClearITPendingBit( ADC1, ADC_IT_JEOC);

}

void DMA1_Channel1_IRQHandler(void)   __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      DMA1_Channel1_IRQHandler
 *
 * @brief   This function handles DMA1 Channel1 exception.
 *
 * @return  none
 */
extern u32 vbus_gnd_raw_DMA;
extern u16 vbus_DMA;
extern u16 vgnd_DMA;

void DMA1_Channel1_IRQHandler()
{
    if(DMA_GetITStatus(DMA1_IT_TC1)==SET ){
        DMA_ClearITPendingBit(DMA1_IT_GL1);
        // In RegSimulMode, ADC1 and ADC2 data stored in ADC1_RDATAR by DMA
        vbus_DMA = vbus_gnd_raw_DMA&0xffff;
        vgnd_DMA = (vbus_gnd_raw_DMA>>16)&0xffff;
    }
}


void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART3_IRQHandler(void)
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        u16 data = USART_ReceiveData(USART3);
        interrupt_receive_one_char(&cmder, (u8)data);
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    }
}

void UART4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void UART4_IRQHandler(void)
{
    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
        u16 data = USART_ReceiveData(UART4);
        rec_data_package_float(data, hardware_uart4_callback);
        USART_ClearITPendingBit(UART4, USART_IT_RXNE);
    }
}
