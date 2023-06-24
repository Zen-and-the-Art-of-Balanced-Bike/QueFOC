/*
 * usart.c
 *
 *  Created on: Dec 31, 2022
 *      Author: 24216
 */

#include "hardware.h"
#include "ch32v30x.h"

void hardware_usart3_boot(void){
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART3, &USART_InitStructure);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

    USART_Cmd(USART3, ENABLE);
}

void hardware_uart4_boot(void){
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(UART4, &USART_InitStructure);
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

    USART_Cmd(UART4, ENABLE);
}

void hardware_usart3_send_str(const char* data){
    uint32_t i=0;
    while(data[i]!='\0'){
        USART_SendData(USART3, (u16)data[i]);
        /* waiting for sending finish */
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET){}
        i++;
    }
}

void hardware_uart4_send_u8(const u8 data){
    USART_SendData(UART4, data);
    /* waiting for sending finish */
    while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET){}
}

void trans_data_package_float(const float data, void (*send)(uint8_t)){
    union float_4u8{
        float f;
        uint8_t i8[4];
    } f2i;
    f2i.f = data;
    union i16_2i8{
        uint16_t i16;
        uint8_t i8[2];
    } i162i8;
    // frame start
    i162i8.i16 = 0xeb90;
    send(i162i8.i8[0]);
    send(i162i8.i8[1]);
    for(uint8_t i=0;i<4;++i)
        send(f2i.i8[i]);
}

void rec_data_package_float(const uint8_t rec, void (*callback)(float)){
    static union float_4u8{
        float f;
        uint8_t i8[4];
    } i2f;
    static uint8_t is_big_end = 0;
    static uint8_t rec_pre = 0;
    static uint8_t data_index = 4;
    if(data_index==4){
        if(rec==0x90&&rec_pre==0xeb){
            is_big_end = 0;
            data_index = 0;
        }
        else if(rec==0xeb&&rec_pre==0x90){
            is_big_end = 1;
            data_index = 0;
        }
        // printf("%x %x\n", rec, rec_pre);
    }else{
        i2f.i8[(is_big_end?(data_index++):(3-(data_index++)))] = rec;
        // printf("data=%x,index=%d\n", rec,data_index-1);
        if(data_index==4) callback(i2f.f);
    }
    rec_pre = rec;
}
