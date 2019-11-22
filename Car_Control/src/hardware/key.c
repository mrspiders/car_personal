#include "key.h"

/******************************************
 函数名称：	板载按键功能初始化
 参数：		void
 返回值：	void
 备注：		1、
				S4→PA0，初始化为低电位
				S3→PE2，初始化为高电位
				S2→PE3，初始化为高电位
				S1→PE4，初始化为高电位
			2、
*******************************************/
void keyInit(void)
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}



/*****************************************************
 函数名称：	按键处理函数
 参数：		u8，mode，是否支持连按模式
			0：支持连按
			1：不支持连按
 返回值：	u8类型按键值
			0：没有按键按下
			1：S4按下
			2：S3按下
			3：S2按下
			4：S1按下
 备注：		1、按键响应有优先级：S4 > S3 > S2 > S1
			2、支持按键防抖动
			3、可选择是否支持连按
*****************************************************/
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键松开标志
	
	if(mode)
		key_up=1;//支持连按
	
	if(key_up&&(KEY_S1==0||KEY_S2==0||KEY_S3==0||KEY_S4==1))
	{
		delay_ms(10);//去抖动
		key_up=0;
		
		if(KEY_S4==1)
			return KEY_S4_PRES;
		else if(KEY_S3==0)
			return KEY_S3_PRES;
		else if(KEY_S2==0)
			return KEY_S2_PRES;
		else if(KEY_S1==0)
			return KEY_S1_PRES;
		
	}else if(KEY_S1==1&&KEY_S2==1&&KEY_S3==1&&KEY_S4==0)
		key_up=1;
	
		return NO_KEY_PRES;//无按键按下
}


//		//按键测试
//		key=KEY_Scan(0);	//得到键值
//	   	if(key)
//		{						   
//			switch(key)
//			{				 
//				case KEY_S4_PRES:	//S4控制蜂鸣器
//					beepFlash();
//					break;
//				case KEY_S3_PRES:	//S3控制LED3翻转
//					LED3Flash();
//					break;
//				case KEY_S2_PRES:	//S2控制LED2翻转	 
//					LED2Flash();
//					break;
//				case KEY_S1_PRES:	//S1执行一次呼吸灯 
//					LED3OneBreath();
//					break;
//			}
//		}
//		
//		delay_ms(10); 
