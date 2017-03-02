//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------
#include "msp430g2231.h"
#include "init.h"

void InitSPI(void){
	WDTCTL = WDTPW + WDTHOLD;	// Stop WDT

	BCSCTL1 = CALBC1_1MHZ;		// Set range
	DCOCTL = CALDCO_1MHZ;		// SMCLK = DCO = 1MHz

	P1SEL |= BIT1;				// Connected TXD to timer pin
	P1DIR |= BIT1;

	P1IES |= BIT2;				// RXD Hi/lo edge interrupt
	P1IFG &= ~BIT2;				// Clear RXD (flag) before enabling interrupt
	P1IE |= BIT2;				// Enable RXD interrupt
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;				// Turn off LED at P1.0
}
