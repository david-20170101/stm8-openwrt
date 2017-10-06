#include "iostm8s103.h"
#include "dht11.h"

void GPIOPD3_OUT(void)
{
    PD_DDR |= 0x08;    // PD3   输出
    PD_ODR |= 0x08;    // PD3   上拉
    PD_CR1 |= 0x08;    // PD3   推挽
    //PD_CR2 |= 0x08;  // 高速  10MHZ
    PD_CR2 |= 0x00;
}
void GPIOPD3_IN(void)
{
    PD_DDR |= 0x00;  // PD3   输入
    PD_CR1 |= 0x00;  // PD3   
    PD_CR2 |= 0x08;  // 上拉输入 
}
void Delayms( unsigned int time )
{
    unsigned int i;
    while( time-- )
    {
        for( i = 900; i > 0; i-- )
        {
            _asm("nop");
            _asm("nop");
            _asm("nop");
            _asm("nop");
        }
    }
}
void Delayus( unsigned int time )
{
    unsigned int temp = time;
    if( time == 10 )
    {
        temp = 8;
    }
    if( time == 20 )
    {
        temp = 20;
    }
    if( time == 30 )
    {
        temp = 32;
    }
    if( time == 40 )
    {
        temp = 42;
    }
    if( time == 50 )
    {
        temp = 54;
    }
    while( temp-- )
    {
        _asm("nop");
        _asm("nop");
        _asm("nop");
        _asm("nop");
    }
}
/*************************************************************
   函数名称:
   函数功能:
   入口参数:
   入口参数的类型和含义:
   出口参数:
   备 注:
*************************************************************/
unsigned char uc_ComDHT11(void)
{
    unsigned char i, ucComData = 0;
    for( i = 0; i < 8; i++ )
    {
        //接收到响应后会出现50us的低电平表示发送数据的开始，
        //所以这里只要延时不超过50us即可
        while(!((PD_IDR & 0x08) == 0x08));
        //位数据“0”的格式为：50微秒的低电平和26--28微秒的高电平，
        //位数据“1”的格式为：50微秒的低电平加70微秒的高电平。
        Delayus( 30 );
        if((PD_IDR & 0x08) == 0x08) // 高电平为1，低电平为0
        {
            ucComData |= ( 1 << ( 7 - i ) );
            while((PD_IDR & 0x08) == 0x08);
        }
        else
        {
            ucComData |= ( 0 << ( 7 - i ) );
            while(!((PD_IDR & 0x08) == 0x08));
        }
    }
    return ucComData;
}
/*************************************************************
   函数名称:
   函数功能:
   入口参数:
   入口参数的类型和含义:
   出口参数:
   备 注:
*************************************************************/
void ReadTempAndHumi( float *pTempValue, float *pHumiValue )
{
    unsigned char ucDHT11Value[5] = { 0x00 };

    GPIOPD3_OUT();       //推挽输出高速模式，此时输出高电平
    DATA_DQ_LOW;         //此时处于主机输出模式，总线拉低，ODR设置为0
    Delayms(180);        //拉低18毫秒
    DATA_DQ_HIGH;        //释放总线、ODR设置为1
    GPIOPD3_IN();        //上拉输入
    Delayus(35);         //释放总线以后等待35微秒DHT会发出响应信号
    if(!((PD_IDR & 0x08) == 0x08))
    {
        while(!((PD_IDR & 0x08) == 0x08));   //80us的应答信号 DHT11 TO MCU
        while((PD_IDR & 0x08) == 0x08);      //80us的通知信号 DHT11 TO MCU
        ucDHT11Value[0]	= uc_ComDHT11( ); // 湿度H
        ucDHT11Value[1]	= uc_ComDHT11( ); // 湿度L
        ucDHT11Value[2]	= uc_ComDHT11( ); // 温度H
        ucDHT11Value[3]	= uc_ComDHT11( ); // 温度L
        ucDHT11Value[4]	= uc_ComDHT11( ); // Check sum
        GPIOPD3_OUT();
        if( ( ucDHT11Value[0] + ucDHT11Value[1] + ucDHT11Value[2] +
              ucDHT11Value[3] ) == ucDHT11Value[4] )
        {
            *pHumiValue	= ucDHT11Value[0] + ucDHT11Value[1] / 10;
            *pTempValue	= ucDHT11Value[2] + ucDHT11Value[4] / 10;
            TempData = ucDHT11Value[2];
            HumiData = ucDHT11Value[0];
        }
    }
}
/* EOF */
