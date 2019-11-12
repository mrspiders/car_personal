#include "rgb.h"

/******************************************
 函数名称：	板载LED灯功能初始化
 参数：		void
 返回值：	void
 备注：		1、使用PC13引脚
			2、初始化为推挽输出
			3、高电位关灯，低电位开灯
*******************************************/
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



/******************************************
 函数名称：	RGB功能初始化
 参数：		u16 prescaler, u16 period
 返回值：	void
 备注：		1、设置为PWM输出，满足RGB合成不同颜色灯光需求
			2、	公共端为+，3.3v
				R:PA1,TIM2_CH2
				G:PA6,TIM3_CH1
				B:PA8,TIM1_CH1
*******************************************/
void RGBInit(u16 prescaler, u16 period)
{
	
}




/******************************************
 函数名称：	红色灯开关
 参数：		u8 val
 返回值：	void
 备注：		pwm调节亮度，val参数调节范围0-100
			
*******************************************/
void setRedLed(u8 val)
{
	
}


/******************************************
 函数名称：	绿色灯开关
 参数：		u8 val
 返回值：	void
 备注：		pwm调节亮度，val参数调节范围0-100
			
*******************************************/
void setGreenLed(u8 val)
{
	
}


/******************************************
 函数名称：	蓝色灯开关
 参数：		u8 val
 返回值：	void
 备注：		pwm调节亮度，val参数调节范围0-100
			
*******************************************/
void setBlueLed(u8 val)
{
	
}

