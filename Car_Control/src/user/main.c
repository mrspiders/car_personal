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
			len = USART_RX_STA & 0x3f;	//得到此次接收到的数据长度
			printf("\r\n您发送的信息为：\r\n\r\n");
			
			for(t = 0; t < len; t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);	//向串口1发送数据，发送一个字节
				while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)	//获取状态标志位，检测发送的一个字节是否完成发送
					;//等待发送结束
			}
			
			printf("\r\n\r\n");	//插入新行
			
			USART_RX_STA = 0;
		}else{
			times++;
			
			if(times % 5000 == 0)
			{
				printf("\r\n标志1\r\n");
				printf("标志2\r\n");
			}
			
			if(times % 200 == 0)
				printf("请输入数据，以回车键结束\n");
			
			if(times % 30 == 0)
				LED2Flash();
			
			delay_ms(10);
		}
	}	 
}
