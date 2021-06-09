/*
 * SerialCore.c
 *
 * Created: 02/05/2021 20:28:18
 *  Author: Guillaume
 */ 

#include <avr/io.h>
#include  "Serialcore.h"

unsigned char serialBuffer[SIZE_OF_BUFFER] = {0};		//buffer 
unsigned int bufferIndex = 0;				//index tracking track of cursor in the buffer
unsigned char transmitBuffer[SIZE_OF_BUFFER] = {0};	//buffer for characters to transmit
unsigned char transmitBufferindex = 0;		//index to keep track of cursor in the transmit buffer
unsigned char transmitBytesSent = 0;		//second index to keep track of how many characters have been sent

void USART_Init( unsigned int ubrr){
	// Set baud rate 
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	//Set frame format: 8data, 2stop bit
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
} 

void USART_PassToTransmitBuffer(unsigned char * data, unsigned int byteCount){
	for(int i = 0 ; i < byteCount; i++){
		transmitBuffer[transmitBufferindex] = data[i];
		transmitBufferindex++;
	}	
}

void USART_Send(void){
	//check if any characters remain to be send in transmitbuffer
	if(transmitBufferindex != transmitBytesSent){
		//checks UART control and status register if transmit is available
		if(UCSR0A & (1<<UDRE0)){
		//Put data into UART buffer, sends data , increments total bytes sent
		UDR0 = transmitBuffer[transmitBytesSent];
		transmitBytesSent++;	
		}
	}
}

void USART_Receive( void ){
	/* Checks UART Control and status register for presence of any new bytes in the UART buffer*/
	if ( UCSR0A & (1<<RXC0) ){
		serialBuffer[bufferIndex] = UDR0; //adds data to the serial buffer at current space of index
		/*
		#ifdef DEBUG_SERIAL 
			UDR0 = serialBuffer[bufferIndex];
		#endif
		*/
		bufferIndex++; //increments buffer index to next free space
	}
}