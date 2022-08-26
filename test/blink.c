#include "TM4C123.h"                    // Device head

void delay(int ms);

void sysdelay(int count);
int main()
{
	SYSCTL->RCGCGPIO |= 0X20;		//port F clocked
	
	GPIOF->DIR |= 0X0E;
	GPIOF->DEN |= 0X0E;
	
	while(1)
		{
		GPIOF->DATA |= 0X02;				//RED
		sysdelay(1000);
		GPIOF->DATA &=~ 0X02;
		sysdelay(1000);
		
		GPIOF->DATA |= 0X04;			//BLUE
		sysdelay(1000);
		GPIOF->DATA &=~ 0X04;
		sysdelay(1000); 
			
		GPIOF->DATA |= 0X08;			//GREEN
		sysdelay(1000);
		GPIOF->DATA &=~ 0X08;
		sysdelay(1000);
		
		
		
	}
}

void delay(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
	{
		for(j=0;j<3180;j++);
	}
}  

void sysdelay(int count)
{
	int i;
	SysTick->LOAD = 16000;
	SysTick->VAL = 0;
	SysTick->CTRL=5;
	
	for(i=0;i<count;i++)
	{
		while((SysTick->CTRL & (0x10000))==0 ){}
	}
	SysTick->CTRL=0;
}