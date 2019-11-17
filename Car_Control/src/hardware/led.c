#include "led.h"
#include "stm32f10x_gpio.h"


/******************************************
 函数名称：	板载LED灯功能初始化
 参数：		void
 返回值：	void
 备注：		1、使用PB5、PE5引脚
					2、初始化为推挽输出
					3、高电位关灯，低电位开灯
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

