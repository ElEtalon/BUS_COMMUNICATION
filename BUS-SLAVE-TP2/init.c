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
	  P1OUT = 0x00;                        // P1.4 set, else reset
	  P1DIR = BIT0;                         // P1.0 output, else input

	  P1DIR &= ~(BIT1 + BIT5 + BIT7);
	  P1SEL |= BIT5 + BIT6 + BIT7;
	  P1DIR |= BIT6;
}

void InitSPI(void){
	  USICTL0 |= USISWRST;                 // start config
	  USICTL0 |= USIPE7 + USIPE6 + USIPE5 + USIOE; // Port, SPI slave
	  USICTL1 |= USIIE;                     // Counter interrupt, flag remains set

	  USICNT = 8;                           // init-load counter
	  //USICTL1 = USICKPL;                  // Setup clock polarity --> keep low
	  USICTL1 = USICKPH;					// phase
	  USICTL0 &= ~USISWRST;                 // USI released for operation stop config
}
