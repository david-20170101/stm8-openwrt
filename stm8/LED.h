#ifndef __LED_H__
#define __LED_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*************************宏定义******************************/
#define LED_PB4_OFF    PB_ODR|=0x10   //小灯熄灭
#define LED_PB4_ON     PB_ODR&=0xEF   //小灯点亮
#define LED_PB5_OFF    PB_ODR|=0x20   //小灯熄灭
#define LED_PB5_ON     PB_ODR&=0xDF   //小灯点亮
#define LED_PC3_OFF    PC_ODR|=0x08   //小灯熄灭
#define LED_PC3_ON     PC_ODR&=0xF7   //小灯点亮
#define LED_PC4_OFF    PC_ODR|=0x10   //小灯熄灭
#define LED_PC4_ON     PC_ODR&=0xEF   //小灯点亮

void LED_Init(char *buffer);
void LED_Set(char *buffer);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */