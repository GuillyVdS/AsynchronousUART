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

char serialBuffer[] = "maow bork maow meowies";
int bufferIndex = 0;

/*
void transmitword(char * bufferInput, int byteCount)
{

}
*/



int main(void)
{
    /* Replace with your application code */
	USART_Init ( MYUBRR );
    while (1) 
    {
		//transmitword(serialBuffer, strlen(serialBuffer));
		
		
		USART_Transmit(serialBuffer, strlen(serialBuffer));
		/*
		USART_Transmit('W');
		USART_Transmit('U');
		USART_Transmit(' ');
		USART_Transmit(':');
		USART_Transmit('3');
		USART_Transmit(' ');
		USART_Transmit(' ');
		*/
		_delay_ms(2000);
    }
}

