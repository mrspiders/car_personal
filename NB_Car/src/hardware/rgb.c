#include "rgb.h"

/******************************
 板载LED灯初始化函数
 PC13引脚
 初始化为推挽输出
 高电位关灯，低电位开灯
*/
void LEDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}


/********************************
 RGB初始化函数
			1、设置为PWM输出，满足RGB合成不同颜色灯光需求
			2、

 公共端为+，3.3v
 R:PA1,TIM2_CH2
 G:PA6,TIM3_CH1
 B:PA8,TIM1_CH1
 

 ********************************/
void RGBInit(u16 prescaler, u16 period)
{
	
}


/*红色灯开关*/
void setRedLed(u8 val)
{
	
}


/*绿色灯开关*/
void setGreenLed(u8 val)
{
	
}


/*蓝色灯开关*/
void setBlueLed(u8 val)
{
	
}

