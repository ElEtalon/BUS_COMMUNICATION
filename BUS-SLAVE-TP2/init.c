//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------
#include "msp430g2231.h"
#include "init.h"

void InitPort(void){
	  P1OUT =  0x10;                        // P1.4 set, else reset
	  P1REN |= 0x10;                        // P1.4 pullup
	  P1DIR = 0x01;                         // P1.0 output, else input
}

void InitSPI(void){
	  USICTL0 |= USIPE7 + USIPE6 + USIPE5 + USIOE; // Port, SPI slave
	  USICTL1 |= USIIE;                     // Counter interrupt, flag remains set
	  USICTL0 &= ~USISWRST;                 // USI released for operation
	  USISRL = P1IN;                        // init-load data
	  USICNT = 8;                           // init-load counter
	  USICTL1 = USICKPL;                  // Setup clock polarity
	  USICKCTL = USICKPH;					// phase
}
