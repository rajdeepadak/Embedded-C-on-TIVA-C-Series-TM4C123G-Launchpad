#include "TM4C123.h"                    // Device header

uint8_t leds = 0x00;

void writeSPI(uint8_t data)
{
	SSI2->DR = data;
	while((SSI2->SR & (1<<0)) == 0);
}

int main()
{
	//Enable SSI module using RCGCSSI
	SYSCTL->RCGCSSI = (1<<2);
	
	
	//Enable clock using RCGCGPIO to appropriate GPIO module
	SYSCTL->RCGCGPIO = (1<<1);
	
	
	//Enable Alternate functions on GPIO pins
	GPIOB->AFSEL |= (1<<4)|(1<<6)|(1<<7);
	GPIOB->AFSEL &= ~(1<<5);       //Turn off PB5 Alternate function
	
	
	//Assign SSI signal to appropriate pins
	GPIOB->PCTL |= (2<<16)|(2<<20)|(2<<24)|(2<<28);
		
	
	//Digital Enable each pin
	GPIOB->DEN |= (1<<4)|(1<<5)|(1<<6)|(1<<7);
	GPIOB->DIR |= (1<<5);          //make PB5 as output. 
	
	
	//Clear SSE before any configuration
	SSI2->CR1 &= ~(1<<1);
	
	
	//Tiva is master
	SSI2->CR1 = 0x00000000;
	
	
	//SSI clock is system clock
	SSI2->CC = 0x00;
	
	
	//Set divisor factor (value between 2 and 254)
	//Default frequency is 1.6 Mhz
	SSI2->CPSR = 10;
	
	
	//Sending 3 Bytes
	SSI2->CR0 = (0x7<<0);
	
	
	//No DMA Configured
	//Enable SSE to allow SPI 
	SSI2->CR1 |= (1<<1);
	
	
	//Chip Select(PB5) is initially High, then switched to LOW
	GPIOB->DATA |= (1<<5);
	GPIOB->DATA &= ~(1<<5);
	
	
	//Send 3 bytes of Data
	//I/O Expander IC                   //For MCP23S08 
	writeSPI(0x40);                     //writeSPI(0x40)
	writeSPI(0x0A);                     //writeSPI(0x00)
	writeSPI(0x98);                     //writeSPI(0x00)
	
	
	//Delay given to match one half period of clock frequency (See page 959 Freescale SPI Format)
	for(int i = 0 ; i<15 ; i++);
	
	
	//Chip Select is then turned High
	GPIOB->DATA |= (1<<5);
		
	
	while(1)
	{
		//Chip Select is turned Low again
		GPIOB->DATA &= ~(1<<5);
		
		
		//Send 3 Bytes of Data
		writeSPI(0x40);
		writeSPI(0x0A);
		writeSPI(leds++);  //leds should glow in binary format from 00000000 to 11111111 OR (0-255)
		
		
		//Delay given to match one half period of clock frequency (See page 959 Freescale SPI Format)
		for(int i = 0 ; i<15 ; i++);
		
		
		//Chip Select is turned High
		GPIOB->DATA |= (1<<5);
		
		
		//Delay to observe led change.
		//Change value of 100000 accordingly
		for(int i = 0 ; i<100000 ; i++);
	}
	
	return 0;
}
	
	
	
	
	
	