#ifndef __CONTROL_H
#define __CONTROL_H	 
#include "stm32f10x.h"


void moveInit();
void moveForward(u8 val);
void moveBack(u8 val);

void turnStop(void);
void turnLeft(void);
void turnRight(void);

#endif

