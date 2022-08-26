#include<stdint.h>
#include "TM4C123.h"                    // Device header

void delayms(int time);

void delayms(int time)
{
	int x, y;
	for(x = 0 ; x<time ; x++)
	{
		for(y = 0 ; y<7900 ; y++);
	}
}

int main()
{
	SYSCTL -> RCC |= 0x02400540;
	SYSCTL -> RCGCGPIO |= 0x20;
	GPIOF -> DIR |= 0x02;
	GPIOF -> DEN |= 0x02;
	
	while(1)
	{
		GPIOF -> DATA = 0x02;
		delayms(1000);
		GPIOF -> DATA = 0x00;
		delayms(1000);
	}
}