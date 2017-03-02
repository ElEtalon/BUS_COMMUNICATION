//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------

#include <msp430g2231.h>
#include "stdbool.h"
#include "io.h"

/**
* Handles the received byte and calls the needed functions.\
**/
void Receive(bool * hasReceived, unsigned int * RXByte, unsigned int * TXByte)
{
	*hasReceived = false;		// Clear the flag
	switch(*RXByte)							// Switch depending on command value received
	{
		case TEST:
		break;
		default:
			P1OUT |= BIT0;				// Turn on LED while testing
			*TXByte = 0x041; // A
			Transmit();
			*TXByte = 0;
			Transmit();
			break;
	}
}

/**
* Transmits the value currently in TXByte. The function waits till it is
*   finished transmiting before it returns.
**/
void Transmit(bool * isReceiving, unsigned int * RXByte, unsigned int * TXByte)
{
	while(isReceiving);			// Wait for RX completion
	*TXByte |= 0x100;			// Add stop bit to TXByte (which is logical 1)
	*TXByte = TXByte << 1;			// Add start bit (which is logical 0)
	BitCnt = 0xA;				// Load Bit counter, 8 bits + ST/SP

	CCTL0 = OUT;				// TXD Idle as Mark
	TACTL = TASSEL_2 + MC_2;		// SMCLK, continuous mode
	CCR0 = TAR;				// Initialize compare register
	CCR0 += 104;			// Set time till first bit
	CCTL0 =  CCIS0 + OUTMOD0 + CCIE; 	// Set signal, intial value, enable interrupts
	while ( CCTL0 & CCIE ); 		// Wait for previous TX completion
}
