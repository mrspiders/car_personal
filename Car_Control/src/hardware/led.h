#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"
#include "delay.h"

void ledInit(void);
void setPWMled(u8 val);


void setPWMled(u8 val);
void LED2Flash(void);
void LED3Flash(void);
void LED3OneBreath(void);

#endif
