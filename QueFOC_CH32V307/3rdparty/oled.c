#include "oled.h"
#include "oledfont.h"
#include "hardware.h"

// the storage format is as follow
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127
/**********************************************
 * IIC Start  I2CЭ��涨��SCL���ڸߵ�ƽʱ��SDA�ɸߵ��ͱ仯�������ź�����ʼ�źš�
 * ���豸��ʼ����ͨѶͨ����ʼ����.��ʼ����������SCL�ߵ�ƽ�ڼ䣬SDA����һ���½��ص����䡣
**********************************************/
void IIC_Start()//I2C�����źţ���ʼSCL��SDA����1��֮��SDA��0��SCL����0
{

    OLED_SCLK_Set();
    OLED_SDIN_Set();
    OLED_SDIN_Clr();
    OLED_SCLK_Clr();
}

/**********************************************
 * IIC Stop  I2CЭ��涨��SCL���ڸߵ�ƽ��SDA�ɵ͵��߱仯�������ź���ֹͣ�źš�
 * дģʽ�ڽ��ܵ�ֹͣ�ź�֮�������ֹͣ�źŷ�����SCL�ߵ�ƽ�ڼ�SDA�������أ���Ϊֹͣ�źš�
**********************************************/
void IIC_Stop()//I2Cֹͣ�źţ���ʼSCL��1��SDA��0��֮��SDA��1
{
    OLED_SCLK_Set() ;
//  OLED_SCLK_Clr();
    OLED_SDIN_Clr();
    OLED_SDIN_Set();

}

/**********************************************
 * IIC Wait Ack  Ӧ���źų�����1���ֽڴ������֮�󣬼���9��SCLʱ�������ڣ�
 * ��ʱ������Ҫ�ͷ�SDA���ߣ������߿���Ȩ�����ӻ���
 * ����������������ã���ʱ����Ϊ�ߵ�ƽ��
 * ����ӻ���ȷ���յ����������������ݣ����SDA���ͣ���ʾӦ����Ӧ��
**********************************************/
void IIC_Wait_Ack()//I2CӦ���źţ�SCL��1����0���˴�ֻ�����9��SCLʱ������������һ��Ӧ�����ڣ���������Ӧ���ź�
{
    OLED_SCLK_Set() ;
    OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
 * һ��д��һλ�ֽڵ�һ�����ݣ�˳���ǴӸߵ���
 * д��һ�����ݺ����һ��SCL�ӵ͵����ٴӸߵ��͵ı仯�������Ѿ�������
 *
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
    unsigned char i;
    unsigned char m,da;
    da=IIC_Byte;
    OLED_SCLK_Clr();//SCLK����Ϊ�͵�ƽ
    for(i=0;i<8;i++)//�Ӹߵ������η�������
    {
        m=da;
        //  OLED_SCLK_Clr();
        m=m&0x80;
        if(m==0x80) //ȡ���λ����(0-��,1-��)
        {
            OLED_SDIN_Set();
        }
        else OLED_SDIN_Clr();
        da=da<<1;
        OLED_SCLK_Set();//SCLK����Ϊ�ߵ�ƽ
        OLED_SCLK_Clr();//SCLK����Ϊ�͵�ƽ
        }
}
/**********************************************
// IIC Write Command
 * OLED��IICд��Command�����������ֲ�
 * ��ַ��
 * b7 |  b6 |  b5 | b4 | b3 |  b2  | b1  | b0
 * 0  |  1  |  1  | 1  |  0 |  SA0 | SA0 | R/W#
 * ��SA0��λ�ṩһ������Ĵӵ�ַλ�������ǡ�0111_100�����ǡ�0111_101����
 * �����Ա�ѡ��ΪSSD1306�Ĵӵ�ַ��D/C#������ΪSA0Ϊ�ӵ�ַѡ��(�����ϱ����0x78������SA0����0)
 * ��R/W#��λ�Ǳ���������IICЭ��Ĺ���ģʽ��R/W#=1ʱ��Ϊ��ģʽ��R/W#=0ʱ��Ϊдģʽ��
 * д��0x78��˼��Ҫ��ӵ�ַΪ0x78(7λ��ַ,0111_100)���豸����д�����(R/W#=0)
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
    IIC_Wait_Ack();
   Write_IIC_Byte(0x00);            //write command
    IIC_Wait_Ack();
   Write_IIC_Byte(IIC_Command);
    IIC_Wait_Ack();
   IIC_Stop();
}
/**********************************************
// IIC Write Data
 * IICд����ʾ����
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //D/C#=0; R/W#=0
    IIC_Wait_Ack();
   Write_IIC_Byte(0x40);            //write data
    IIC_Wait_Ack();
   Write_IIC_Byte(IIC_Data);
    IIC_Wait_Ack();
   IIC_Stop();
}
/**********************************************
// OLED_WR_Byte
 * OLEDд��ָ���cmd����д��ʲô����
 * �궨���Ѿ�������ˣ�OLED_CMD  0   OLED_DATA  1
 * ��������Command����д����ʾ����
**********************************************/
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
    if(cmd)
    {
        Write_IIC_Data(dat);
    }
    else
    {
        Write_IIC_Command(dat);
    }
}


