#include "beep.h"

/******************************************
 函数名称：	板载蜂鸣器功能初始化
 参数：		void
 返回值：	void
 备注：	1、使用PB8引脚
		2、初始化为推挽输出
		3、高电位打开蜂鸣器，低电位关闭蜂鸣器
*******************************************/
void beepInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
}
