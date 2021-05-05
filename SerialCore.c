/*
 * SerialCore.c
 *
 * Created: 02/05/2021 20:28:18
 *  Author: Guillaume
 */ 

#include <avr/io.h>

#include  "Serialcore.h"


void USART_Init( unsigned int ubrr){
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
} // USART_Init


void USART_Transmit( unsigned char * data , unsigned int byteCount ){
	
	for(int i = 0 ; i < byteCount; i++){
		while ( !( UCSR0A & (1<<UDRE0)) );
		// Put data into buffer, sends the data /
		UDR0 = data[i];
	}
	
}



/*
void USART_Transmit( unsigned char * data , int byteCount ){
	
	//for(int i = 0 ; i < byteCount; i++){
	while(byteCount--){	
		while ( !( UCSR0A & (1<<UDRE0)) );
		/ Put data into buffer, sends the data /
		
		UDR0 = *(data++);
	}
	
}
*/


unsigned char USART_Receive( void ){
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}