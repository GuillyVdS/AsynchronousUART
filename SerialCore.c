/*
 * SerialCore.c
 *
 * Created: 02/05/2021 20:28:18
 *  Author: Guillaume
 */

#include <avr/io.h>

#include "Serialcore.h"

unsigned char serialBuffer[100] = { 0 };
unsigned int bufferIndex = 0;
unsigned char transmitBuffer[100] = { 0 };
unsigned char transmitBufferindex = 0;
unsigned char transmitBytesSent = 0;

void
USART_Init(unsigned int ubrr)
{
  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  /* Enable receiver and transmitter */
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);
} // USART_Init

void
USART_PassToTransmitBuffer(unsigned char* data, unsigned int byteCount)
{
  for (int i = 0; i < byteCount; i++) {
    transmitBuffer[transmitBufferindex] = data[i];
    transmitBufferindex++;
  }
}

void
USART_Send(void)
{
  // check if any characters remain to be send in transmitbuffer
  if (transmitBufferindex != transmitBytesSent) {
    // check if uart transmit is available
    if (UCSR0A & (1 << UDRE0)) {
      // Put data into buffer, sends data
      UDR0 = transmitBuffer[transmitBytesSent];
      transmitBytesSent++;
    }
  }
}

void
USART_Receive(void)
{
  /* Wait for data to be received */
  if (UCSR0A & (1 << RXC0)) {
    serialBuffer[bufferIndex] = UDR0;

#ifdef DEBUG_SERIAL
    // UDR0 = serialBuffer[bufferIndex];
#endif

    bufferIndex++;
  }
}
