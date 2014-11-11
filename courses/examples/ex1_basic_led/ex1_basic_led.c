/*
 * ex1_basic_led.c
 *  Author: thibaut.viard
 */ 

#include "sam.h"

/*
 * LED1 definitions
 */
#define LED1_PIO  PIOC
#define LED1_PIN  PIO_PC10

/*
 * LED2 definitions
 */
#define LED2_PIO  PIOC
#define LED2_PIN  PIO_PC17

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
  // Assign the LED1 pin as OUTPUT
  LED1_PIO->PIO_OER=LED1_PIN ;
  // Clear the LED1 pin level, ie put to 0V -> the pin is connected to the LED cathode, anode is connected to +3.3V.
  LED1_PIO->PIO_CODR=LED1_PIN ;
  
  // Assign the LED2 pin as OUTPUT
  LED2_PIO->PIO_OER=LED2_PIN ;
  // Clear the LED2 pin level, ie put to 0V -> the pin is connected to the LED cathode, anode is connected to +3.3V.
  LED2_PIO->PIO_CODR=LED2_PIN ;
}

