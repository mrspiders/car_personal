#ifndef __RGB_H
#define __RGB_H	 
#include "system_stm32f10x.h"
#include "stm32f10x_gpio.h"


void LEDInit(void);
void RGBInit(u16 prescaler, u16 period);

void setRedLed(u8 val);
void setGreenLed(u8 val);
void setBlueLed(u8 val);

#endif

