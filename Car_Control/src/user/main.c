#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "usart.h"

int main(void)
{
	u8 t;
	u8 len;
	u16 times;
	
	delay_init();
	ledInit();
	keyInit();
	beepInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart1Init(115200);
	
	while(1)
	{
		if(USART_RX_STA & 0x8000)
		{
			len = USART_RX_STA & 0x3f;	//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ��\r\n\r\n");
			
			for(t = 0; t < len; t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);	//�򴮿�1�������ݣ�����һ���ֽ�
				while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)	//��ȡ״̬��־λ����ⷢ�͵�һ���ֽ��Ƿ���ɷ���
					;//�ȴ����ͽ���
			}
			
			printf("\r\n\r\n");	//��������
			
			USART_RX_STA = 0;
		}else{
			times++;
			
			if(times % 5000 == 0)
			{
				printf("\r\n��־1\r\n");
				printf("��־2\r\n");
			}
			
			if(times % 200 == 0)
				printf("���������ݣ��Իس�������\n");
			
			if(times % 30 == 0)
				LED2Flash();
			
			delay_ms(10);
		}
	}	 
}