/********************************************
// fill_Picture ��
********************************************/
void fill_picture(unsigned char fill_Data)
{
    unsigned char m,n;
    for(m=0;m<8;m++)
    {
        OLED_WR_Byte(0xb0+m,0);     //page0-page1
        OLED_WR_Byte(0x00,0);       //low column start address
        OLED_WR_Byte(0x10,0);       //high column start address
        for(n=0;n<128;n++)
        {
            OLED_WR_Byte(fill_Data,1);
        }
    }
}


/********************************************
// OLED_Set_Pos
 * �趨OLED��ʾλ��
********************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f),OLED_CMD);
}

/********************************************
// OLED_Display_On
 * ��OLED��ʾ
********************************************/
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

/********************************************
// OLED_Display_Off
 * �ر�OLED��ʾ
********************************************/
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

/********************************************
// OLED_Clear
 * OLED������������д��0
********************************************/
void OLED_Clear(void)
{
    u8 i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);
        OLED_WR_Byte (0x00,OLED_CMD);
        OLED_WR_Byte (0x10,OLED_CMD);
        for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA);
    }
}

/********************************************
// OLED_On
 * OLED������������д��1
********************************************/
void OLED_On(void)
{
    u8 i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);
        OLED_WR_Byte (0x00,OLED_CMD);
        OLED_WR_Byte (0x10,OLED_CMD);
        for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA);
    }
}

//������ʾλ��ѡ�������С��
//x:0~127
//y:0~63
//size:16/12
/********************************************
// OLED_ShowChar
 * OLED��ʾ�ַ��������������Ϸ���ʾ����ѡ�������С
 * OLED���ϵ��·ֳɰ˸����򣬶�ÿ�����򵥶�д��
 * ÿ����������ҷֳ�0~127��128��С���򣬱����������
 * ÿ��С������������ϱ�Ϊ��λ(LSB D0)���±�Ϊ��λ(MSB D7)
********************************************/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{
    unsigned char c=0,i=0;
    c=chr-' ';
    if(x>Max_Column-1){x=0;y=y+2;}
    if(Char_Size ==16)
    {
        OLED_Set_Pos(x,y);
        for(i=0;i<8;i++)
            OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
        OLED_Set_Pos(x,y+1);
        for(i=0;i<8;i++)
            OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
    }
    else
    {
        OLED_Set_Pos(x,y);
        for(i=0;i<6;i++)
            OLED_WR_Byte(F6x8[c][i],OLED_DATA);
    }
}

/********************************************
// oled_pow
 * OLED�������ݶ�λ����
********************************************/
u32 oled_pow(u8 m,u8 n)
{
    u32 result=1;
    while(n--)result*=m;
    return result;
}

/********************************************
// OLED_ShowNum
 * OLED��ʾ���֣������������Ϸ���ʾ����ѡ�������С
********************************************/
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{
    u8 t,temp;
    u8 enshow=0;
    for(t=0;t<len;t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
                continue;
            }else enshow=1;

        }
        OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2);
    }
}

/********************************************
// OLED_ShowVI
 * OLED��ʾ������δ��ʹ��
********************************************/
void OLED_ShowVI(u8 x,u8 y,u32 num,u8 size2)
{
    OLED_ShowNum(x+size2*4-1,y,num%10,1,size2);
    OLED_ShowNum(x+size2*3-1,y,num/10%10,1,size2);
    OLED_ShowNum(x+size2*2-1,y,num/100%10,1,size2);
    OLED_ShowString(x+size2*1-1,y,".",size2);
    OLED_ShowNum(x-1,y,num/1000,1,size2);
}

/********************************************
// OLED_ShowString
 * OLED��ʾ�ַ����������������Ϸ���ʾ����ѡ�������С
********************************************/
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
    unsigned char j=0;
    while (chr[j]!='\0')
    {
        OLED_ShowChar(x,y,chr[j],Char_Size);
        x+=8;
        if(x>120)
        {
            x=0;
            y+=2;
        }
        j++;
    }
}

/********************************************
// OLED_DrawBMP
 * OLED��ʾͼƬ�������������Ϸ���ʾ����ѡ�������С
 * �����ⲿ�ֵ��õ�BMP���飬Ҫ��ʾ��ͼ����Ҫ��������
********************************************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{
    unsigned int j=0;
    unsigned char x,y;

    if(y1%8==0) y=y1/8;
    else y=y1/8+1;
    for(y=y0;y<y1;y++)
    {
        OLED_Set_Pos(x0,y);
        for(x=x0;x<x1;x++)
        {
            OLED_WR_Byte(BMP[j++],OLED_DATA);
        }
    }
}

/********************************************
// OLED_Init
 * OLED���庯������������ֲ�                                    (û�ҵ���Ӧλ��)
********************************************/
void OLED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure={0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);


    hardware_delay_ms(200);

    OLED_WR_Byte(0xAE,OLED_CMD);//--display off
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address
    OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
    OLED_WR_Byte(0x81,OLED_CMD); // contract control
    OLED_WR_Byte(0xFF,OLED_CMD);//--128
    OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap
    OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
    OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
    OLED_WR_Byte(0x00,OLED_CMD);//

    OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
    OLED_WR_Byte(0x80,OLED_CMD);//

    OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
    OLED_WR_Byte(0x05,OLED_CMD);//

    OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
    OLED_WR_Byte(0xF1,OLED_CMD);//

    OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
    OLED_WR_Byte(0x12,OLED_CMD);//

    OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
    OLED_WR_Byte(0x30,OLED_CMD);//

    OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
    OLED_WR_Byte(0x14,OLED_CMD);//

    OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}























