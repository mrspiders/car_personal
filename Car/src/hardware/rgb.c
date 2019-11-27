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
 参数：		void
 返回值：	void
 备注：		1、设置为PWM输出，满足RGB合成不同颜色灯光需求
			2、	公共端为+，3.3v
				R:PA1,TIM2_CH2
				G:PA6,TIM3_CH1
				B:PA8,TIM1_CH1
*******************************************/
void RGBInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 |RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	
	//配置PA1,PA6,PA8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//初始化GPIO
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_8);
	
	//配置时钟参数
	TIM_TimeBaseStructure.TIM_Period = 99;
	TIM_TimeBaseStructure.TIM_Prescaler = 4;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	//初始化时钟R:PA1,TIM2_CH2; G:PA6,TIM3_CH1; B:PA8,TIM1_CH1
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	
	//配置pwm模式参数
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	//初始化pwm模式R:PA1,TIM2_CH2; G:PA6,TIM3_CH1; B:PA8,TIM1_CH1
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	
	
	//使能TIM在CCR上的预装载寄存器
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	//时钟使能
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
}



/******************************************
 函数名称：	红色灯开关
 参数：		u8 val
 返回值：	void
 备注：		pwm调节亮度，val参数调节范围0-100
			
*******************************************/
void setRedLed(u8 val)
{
	TIM_SetCompare2(TIM2, val);
}


/******************************************
 函数名称：	绿色灯开关
 参数：		u8 val
 返回值：	void
 备注：		pwm调节亮度，val参数调节范围0-100
			
*******************************************/
void setGreenLed(u8 val)
{
	TIM_SetCompare1(TIM3, val);
}


/******************************************
 函数名称：	蓝色灯开关
 参数：		u8 val
 返回值：	void
 备注：		pwm调节亮度，val参数调节范围0-100
			
*******************************************/
void setBlueLed(u8 val)
{
	TIM_SetCompare1(TIM1, val);
}

