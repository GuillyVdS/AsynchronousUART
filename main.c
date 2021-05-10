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
//unsigned char LED_On = "Turn LED on";
//unsigned char LED_Off = "Turn LED off";
//char ack[] = "Received: ";
//char message[] = "TESTING \n" ;

/*
void transmitword(char * bufferInput, int byteCount)
{

}
*/


unsigned char testvR;
int main(void)
{
    /* Replace with your application code */
	USART_Init ( MYUBRR );
	//USART_Transmit( (unsigned char *)message, (unsigned int)strlen( (const char *)message));
    while (1) 
    {
		//runs function checking to see if any data is being sent 
		USART_Receive();
		
		
		if(serialBuffer[ (bufferIndex - 1) ] == 0x0D ) //0xDD
		{	
			
			USART_PassToTransmitBuffer(serialBuffer, bufferIndex); //sends 
			memset(serialBuffer,0,bufferIndex);
			bufferIndex = 0;
		}
		
		USART_Send(); //sends any available characters in transmit buffer
		
    }
}
/*
void checkForCommand(serialBuffer){
	if()
	
	
}
*/
/*
-move all serial uart functionality into separate files SerialCore.c and Serialcore.h DONE
-then create a function that you can pass a string - a const * char - that will print to command line DONE
-then create a system that will listen to all sent characters from a serial terminal and wait for new line DONE
    then process them using strcmp against some commands
 */





