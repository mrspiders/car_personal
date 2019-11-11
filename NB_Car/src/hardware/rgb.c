#include "rgb.h"

/******************************
 ����LED�Ƴ�ʼ������
 PC13����
 ��ʼ��Ϊ�������
 �ߵ�λ�صƣ��͵�λ����
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
 RGB��ʼ������
			1������ΪPWM���������RGB�ϳɲ�ͬ��ɫ�ƹ�����
			2��

 ������Ϊ+��3.3v
 R:PA1,TIM2_CH2
 G:PA6,TIM3_CH1
 B:PA8,TIM1_CH1
 

 ********************************/
void RGBInit(u16 prescaler, u16 period)
{
	
}


/*��ɫ�ƿ���*/
void setRedLed(u8 val)
{
	
}


/*��ɫ�ƿ���*/
void setGreenLed(u8 val)
{
	
}


/*��ɫ�ƿ���*/
void setBlueLed(u8 val)
{
	
}

