#include "led.h"

/******************************************
 函数名称：	板载LED灯功能初始化
 参数：		void
 返回值：	void
 备注：		1、LED3支持pwm，使用PB5(TIM3_CH2)
			   LED2不支持pwm，使用PE5
			2、初始化为推挽输出
			3、高电位关灯，低电位开灯
*******************************************/
void ledInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIOB、GPIOE和AFIO复用功能模块时钟
	
	//初始化PE5，推挽输出,无pwm
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_5);
	
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = 99; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =4; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}



/******************************************
 函数名称：	LED3PWM控制
 参数：		u8，val，亮度强弱，调节范围0-100
 返回值：	void
 备注：
*******************************************/
void setPWMled(u8 val)
{
	TIM_SetCompare2(TIM3, val);
}



/******************************************
 函数名称：	LED2循环打开关闭
 参数：		void
 返回值：	void
 备注：
*******************************************/
void LED2Flash(void)
{
	static u8 LED2State = 0;
	
	if(LED2State)
		GPIO_SetBits(GPIOE,GPIO_Pin_5);
	else
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
	
	LED2State = !LED2State;
}



/******************************************
 函数名称：	LED3循环打开关闭
 参数：		void
 返回值：	void
 备注：使用亮度100和亮度0表示亮灭
*******************************************/
void LED3Flash(void)
{
	static u8 LED3State = 0;
	
	if(LED3State)
		setPWMled(0);
	else
		setPWMled(100);
	
	LED3State = !LED3State;
}



/******************************************
 函数名称：	执行一次呼吸灯
 参数：		void
 返回值：	void
 备注：
*******************************************/
void LED3OneBreath(void)
{
	u8 led0pwmval=0;
	u8 dir=1;	
	
	for(u8 i = 0; i < 200; i++)
	{
		delay_ms(10);	 
		if(dir)
			led0pwmval++;
		else 
			led0pwmval--;

		if(led0pwmval>99)
			dir=0;
		if(led0pwmval==0)
			dir=1;										 
		setPWMled(led0pwmval);
	}
		
}
