#include "ch32v30x.h"

#include "hardware.h"

void hardware_encoder_spi_boot(){
    SPI_InitTypeDef SPI_InitStructure={0};

    RCC_APB1PeriphClockCmd( ENCODER_SPI_RCC , ENABLE );


    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
    // mode=1(CPOL=0, CPHA=1)
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;

    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    // PCLK1=HCLK/APB1_P=72M
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    //SPI_InitStructure.SPI_CRCPolynomial = 7;

    SPI_Init( ENCODER_SPIx, &SPI_InitStructure );

    //SPI_SSOutputCmd( ENCODER_SPIx, ENABLE );
//    SPI_SSOutputCmd( ENCODER_SPIx, DISABLE );
    SPI_Cmd( ENCODER_SPIx, ENABLE );

}

void spi_write(SPI_TypeDef *SPIx, u16 data){
    while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) {}
    SPI_I2S_SendData(SPIx, data);
    while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) {}
}

u16 spi_read(SPI_TypeDef *SPIx){
    while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET) {}
    return SPI_I2S_ReceiveData(SPIx);
}

u16 spi_write_read(SPI_TypeDef *SPIx, u16 data){
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    spi_write(SPIx, data);
//    GPIO_SetBits(GPIOB, GPIO_Pin_12);
//    hardware_delay_us(1);
////
//    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    u16 raw_data = spi_read(SPIx);
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
    //hardware_delay_us(2);

    return raw_data;
}

// 奇偶校验，判断是否有偶数个1
bool check_parity(u16 v)
{
    v ^= v >> 8;
    v ^= v >> 4;
    v ^= v >> 2;
    v ^= v >> 1;
    return v & 1;
}

bool hardware_encoder_spi_data(u16 *data){
    // SPI Read Data Frame
    // [15] [14]        [13:0]
    // PARC EF(ERRO-1)  Data
    u16 raw_data = spi_write_read(ENCODER_SPIx, 0xffff);
    //for(unsigned int j=0;j<0xfffffff;++j);

//    spi_write_read(ENCODER_SPIx, 0xffff);
//    u16 raw_data = spi_write_read(ENCODER_SPIx, 0);



    if(check_parity(raw_data)){
        return 0;
    }else if((raw_data>>14) & 1){
        // if EF=1
        *data = raw_data & 0x3fff;
        return 1; // FIXME
    }else{
        *data = raw_data & 0x3fff;
    }
    //SPI_Cmd( ENCODER_SPIx, DISABLE);

    return true;
}
