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

	extern unsigned char serialBuffer[100];
	//extern unsigned int serialBufferLength = 0;
	extern unsigned int bufferIndex;
	extern unsigned char transmitBuffer[100];
	extern unsigned char transmitBufferindex;
	extern unsigned char transmitBytesSent;

	//function declaration

	void USART_Init(unsigned int);

	//void USART_Transmit( unsigned char * data , unsigned int byteCount );

	void USART_Receive( void );

	void USART_PassToTransmitBuffer(unsigned char * data, unsigned int byteCount);

	void USART_Send(void);



#endif /* SERIALCORE_H_ */