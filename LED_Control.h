/*
 * LED_Control.h
 *
 * Created: 15/05/2021 18:00:46
 *  Author: Guillaume
 */

#ifndef LED_CONTROL_H_
#define LED_CONTROL_H_

#include <stdbool.h>
#define NUMBER_OF_LEDS 3
#define LED_BREADBOARD (1 << (5))

typedef struct
{
  int ID;
  volatile uint8_t* port_Addr;
  int port_num;
  int port_State;
} LED;

extern LED listOfLED[NUMBER_OF_LEDS];

int
setup_LED(volatile uint8_t*, int);
void
turn_LED_On(int);
void
turn_LED_Off(int);
bool
get_LED_State(int);
void
toggle_LED(int);

#endif /* LED_CONTROL_H_ */
