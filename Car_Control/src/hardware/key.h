#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"
#include "delay.h"

#define KEY_S1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
#define KEY_S2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1
#define KEY_S3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键2 
#define KEY_S4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP) 

 

#define KEY_S4_PRES 1	//KEY_S4按下
#define KEY_S3_PRES	2	//KEY_S3按下
#define KEY_S2_PRES	3	//KEY_S2按下
#define KEY_S1_PRES 4	//KEY_S1按下

void keyInit(void);
u8 KEY_Scan(u8 mode);
#endif
