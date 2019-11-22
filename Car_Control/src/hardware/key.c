#include "key.h"

/******************************************
 �������ƣ�	���ذ������ܳ�ʼ��
 ������		void
 ����ֵ��	void
 ��ע��		1��
				S4��PA0����ʼ��Ϊ�͵�λ
				S3��PE2����ʼ��Ϊ�ߵ�λ
				S2��PE3����ʼ��Ϊ�ߵ�λ
				S1��PE4����ʼ��Ϊ�ߵ�λ
			2��
*******************************************/
void keyInit(void)
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}



/*****************************************************
 �������ƣ�	����������
 ������		u8��mode���Ƿ�֧������ģʽ
			0��֧������
			1����֧������
 ����ֵ��	u8���Ͱ���ֵ
			0��û�а�������
			1��S4����
			2��S3����
			3��S2����
			4��S1����
 ��ע��		1��������Ӧ�����ȼ���S4 > S3 > S2 > S1
			2��֧�ְ���������
			3����ѡ���Ƿ�֧������
*****************************************************/
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�����ɿ���־
	
	if(mode)
		key_up=1;//֧������
	
	if(key_up&&(KEY_S1==0||KEY_S2==0||KEY_S3==0||KEY_S4==1))
	{
		delay_ms(10);//ȥ����
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
	
		return NO_KEY_PRES;//�ް�������
}


//		//��������
//		key=KEY_Scan(0);	//�õ���ֵ
//	   	if(key)
//		{						   
//			switch(key)
//			{				 
//				case KEY_S4_PRES:	//S4���Ʒ�����
//					beepFlash();
//					break;
//				case KEY_S3_PRES:	//S3����LED3��ת
//					LED3Flash();
//					break;
//				case KEY_S2_PRES:	//S2����LED2��ת	 
//					LED2Flash();
//					break;
//				case KEY_S1_PRES:	//S1ִ��һ�κ����� 
//					LED3OneBreath();
//					break;
//			}
//		}
//		
//		delay_ms(10); 
