/*
 * LED_Control.c
 *
 * Created: 15/05/2021 18:01:15
 *  Author: Guillaume
 */

#include "LED_Control.h"
#include <avr/io.h>

#define NUMBER_OF_LEDS 3

typedef struct LED
{
  int ID;
  volatile uint8_t* port_Addr;
  int port_num;
  int port_State;
};

LED listOfLED[NUMBER_OF_LEDS] = { 0 };
static int listOfLEDIndex;

int setup_LED(volatile uint8_t* address, int port_num)
{
  volatile uint8_t* ddrE = (volatile uint8_t*)(0x0D + 0x20);

  listOfLED[listOfLEDIndex].ID = listOfLEDIndex; // Set LED ID in struct using ID in array
  listOfLED[listOfLEDIndex].port_Addr = address; // Set LED address
  listOfLED[listOfLEDIndex].port_num = port_num;
  *(address - 1) |= port_num; // Turn LED into output.
  listOfLEDIndex++;
  return (listOfLEDIndex - 1);
}

void turn_LED_On(int led_ID)
{

  *(listOfLED[led_ID].port_Addr) |= listOfLED[led_ID].port_num;
  listOfLED[led_ID].port_State = 1;
}

void turn_LED_Off(int led_ID)
{

  if (led_ID >= 0 && led_ID < 3) {
    *listOfLED[led_ID].port_Addr &= ~(listOfLED[led_ID].port_num);
    listOfLED[led_ID].port_State = 0;
  }
}

bool get_LED_State(int led_ID)
{
  if (listOfLED[led_ID].port_State == 1) {
    return true;
  } else {
    return false;
  }
}

/*Utilizes the above functions to check LED status and change it to the opposite
status.*/

void toggle_LED(int led_ID)
{
  if (get_LED_State(led_ID) == false) {
    turn_LED_On(led_ID);
  } else {
    turn_LED_Off(led_ID);
  }
}
