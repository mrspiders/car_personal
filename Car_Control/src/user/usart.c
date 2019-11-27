#include "usart.h"


////�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
//#if 1
//#pragma import(__use_no_semihosting)             
////��׼����Ҫ��֧�ֺ���                 
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////����_sys_exit()�Ա���ʹ�ð�����ģʽ    
//void _sys_exit(int x) 
//{ 
//	x = x; 
//} 
////�ض���fputc���� 
//int fputc(int ch, FILE *f)
//{      
//	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
//#endif 



/******************************************
 �������ƣ�	����1��ʼ��
 ������		u32��bound�����ڲ�����
 ����ֵ��	void
 ��ע��	1��PA9��TX��PA10��RX
		2����ʼ��Ϊ�������
		3���ߵ�λ�򿪷��������͵�λ�رշ�����
*******************************************/
void uart1Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
	USART_DeInit(USART1);	//USART1��λ
	
	//GPIO�˿�ģʽ����,PA9,PA10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//PA9��TX������Ϊ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//PA10��RX������Ϊ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//���ڲ�����ʼ��
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	//��ʹ�ܽ��գ���Ҫ�����ж�
	#if EN_USART1_RX
	
	//��ʼ��NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//�����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	#endif
	
	//ʹ�ܴ���
	USART_Cmd(USART1, ENABLE);
}



/******************************************
 �������ƣ�	�����ַ����ͺ���
 ������		1��USART_TypeDef,*USARTx,ѡ�񴮿�
			2��uint8_t,ch,Ҫ���͵��ַ�
 ����ֵ��	void
 ��ע��	ÿ�η���һ���ַ�
*******************************************/
void usart_send_char(USART_TypeDef *USARTx, uint8_t ch)
{
	USART_SendData(USARTx, ch);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
		;
}



/******************************************
 �������ƣ�	�����ַ������ͺ���
 ������		1��USART_TypeDef,*USARTx,ѡ�񴮿�
			2��uint8_t,ch,Ҫ���͵��ַ�
 ����ֵ��	void
 ��ע��	ÿ�η���һ���ַ�
*******************************************/
void usart_send_string(USART_TypeDef *USARTx, uint8_t *str)
{
	while(*str)
	{
		usart_send_char(USARTx, *str);
		str++;
	}
}



u16 USART_RX_STA=0;       //����״̬���	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.


/******************************************
 �������ƣ�	����1�жϷ�����
 ������		void
 ����ֵ��	void
 ��ע��	1��
*******************************************/
void USART1_IRQHandler(void)
{
	/*************************************************
	����ִ��ǰ��������
		1��ÿ���յ�һ���ַ��������жϴ�����
		2����ȷ���ַ�����ʽ����Ч����+0x0d+0x0a
		3��������ַ������ȣ�300
	����
		1���жϽ��յ����ַ���ʽ�Ƿ���ȷ����������������½��գ�ֻ������ʽ��ȷ���ַ���
		2�������ĩβ��Ϊ��ʽȷ�ϵ������ַ�����ַ����Ȳ��洢
		3���ַ������ȳ�������
	
	
	**************************************************/
	//256   0100 0001 0000 0000
	
	u8 res;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		res = USART_ReceiveData(USART1);
		
		if((USART_RX_STA & 0x8000) == 0)	//1000 0000 0000 000
		{//�жϽ��յ�����ַ�ǰ���λ�Ƿ��Ѿ���0x0a,��������Խ��ո��ַ�
			if(USART_RX_STA & 0x4000)	//0100 0000 0000 0000
			{//�θ�λΪ0x0d����Ҫ�жϴ˴ν��յ��Ƿ�Ϊ0x0a
				if(res == 0x0a)	
				{//�������
					USART_RX_STA |= 0x8000;	//1000 0000 0000 0000 �� 1100 0001 0000 0000
				}else{//�θ�λΪ0x0d�����Ǵ˴ν��յ��Ĳ���0x0a
					USART_RX_STA = 0;
				}
			}else{//�θ�λ����0x0d,�ж��Ƿ�Ϊ�θ�λ��0x0d
				if(res == 0x0d)
				{//�θ�λ��Ϊ1
					USART_RX_STA |= 0x4000;	//0100 0000 0000 0000
				}else{//�����λ���Ǵθ�λ���������մ���buf
					USART_RX_BUF[USART_RX_STA & 0x3fff] = res;	//0011 1111 1111 1111
					USART_RX_STA++;
					
					if(USART_RX_STA > USART_REC_LEN)
					{
						//printf("\r\n\r\n�����ַ��������ޣ������������ʷ�����������룡\r\n\r\n");
						USART_RX_STA |= 0x2000;		//0010 0000 0000 0000
						//memset(USART_RX_BUF, 0, USART_REC_LEN);
					}
				}
			}
		}
	}
}
