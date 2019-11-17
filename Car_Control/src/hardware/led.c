#include "led.h"
#include "stm32f10x_gpio.h"


/******************************************
 �������ƣ�	����LED�ƹ��ܳ�ʼ��
 ������		void
 ����ֵ��	void
 ��ע��		1��ʹ��PB5��PE5����
					2����ʼ��Ϊ�������
					3���ߵ�λ�صƣ��͵�λ����
*******************************************/
void ledInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

