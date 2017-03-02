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
	WDTCTL = WDTPW + WDTHOLD;                      // Stop WDT
	BCSCTL1 = CALBC1_1MHZ;               // Set DCO
	DCOCTL = CALDCO_1MHZ;

	P1OUT = 0xC0;                        // P1.6 & P1.7 Pullups
	P1REN |= 0xC0;                       // P1.6 & P1.7 Pullups
	P1DIR = 0xFF;                        // Unused pins as outputs
	P2OUT = 0;
	P2DIR = 0xFF;
}

void InitSPI(void){
	USICTL0 = USIPE6+USIPE7+USISWRST;    // Port & USI mode setup
	USICTL1 = USII2C+USIIE+USISTTIE;     // Enable I2C mode & USI interrupts
	USICKCTL = USICKPL;                  // Setup clock polarity
	USICNT |= USIIFGCC;                  // Disable automatic clear control
	USICTL0 &= ~USISWRST;                // Enable USI
	USICTL1 &= ~USIIFG;                  // Clear pending flag
	_EINT();
}
