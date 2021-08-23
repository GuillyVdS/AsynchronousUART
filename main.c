/*
 * UARTTEST.c
 *
 * Created: 02/05/2021 20:14:09
 * Author : Guillaume
 */

#include "Serialcore.h"
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#define BAUD 9600
/*Function used to calculate Baud rate as specified by datasheet.
F_CPU is defined within delay.h as frequency of processor in Hertz.*/
#define MYUBRR (F_CPU / 16 / BAUD - 1)
#define LED_BREADBOARD (1 << (5))
#define RETURN_CHAR 0x0D

/*This was me learning how to use volatiles instead of predefined BSP defines.
0x20 is used as offset for memory addresses. See C datasheet "page 403
atmel-2549-8-bit-avr-microcontroller-atmega640-1280-1281-2560-2561_datasheet.pdf"*/

volatile uint8_t* ddrE = (volatile uint8_t*)(0x0D + 0x20);
volatile uint8_t* portE = (volatile uint8_t*)(0x0E + 0x20);

const char LED_On[] = "Turn LED on";
const char LED_Off[] = "Turn LED off";
const char Error_Message = "error";

/*Takes serialbuffer as input and compares against some predefined commands
In this instance this program was set up to either turn an LED ON or OFF.
If the command is succesful, it will get transmitted, else error gets transmitted */

void checkForCommand(unsigned char* inputbuffer)
{
  if (strncmp((const char*)inputbuffer, LED_On, strlen(LED_On)) == 0) {
    USART_PassToTransmitBuffer(serialBuffer, bufferIndex);
    *portE |= LED_BREADBOARD;

  } else if (strncmp((const char*)inputbuffer, LED_Off, strlen(LED_Off)) == 0) {
    USART_PassToTransmitBuffer(serialBuffer, bufferIndex);
    *portE &= ~(LED_BREADBOARD);

  } else {
    USART_PassToTransmitBuffer((unsigned char*)Error_Message, strlen(Error_Message));
  }
}

int main(void)
{
  *ddrE |= LED_BREADBOARD;
  USART_Init(MYUBRR); // Initialises uart using defined BAUD rate.

  /*While loop executes indefinitely. USART_Receive will return data when
  information is entered into the com port. */
  while (1) {

    USART_Receive(); // Checking to see if any data is being sent

    /*Checks last entered character in serialbuffer (current bufferindex -1
     because previous char) to see if escape character has been entered to
     reset buffer.*/
    if (serialBuffer[(bufferIndex - 1)] == RETURN_CHAR) {
      checkForCommand(serialBuffer);
      memset(serialBuffer, 0, bufferIndex);
      bufferIndex = 0;
    }

    USART_Send(); // Sends any available characters in transmit buffer.
  }
}

/*Will need to check bufferlength vs buffersize in order to reset and loop back
 to beginning of buffer*/
