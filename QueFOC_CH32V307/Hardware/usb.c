/*
 * usb.c
 *
 *  Created on: Jan 12, 2023
 *      Author: 24216
 */
#include "hardware.h"

#include "ch32v30x_usbotg_device.h"


void usb_cdc_send_pack(const uint8_t *p, uint32_t length)
{
    uint32_t i = 0;

    for(i=0; i<length; i++)
    {
       pEP2_IN_DataBuf[i] = p[i];
    }
    DevEP2_IN_Deal(length);

    //等待发送完成
    while(!(USBOTG_FS->UEP2_TX_CTRL&USBHD_UEP_T_RES1));

    // bUEP_T_RES1 & bUEP_T_RES0: handshake response type for USB endpoint X transmittal (IN)
    // 00: DATA0 or DATA1 then expecting ACK (ready)
    // 01: DATA0 or DATA1 then expecting no response, time out from host, for non-zero endpoint isochronous transactions
    // 10: NAK (busy)
    // 11: TALL (error)
}

uint8_t buff[64];

void hardware_usb_cdc_send(const char* data){
    int i=0;
    while(data[i]!='\0'){
        int j=0;
        for(;data[i]!='\0'&&j<64;++i,++j)
            buff[j] = (uint8_t)data[i];
        usb_cdc_send_pack(buff, j);
    }

}


void hardware_usb_fs_cdc_boot(void)
{
    // 端点缓冲区初始化
    pEP0_RAM_Addr = EP0_DatabufHD;
    pEP1_RAM_Addr = EP1_DatabufHD;
    pEP2_RAM_Addr = EP2_DatabufHD;
    // 使能usb时钟
    USBOTG_RCC_Init();
    hardware_delay_ms(100);
    // usb设备初始化
    USBDeviceInit();
    EXTEN->EXTEN_CTR |= EXTEN_USBD_PU_EN;
    // 使能usb中断
    NVIC_EnableIRQ(OTG_FS_IRQn);
}
