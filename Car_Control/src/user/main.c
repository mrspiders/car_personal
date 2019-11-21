#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "key.h"

int main(void)
{	
	//vu8 key=0;	
	u16 led0pwmval=0;
	u8 dir=1;	
	
	delay_init();
	ledInit();
	//beepInit();
	//keyInit();
	
	
	while(1)
	{
//		//LED灯测试
//		GPIO_SetBits(GPIOE, GPIO_Pin_5);
//		delay_ms(500);
//		GPIO_ResetBits(GPIOE, GPIO_Pin_5);
//		delay_ms(500);
		
		//LEDpwm检测
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
		
		
		
		
		
//		//按键测试
//		key=KEY_Scan(0);	//得到键值
//	   	if(key)
//		{						   
//			switch(key)
//			{				 
//				case WKUP_PRES:	//控制蜂鸣器
//					BEEP=!BEEP;
//					break;
//				case KEY2_PRES:	//控制LED0翻转
//					LED0=!LED0;
//					break;
//				case KEY1_PRES:	//控制LED1翻转	 
//					LED1=!LED1;
//					break;
//				case KEY0_PRES:	//同时控制LED0,LED1翻转 
//					LED0=!LED0;
//					LED1=!LED1;
//					break;
//			}
//		}else delay_ms(10); 
		
		
//		//蜂鸣器测试		
//		GPIO_SetBits(GPIOB, GPIO_Pin_8);
//		delay_ms(50);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
//		delay_ms(50);
	}	 
}
