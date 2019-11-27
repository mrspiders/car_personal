#include "rgb.h"

/******************************************
 �������ƣ�	����LED�ƹ��ܳ�ʼ��
 ������		void
 ����ֵ��	void
 ��ע��		1��ʹ��PC13����
			2����ʼ��Ϊ�������
			3���ߵ�λ�صƣ��͵�λ����
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
 �������ƣ�	RGB���ܳ�ʼ��
 ������		void
 ����ֵ��	void
 ��ע��		1������ΪPWM���������RGB�ϳɲ�ͬ��ɫ�ƹ�����
			2��	������Ϊ+��3.3v
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
	
	
	//����PA1,PA6,PA8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//��ʼ��GPIO
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_8);
	
	//����ʱ�Ӳ���
	TIM_TimeBaseStructure.TIM_Period = 99;
	TIM_TimeBaseStructure.TIM_Prescaler = 4;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	//��ʼ��ʱ��R:PA1,TIM2_CH2; G:PA6,TIM3_CH1; B:PA8,TIM1_CH1
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	
	//����pwmģʽ����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	//��ʼ��pwmģʽR:PA1,TIM2_CH2; G:PA6,TIM3_CH1; B:PA8,TIM1_CH1
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	
	
	//ʹ��TIM��CCR�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	//ʱ��ʹ��
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
}



/******************************************
 �������ƣ�	��ɫ�ƿ���
 ������		u8 val
 ����ֵ��	void
 ��ע��		pwm�������ȣ�val�������ڷ�Χ0-100
			
*******************************************/
void setRedLed(u8 val)
{
	TIM_SetCompare2(TIM2, val);
}


/******************************************
 �������ƣ�	��ɫ�ƿ���
 ������		u8 val
 ����ֵ��	void
 ��ע��		pwm�������ȣ�val�������ڷ�Χ0-100
			
*******************************************/
void setGreenLed(u8 val)
{
	TIM_SetCompare1(TIM3, val);
}


/******************************************
 �������ƣ�	��ɫ�ƿ���
 ������		u8 val
 ����ֵ��	void
 ��ע��		pwm�������ȣ�val�������ڷ�Χ0-100
			
*******************************************/
void setBlueLed(u8 val)
{
	TIM_SetCompare1(TIM1, val);
}

