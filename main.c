/*
 * UARTTEST.c
 *
 * Created: 02/05/2021 20:14:09
 * Author : Guillaume
 */ 

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include  "Serialcore.h"


#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD-1)

unsigned char charTest;
char ack[] = "Received: ";
char message[] = "Press key for input \n" ;
unsigned char serialBuffer[100];
unsigned int bufferIndex = 0;

/*
void transmitword(char * bufferInput, int byteCount)
{

}
*/



int main(void)
{
    /* Replace with your application code */
	USART_Init ( MYUBRR );
	USART_Transmit( (unsigned char *)message, (unsigned int)strlen( (const char *)message));
    while (1) 
    {
		charTest = USART_Receive();
		if(charTest != 0)
		{	
			USART_Transmit((unsigned char *)ack, strlen((const char *)ack));
			USART_Transmit( &charTest, 1);
		}
		
		//transmitword(serialBuffer, strlen(serialBuffer));
		
		
		//USART_Transmit(serialBuffer, strlen(serialBuffer));

		_delay_ms(2000);
    }
}

/*
-move all serial uart functionality into separate files SerialCore.c and Serialcore.h
-then create a function that you can pass a string - a const * char - that will print to command line
-then create a system that will listen to all sent characters from a serial terminal and wait for new line
    then process them using strcmp against some commands
 */

