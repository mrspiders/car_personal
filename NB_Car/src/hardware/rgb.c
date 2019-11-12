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
 ������		u16 prescaler, u16 period
 ����ֵ��	void
 ��ע��		1������ΪPWM���������RGB�ϳɲ�ͬ��ɫ�ƹ�����
			2��	������Ϊ+��3.3v
				R:PA1,TIM2_CH2
				G:PA6,TIM3_CH1
				B:PA8,TIM1_CH1
*******************************************/
void RGBInit(u16 prescaler, u16 period)
{
	
}




/******************************************
 �������ƣ�	��ɫ�ƿ���
 ������		u8 val
 ����ֵ��	void
 ��ע��		pwm�������ȣ�val�������ڷ�Χ0-100
			
*******************************************/
void setRedLed(u8 val)
{
	
}


/******************************************
 �������ƣ�	��ɫ�ƿ���
 ������		u8 val
 ����ֵ��	void
 ��ע��		pwm�������ȣ�val�������ڷ�Χ0-100
			
*******************************************/
void setGreenLed(u8 val)
{
	
}


/******************************************
 �������ƣ�	��ɫ�ƿ���
 ������		u8 val
 ����ֵ��	void
 ��ע��		pwm�������ȣ�val�������ڷ�Χ0-100
			
*******************************************/
void setBlueLed(u8 val)
{
	
}

