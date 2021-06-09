/*
 * UARTTEST.c
 *
 * Created: 02/05/2021 20:14:09
 * Author : Guillaume
 */ 

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <stdio.h>
#include  "Serialcore.h"


#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD-1)

#define LED_BREADBOARD (1 << (5)) //breadboard port on chip
	
volatile uint8_t * ddrE = (volatile uint8_t *) (0x0D + 0x20);
volatile uint8_t * portE = (volatile uint8_t *) (0x0E + 0x20);

unsigned char charTest;
const char LED_On[] = "Turn LED on";
const char LED_Off[] = "Turn LED off";

void checkForCommand(unsigned char * inputbuffer){
	if(strncmp( (const char *)inputbuffer, LED_On, strlen(LED_On) ) == 0)
	{
		USART_PassToTransmitBuffer(serialBuffer, bufferIndex);
		*portE |= LED_BREADBOARD;		
	}
	else if(strncmp( (const char *)inputbuffer, LED_Off, strlen(LED_Off) ) == 0)
	{
		USART_PassToTransmitBuffer(serialBuffer, bufferIndex);
		*portE  &=  ~(LED_BREADBOARD);
	}
	else
	{
		USART_PassToTransmitBuffer((unsigned char *)"error", 5);
	}
}



unsigned char testvR;
int main(void)
{
	*ddrE |= LED_BREADBOARD;
	USART_Init ( MYUBRR );

    while (1) 
    {
		//runs function checking to see if any data is being sent 
		USART_Receive();
		
		//checks last entered character in serialbuffer (current bufferindex -1 because previous char) 
		//to see if escape character has been entered to reset buffer
		if(serialBuffer[ (bufferIndex - 1) ] == 0x0D ) //0xDD
		{	
			checkForCommand(serialBuffer);
			memset(serialBuffer,0,bufferIndex);
			bufferIndex = 0;
		}
		USART_Send(); //sends any available characters in transmit buffer	
    }
}






