#include "stm32f10x.h"
#include "delay.h"
#include "rgb.h"

int main(void)
{
	uint8_t pwmval = 0;
	uint8_t dir = 1;
	
	delay_init();
	RGBInit();
	
	while(1)
	{
		delay_ms(10);
		
		if(dir)
			pwmval++;
		else
			pwmval--;
		
		if(pwmval > 99)
			dir = 0;
		if(pwmval == 0)
			dir = 1;
		
		setRedLed(pwmval);
		setGreenLed(pwmval);
		setBlueLed(pwmval);
	}
}

