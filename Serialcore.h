/*
 * Serialcore.h
 *
 * Created: 02/05/2021 20:33:04
 *  Author: Guillaume
 */ 


#ifndef SERIALCORE_H_
#define SERIALCORE_H_

//function declaration

void USART_Init(unsigned int);

void USART_Transmit( unsigned char * data , unsigned int byteCount );

unsigned char USART_Receive( void );



#endif /* SERIALCORE_H_ */