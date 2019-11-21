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
		//��������
		key=KEY_Scan(0);	//�õ���ֵ
	   	if(key)
		{						   
			switch(key)
			{				 
				case KEY_S4_PRES:	//S4���Ʒ�����
					beepFlash();
					break;
				case KEY_S3_PRES:	//S3����LED3��ת
					LED3Flash();
					break;
				case KEY_S2_PRES:	//S2����LED2��ת	 
					LED2Flash();
					break;
				case KEY_S1_PRES:	//S1ִ��һ�κ����� 
					LED3OneBreath();
					break;
			}
		}
		
		delay_ms(10); 
	}	 
}
