/*
 * Serialcore.h
 *
 * Created: 02/05/2021 20:33:04
 *  Author: Guillaume
 */


#ifndef SERIALCORE_H_
#define SERIALCORE_H_


	#define DEBUG_SERIAL
	//variable declaration

	//set default buffer size
	#define SIZE_OF_BUFFER 100


	//set read buffer variables
	extern unsigned char serialBuffer[SIZE_OF_BUFFER];
	extern unsigned int bufferIndex;



	//transmit transmit buffer variables
	extern unsigned char transmitBuffer[SIZE_OF_BUFFER];
	extern unsigned int transmitBufferLength;
	extern unsigned int transmitBufferRead;
	extern unsigned int transmitBufferWrite;



	//old vars
	extern unsigned char transmitBufferindex;
	extern unsigned char transmitBytesSent;

	//function declaration
	void USART_Init(unsigned int);

	//void USART_Transmit( unsigned char * data , unsigned int byteCount );

	void USART_Receive( void );

	void USART_PassToTransmitBuffer(unsigned char * data, unsigned int byteCount);

	void USART_Send(void);



#endif /* SERIALCORE_H_ */
