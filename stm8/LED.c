#include "iostm8s103.h"
#include "led.h"

void GPIOPB4_OUT(void)
{
    PB_DDR |= 0x10;    // PB4   输出
    PB_ODR |= 0x10;    // PB4   上拉
    PB_CR1 |= 0x10;    // PB4   推挽
    //PB_CR2 |= 0x10;  // 高速  10MHZ
    PB_CR2 |= 0x00;
}
void GPIOPB5_OUT(void)
{
    PB_DDR |= 0x20;    // PB5   输出
    PB_ODR |= 0x20;    // PB5   上拉
    PB_CR1 |= 0x20;    // PB5   推挽
    //PB_CR2 |= 0x20;  // 高速  10MHZ
    PB_CR2 |= 0x00;
}
void GPIOPC3_OUT(void)
{
    PC_DDR |= 0x08;    // PC3   输出
    PC_ODR |= 0x08;    // PC3   上拉
    PC_CR1 |= 0x08;    // PC3   推挽
    //PC_CR2 |= 0x08;  // 高速  10MHZ
    PC_CR2 |= 0x00;
}
void GPIOPC4_OUT(void)
{
    PC_DDR |= 0x10;    // PC4   输出
    PC_ODR |= 0x10;    // PC4   上拉
    PC_CR1 |= 0x10;    // PC4   推挽
    //PC_CR2 |= 0x10;  // 高速  10MHZ
    PC_CR2 |= 0x00;
}
/*************************************************************
   函数名称:
   函数功能:
   入口参数:
   入口参数的类型和含义:
   出口参数:
   备 注:
*************************************************************/
void LED_Init(char *buffer)
{
    GPIOPB4_OUT();
    GPIOPB5_OUT();
    GPIOPC3_OUT();
    GPIOPC4_OUT();
    if (buffer[0]=='0') 
    { 
        LED_PB4_OFF; 
    }
    else
    {
        LED_PB4_ON;
    }
    if (buffer[1]=='0') 
    { 
        LED_PB5_OFF; 
    }
    else
    {
        LED_PB5_ON;
    }
    if (buffer[2]=='0') 
    { 
        LED_PC3_OFF; 
    }
    else
    {
        LED_PC3_ON;
    }
    if (buffer[3]=='0') 
    { 
        LED_PC4_OFF; 
    }
    else
    {
        LED_PC4_ON;
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
void LED_Set(char *buffer)
{
    if ( buffer[0] != buffer[4] )
    {
        if (buffer[4]=='1') 
        {
            LED_PB4_ON;
        }
        else
        {
            LED_PB4_OFF;
        }
        buffer[0] = buffer[4];
    }
    if ( buffer[1] != buffer[5] )
    {
        if (buffer[5]=='1') 
        {
            LED_PB5_ON;
        }
        else
        {
            LED_PB5_OFF;
        }
        buffer[1] = buffer[5];
    }
    if ( buffer[2] != buffer[6] )
    {
        if (buffer[6]=='1') 
        {
            LED_PC3_ON;
        }
        else
        {
            LED_PC3_OFF;
        }
        buffer[2] = buffer[6];
    }
    if ( buffer[3] != buffer[7] )
    {
        if (buffer[7]=='1') 
        {
            LED_PC4_ON;
        }
        else
        {
            LED_PC4_OFF;
        }
        buffer[3] = buffer[7];
    }
}
/* EOF */