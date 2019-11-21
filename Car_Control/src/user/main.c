#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "key.h"

int main(void)
{	
	vu8 key=0;	
	
	delay_init();
	ledInit();
	keyInit();
	beepInit();
	
	
	while(1)
	{
		delay_ms(200);
		//按键测试
		key=KEY_Scan(0);	//得到键值
	   	if(key)
		{						   
			switch(key)
			{				 
				case KEY_S4_PRES:	//S4控制蜂鸣器
					beepFlash();
					break;
				case KEY_S3_PRES:	//S3控制LED3翻转
					LED3Flash();
					break;
				case KEY_S2_PRES:	//S2控制LED2翻转	 
					LED2Flash();
					break;
				case KEY_S1_PRES:	//S1执行一次呼吸灯 
					LED3OneBreath();
					break;
			}
		}
		
		delay_ms(10); 
	}	 
}
