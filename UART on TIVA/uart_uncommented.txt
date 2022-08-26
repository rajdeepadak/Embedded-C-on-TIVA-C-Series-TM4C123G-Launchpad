#include "TM4C123.h"                    
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

char readChar(void);
void printChar(char c);
void printString(char * string);

int main(void) 
{
    char c;
    
    SYSCTL->RCGCUART |= (1<<0);     
    SYSCTL->RCGCGPIO |= (1<<0); 
    
    GPIOA->AFSEL = (1<<1)|(1<<0);     
    GPIOA->PCTL = (1<<0)|(1<<4);      
    GPIOA->DEN = (1<<0)|(1<<1); 
   
    UART0->CTL &= ~(1<<0);    
    UART0->IBRD = 104;          
    UART0->FBRD = 11; 
    UART0->LCRH = (0x3<<5);         
    UART0->CC = 0x05;          
    UART0->CTL = (1<<0)|(1<<8)|(1<<9); 
    
    SYSCTL->RCGCGPIO |= (1<<5); 
    GPIOF->DIR = (1<<1)|(1<<2)|(1<<3);  
    GPIOF->DEN = (1<<1)|(1<<2)|(1<<3); 
    GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3)); 

    while(1)
    {
        printString("Enter \"r\", \"g\", or \"b\":\n\r");

        c = readChar();
        printChar(c);
        printString("\n\r");
        
        switch(c)
        {
        case 'r':
          GPIOF->DATA = (1<<1);
          break;
        case 'b':
          GPIOF->DATA = (1<<2);
          break;
        case 'g':
          GPIOF->DATA = (1<<3);
          break;
        default:
          GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3));
          break;
        }
     }
    
}

char readChar(void)  
{
    char c;
    while((UART0->FR & (1<<4)) != 0);
    c = UART0->DR;                 
    return c;                    
}

void printChar(char c)  
{
    while((UART0->FR & (1<<5)) != 0);
    UART0->DR = c;           
}

void printString(char * string)
{
  while(*string)
  {
    printChar(*(string++));
  }
}