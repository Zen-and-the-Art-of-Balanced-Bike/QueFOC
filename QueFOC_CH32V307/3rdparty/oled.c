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
 * IIC Start  I2C协议规定，SCL处于高电平时，SDA由高到低变化，这种信号是起始信号。
 * 主设备开始数据通讯通过开始条件.开始条件发生在SCL高电平期间，SDA产生一个下降沿的跳变。
**********************************************/
void IIC_Start()//I2C启动信号，开始SCL与SDA都置1，之后SDA置0，SCL再置0
{

    OLED_SCLK_Set();
    OLED_SDIN_Set();
    OLED_SDIN_Clr();
    OLED_SCLK_Clr();
}

/**********************************************
 * IIC Stop  I2C协议规定，SCL处于高电平，SDA由低到高变化，这种信号是停止信号。
 * 写模式在接受到停止信号之后结束。停止信号发生在SCL高点平期间SDA的上升沿，作为停止信号。
**********************************************/
void IIC_Stop()//I2C停止信号，开始SCL置1，SDA置0，之后SDA置1
{
    OLED_SCLK_Set() ;
//  OLED_SCLK_Clr();
    OLED_SDIN_Clr();
    OLED_SDIN_Set();

}

/**********************************************
 * IIC Wait Ack  应答信号出现在1个字节传输完成之后，即第9个SCL时钟周期内，
 * 此时主机需要释放SDA总线，把总线控制权交给从机，
 * 由于上拉电阻的作用，此时总线为高电平，
 * 如果从机正确的收到了主机发来的数据，会把SDA拉低，表示应答响应。
**********************************************/
void IIC_Wait_Ack()//I2C应答信号，SCL置1后置0，此处只负责第9个SCL时钟周期内生成一个应答周期，不负责处理应答信号
{
    OLED_SCLK_Set() ;
    OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
 * 一次写入一位字节的一个数据，顺序是从高到低
 * 写完一个数据后产生一个SCL从低到高再从高到低的变化，表明已经发完了
 *
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
    unsigned char i;
    unsigned char m,da;
    da=IIC_Byte;
    OLED_SCLK_Clr();//SCLK设置为低电平
    for(i=0;i<8;i++)//从高到低依次发送数据
    {
        m=da;
        //  OLED_SCLK_Clr();
        m=m&0x80;
        if(m==0x80) //取最高位发送(0-低,1-高)
        {
            OLED_SDIN_Set();
        }
        else OLED_SDIN_Clr();
        da=da<<1;
        OLED_SCLK_Set();//SCLK设置为高电平
        OLED_SCLK_Clr();//SCLK设置为低电平
        }
}
/**********************************************
// IIC Write Command
 * OLED的IIC写入Command命令，详见数据手册
 * 地址：
 * b7 |  b6 |  b5 | b4 | b3 |  b2  | b1  | b0
 * 0  |  1  |  1  | 1  |  0 |  SA0 | SA0 | R/W#
 * “SA0”位提供一个额外的从地址位。不管是“0111_100”还是“0111_101”，
 * 都可以被选择为SSD1306的从地址。D/C#引脚作为SA0为从地址选择。(器材上标的是0x78，代表SA0都是0)
 * “R/W#”位是被用来决定IIC协议的工作模式，R/W#=1时，为读模式，R/W#=0时，为写模式。
 * 写入0x78意思是要向从地址为0x78(7位地址,0111_100)的设备进行写入操作(R/W#=0)
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
 * IIC写入显示数据
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
 * OLED写入指令，有cmd决定写入什么东西
 * 宏定义已经定义好了：OLED_CMD  0   OLED_DATA  1
 * 即决定向Command还是写入显示数据
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
// fill_Picture ？
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
 * 设定OLED显示位置
********************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f),OLED_CMD);
}

/********************************************
// OLED_Display_On
 * 打开OLED显示
********************************************/
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

/********************************************
// OLED_Display_Off
 * 关闭OLED显示
********************************************/
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

/********************************************
// OLED_Clear
 * OLED清屏操作，都写入0
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
 * OLED填屏操作，都写入1
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

//坐标显示位置选择及字体大小：
//x:0~127
//y:0~63
//size:16/12
/********************************************
// OLED_ShowChar
 * OLED显示字符，输入参数详见上方显示坐标选择及字体大小
 * OLED从上到下分成八个区域，对每个区域单独写入
 * 每个区域从左到右分成0~127共128个小区域，编号依次增大
 * 每个小区域的数据是上边为低位(LSB D0)，下边为高位(MSB D7)
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
 * OLED输入数据定位函数
********************************************/
u32 oled_pow(u8 m,u8 n)
{
    u32 result=1;
    while(n--)result*=m;
    return result;
}

/********************************************
// OLED_ShowNum
 * OLED显示数字，输入参数详见上方显示坐标选择及字体大小
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
 * OLED显示（？）未见使用
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
 * OLED显示字符串，输入参数详见上方显示坐标选择及字体大小
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
 * OLED显示图片，输入参数详见上方显示坐标选择及字体大小
 * 但是这部分调用的BMP数组，要显示的图像需要单独加上
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
 * OLED定义函数，详见数据手册                                    (没找到对应位置)
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























