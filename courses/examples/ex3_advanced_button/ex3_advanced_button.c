/*
 * ex3_advanced_button.c
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

/*
 * BP2 definitions
 */
#define BP2_PIO  PIOA
#define BP2_PIN  PIO_PA5
#define BP2_PID  ID_PIOA
#define BP2_IRQ  PIOA_IRQn

// Global state variable for LED toggle
static uint32_t ul_toggle=0 ;

/*
 * \brief Initialization of board components.
 *
 */
void hardware_init( void )
{
  // Assign the LED1 pin as OUTPUT
  LED1_PIO->PIO_OER = LED1_PIN ;
  // Clear the LED1 pin level, ie put to 0V -> the pin is connected to the LED cathode, anode is connected to +3.3V.
  LED1_PIO->PIO_CODR = LED1_PIN ;
  
  // Assign the LED2 pin as OUTPUT
  LED2_PIO->PIO_OER = LED2_PIN ;
  // Set the LED2 pin level, ie put to 0V -> the pin is connected to the LED cathode, anode is connected to +3.3V.
  LED2_PIO->PIO_SODR = LED2_PIN ;
  
  // Assign the BP2 pin as INPUT
  BP2_PIO->PIO_ODR = BP2_PIN ;
  // Clock the BP2 associated PIO, to allow input measure
  PMC->PMC_PCER0 = 1 << BP2_PID ;

  // Set debouncing filter on BP2 pin
  BP2_PIO->PIO_IFSCER = BP2_PIN ;
  // Enable the filter 
  BP2_PIO->PIO_IFER = BP2_PIN ;
  // Set falling edge detection interrupt on BP2 pin (connection to GND by pressing the button)
  BP2_PIO->PIO_ESR = BP2_PIN ;
  BP2_PIO->PIO_FELLSR = BP2_PIN ;
  BP2_PIO->PIO_AIMER = BP2_PIN ;

  // Enable interrupt for BP2 associated PIO controller
  NVIC_EnableIRQ( BP2_IRQ ) ;
  // Enable interrupt for BP2 pin
  BP2_PIO->PIO_IER = BP2_PIN ;
}

/*
 * \brief Toggle the LED.
 *
 */
void toggle_LED( void )
{
  if ( ul_toggle == 0 )
  {
    // Set the LED1 pin level, ie put to 3.3V -> this light off the LED
    LED1_PIO->PIO_SODR=LED1_PIN ;
  
    // Clear the LED2 pin level, ie put to 0V -> this light on the LED
    LED2_PIO->PIO_CODR=LED2_PIN ;

    ul_toggle=1 ;
  }
  else
  {
    // Clear the LED1 pin level, ie put to 0V -> this light on the LED
    LED1_PIO->PIO_CODR=LED1_PIN ;
  
    // Set the LED2 pin level, ie put to 3.3V -> this light off the LED
    LED2_PIO->PIO_SODR=LED2_PIN ;

    ul_toggle=0 ;
  }
}

/**
 * \brief PIOA interrupt handler.
 *
 */
void PIOA_Handler( void )
{
  uint32_t ul_status ;

  /* Read PIO controller status */
  ul_status = BP2_PIO->PIO_ISR ;
  ul_status &= BP2_PIO->PIO_IMR ;

  /* Check pending events */
  if ( (ul_status & BP2_PIN) != 0 )
  {
    toggle_LED() ;
  }
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main( void )
{
  // Initialize hardware
  hardware_init() ;

  while ( 1 )
  {
  }
}


