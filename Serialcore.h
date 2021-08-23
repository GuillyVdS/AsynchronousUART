/*
 * Serialcore.h
 *
 * Created: 02/05/2021 20:33:04
 *  Author: Guillaume
 */

#ifndef SERIALCORE_H_
#define SERIALCORE_H_

#define DEBUG_SERIAL

// Set default buffer size
#define SIZE_OF_BUFFER 100

// Set read buffer variables
extern unsigned char serialBuffer[SIZE_OF_BUFFER];
extern unsigned int bufferIndex;

// Transmit buffer variables
extern unsigned char transmitBuffer[SIZE_OF_BUFFER];
extern unsigned int transmitBufferLength;
extern unsigned char transmitBufferindex;
extern unsigned char transmitBytesSent;

// Function declarations
void USART_Init(unsigned int);

void USART_Receive(void);

void USART_PassToTransmitBuffer(unsigned char* data, unsigned int byteCount);

void USART_Send(void);

#endif /* SERIALCORE_H_ */
