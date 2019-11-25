#include "usart.h"


//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 



/******************************************
 函数名称：	串口1初始化
 参数：		u32，bound，串口波特率
 返回值：	void
 备注：	1、PA9→TX、PA10→RX
		2、初始化为推挽输出
		3、高电位打开蜂鸣器，低电位关闭蜂鸣器
*******************************************/
void uart1Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
	USART_DeInit(USART1);	//USART1复位
	
	//GPIO端口模式配置,PA9,PA10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//PA9→TX，配置为复用推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//PA10→RX，配置为浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//串口参数初始化
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	//若使能接收，需要开启中断
	#if EN_USART1_RX
	
	//初始化NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//开启中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	#endif
	
	//使能串口
	USART_Cmd(USART1, ENABLE);
}



u16 USART_RX_STA=0;       //接收状态标记	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.


/******************************************
 函数名称：	串口1中断服务函数
 参数：		void
 返回值：	void
 备注：	1、
*******************************************/
void USART1_IRQHandler(void)
{
	/*************************************************
	函数执行前提条件：
		1、每接收到一个字符，进入中断处理函数
		2、正确的字符串格式：内容+0x0d+0x0a
		3、最大处理字符串长度：200
	需求：
		1、判断接收到的字符格式是否正确，错误的舍弃，重新接收，只保留格式正确的字符串
		2、计算除末尾作为格式确认的两个字符外的字符长度并存储
		3、字符串长度超限提醒
	
	
	**************************************************/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//	u8 Res;
//	
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	
//	//获取中断状态标志位函数
//	//判断是否接收中断，若串口接收中断，则读取串口接收到的数据，接收到的数据必须以0x0d,0x0a结尾
//	{
//		Res = USART_ReceiveData(USART1);	//读取接收到的数据
//		
//		if((USART_RX_STA & 0x8000) == 0)	//USART_RX_STA最高位第15位（0x8000=1000 0000 0000 0000）为0，表示未接收到结束标志字符0x0a（换行），所以接收未完成
//		{
//			if((USART_RX_STA & 0x4000))	//USART_RX_STA次高位第14位（0x4000=0100 0000 0000 0000）为1，表示已接收到倒数第二位0x0d（回车）
//			{
//				if(Res != 0x0a)	//接收错误，重新开始
//					USART_RX_STA = 0;
//				else	//接收完成
//					USART_RX_STA |= 0x8000;
//			}else{	//还没有收到0x0d，以下为未接收到回车换行前的正常接收步骤
//				if(Res == 0x0d)
//					USART_RX_STA |= 0x4000;
//				else
//				{
//					USART_RX_BUF[USART_RX_STA & 0x3FFF] = Res;
//					USART_RX_STA++;
//					if(USART_RX_STA > (USART_REC_LEN - 1))
//						USART_RX_STA = 0;	//接收数据错误，重新开始接收
//				}
//			}
//		}
//	}
}
