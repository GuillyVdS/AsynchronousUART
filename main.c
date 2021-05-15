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

#define LED_BREBBOARD (1 << (5)) //breadboard port

//typedef enum {LED_ON, LED_OFF}LED_State;
//typedef enum {LED_Board, LED_External}LED_Choice;
	
volatile uint8_t * ddrE = (volatile uint8_t *) (0x0D + 0x20);
volatile uint8_t * portE = (volatile uint8_t *) (0x0E + 0x20);

unsigned char charTest;
const char LED_On[] = "Turn LED on";
const char LED_Off[] = "Turn LED off";
//char ack[] = "Received: ";
//char message[] = "TESTING \n" ;

/*
void transmitword(char * bufferInput, int byteCount)
{

}
*/

void checkForCommand(unsigned char * inputbuffer){
	if(strncmp( (const char *)inputbuffer, LED_On, strlen(LED_On) ) == 0)
	{
		//USART_PassToTransmitBuffer("mlem", 4);
		USART_PassToTransmitBuffer(serialBuffer, bufferIndex);
		*portE |= LED_BREBBOARD;
		
		
		
	}
	else if(strncmp( (const char *)inputbuffer, LED_Off, strlen(LED_Off) ) == 0)
	{
		USART_PassToTransmitBuffer(serialBuffer, bufferIndex);
		*portE  &=  ~(LED_BREBBOARD);

	}
	else
	{
		USART_PassToTransmitBuffer((unsigned char *)"error", 5);
	}
	
	
}



unsigned char testvR;
int main(void)
{
	*ddrE |= LED_BREBBOARD;
    /* Replace with your application code */
	USART_Init ( MYUBRR );
	//USART_Transmit( (unsigned char *)message, (unsigned int)strlen( (const char *)message));
    while (1) 
    {
		//runs function checking to see if any data is being sent 
		USART_Receive();
		
		
		
		//checks last entered character in serialbuffer (current bufferindex -1 because previous char) 
		//to see if escape character has been entered to reset buffer
		if(serialBuffer[ (bufferIndex - 1) ] == 0x0D ) //0xDD
		{	
			//USART_PassToTransmitBuffer(serialBuffer, bufferIndex); //sends 
			checkForCommand(serialBuffer);
			memset(serialBuffer,0,bufferIndex);
			bufferIndex = 0;
		}
		
		USART_Send(); //sends any available characters in transmit buffer
		
    }
}


//will need to check bufferlength vs buffersize in order to reset and loop back to beginning of buffer




/*
-move all serial uart functionality into separate files SerialCore.c and Serialcore.h DONE
-then create a function that you can pass a string - a const * char - that will print to command line DONE
-then create a system that will listen to all sent characters from a serial terminal and wait for new line DONE
    then process them using strcmp against some commands
 */





