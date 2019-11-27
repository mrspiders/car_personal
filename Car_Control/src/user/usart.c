#include "usart.h"


////加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
//#if 1
//#pragma import(__use_no_semihosting)             
////标准库需要的支持函数                 
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////定义_sys_exit()以避免使用半主机模式    
//void _sys_exit(int x) 
//{ 
//	x = x; 
//} 
////重定义fputc函数 
//int fputc(int ch, FILE *f)
//{      
//	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
//#endif 



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



/******************************************
 函数名称：	串口字符发送函数
 参数：		1、USART_TypeDef,*USARTx,选择串口
			2、uint8_t,ch,要发送的字符
 返回值：	void
 备注：	每次发送一个字符
*******************************************/
void usart_send_char(USART_TypeDef *USARTx, uint8_t ch)
{
	USART_SendData(USARTx, ch);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
		;
}



/******************************************
 函数名称：	串口字符串发送函数
 参数：		1、USART_TypeDef,*USARTx,选择串口
			2、uint8_t,ch,要发送的字符
 返回值：	void
 备注：	每次发送一个字符
*******************************************/
void usart_send_string(USART_TypeDef *USARTx, uint8_t *str)
{
	while(*str)
	{
		usart_send_char(USARTx, *str);
		str++;
	}
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
		2、正确的字符串格式：有效内容+0x0d+0x0a
		3、最大处理字符串长度：300
	需求：
		1、判断接收到的字符格式是否正确，错误的舍弃，重新接收，只保留格式正确的字符串
		2、计算除末尾作为格式确认的两个字符外的字符长度并存储
		3、字符串长度超限提醒
	
	
	**************************************************/
	//256   0100 0001 0000 0000
	
	u8 res;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		res = USART_ReceiveData(USART1);
		
		if((USART_RX_STA & 0x8000) == 0)	//1000 0000 0000 000
		{//判断接收到这个字符前最高位是否已经是0x0a,若否，则可以接收该字符
			if(USART_RX_STA & 0x4000)	//0100 0000 0000 0000
			{//次高位为0x0d，需要判断此次接收的是否为0x0a
				if(res == 0x0a)	
				{//接收完成
					USART_RX_STA |= 0x8000;	//1000 0000 0000 0000 → 1100 0001 0000 0000
				}else{//次高位为0x0d，但是此次接收到的不是0x0a
					USART_RX_STA = 0;
				}
			}else{//次高位不是0x0d,判断是否为次高位的0x0d
				if(res == 0x0d)
				{//次高位置为1
					USART_RX_STA |= 0x4000;	//0100 0000 0000 0000
				}else{//非最高位，非次高位，正常接收存入buf
					USART_RX_BUF[USART_RX_STA & 0x3fff] = res;	//0011 1111 1111 1111
					USART_RX_STA++;
					
					if(USART_RX_STA > USART_REC_LEN)
					{
						//printf("\r\n\r\n输入字符个数超限，已清除输入历史，请重新输入！\r\n\r\n");
						USART_RX_STA |= 0x2000;		//0010 0000 0000 0000
						//memset(USART_RX_BUF, 0, USART_REC_LEN);
					}
				}
			}
		}
	}
}
