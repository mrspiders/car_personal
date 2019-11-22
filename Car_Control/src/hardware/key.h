#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"
#include "delay.h"

#define KEY_S1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����S1
#define KEY_S2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����S2
#define KEY_S3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//��ȡ����S3
#define KEY_S4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����S4

#define NO_KEY_PRES 0	//�ް�������
#define KEY_S4_PRES 1	//KEY_S4����
#define KEY_S3_PRES	2	//KEY_S3����
#define KEY_S2_PRES	3	//KEY_S2����
#define KEY_S1_PRES 4	//KEY_S1����

void keyInit(void);
u8 KEY_Scan(u8 mode);

#endif
