#include "led.h"

/******************************************
 �������ƣ�	����LED�ƹ��ܳ�ʼ��
 ������		void
 ����ֵ��	void
 ��ע��		1��LED3֧��pwm��ʹ��PB5(TIM3_CH2)
			   LED2��֧��pwm��ʹ��PE5
			2����ʼ��Ϊ�������
			3���ߵ�λ�صƣ��͵�λ����
*******************************************/
void ledInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIOB��GPIOE��AFIO���ù���ģ��ʱ��
	
	//��ʼ��PE5���������,��pwm
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_5);
	
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5    
 
   //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = 99; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =4; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
}



/******************************************
 �������ƣ�	LED3PWM����
 ������		u8��val������ǿ�������ڷ�Χ0-100
 ����ֵ��	void
 ��ע��
*******************************************/
void setPWMled(u8 val)
{
	TIM_SetCompare2(TIM3, val);
}



/******************************************
 �������ƣ�	LED2ѭ���򿪹ر�
 ������		void
 ����ֵ��	void
 ��ע��
*******************************************/
void LED2Flash(void)
{
	static u8 LED2State = 0;
	
	if(LED2State)
		GPIO_SetBits(GPIOE,GPIO_Pin_5);
	else
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
	
	LED2State = !LED2State;
}



/******************************************
 �������ƣ�	LED3ѭ���򿪹ر�
 ������		void
 ����ֵ��	void
 ��ע��ʹ������100������0��ʾ����
*******************************************/
void LED3Flash(void)
{
	static u8 LED3State = 0;
	
	if(LED3State)
		setPWMled(0);
	else
		setPWMled(100);
	
	LED3State = !LED3State;
}



/******************************************
 �������ƣ�	ִ��һ�κ�����
 ������		void
 ����ֵ��	void
 ��ע��
*******************************************/
void LED3OneBreath(void)
{
	u8 led0pwmval=0;
	u8 dir=1;	
	
	for(u8 i = 0; i < 200; i++)
	{
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
	}
		
}
