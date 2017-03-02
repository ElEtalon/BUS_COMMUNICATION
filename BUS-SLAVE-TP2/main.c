/******************************************************************************
 *                      MSP430 ADC10 Example for the G2231
 *
 * Description:	This code provides an example for using the 10 bit ADC in the
 *				MSP430G2231. The code requires either a terminal program or
 *				the application provided on the blog mentioned below.
 *				depending on which ascii character is sent to the device,
 *				either VCC, the temperature sensor, or an external pin will
 *				be measured once and the results sent to the computer.
 *
 *				Originally created for "NJC's MSP430 LaunchPad Blog".
 *
 * Author: Nicholas J. Conn - http://msp430launchpad.com
 * Email: webmaster at msp430launchpad.com
 * Date: 08-29-10
 ******************************************************************************/

#include "msp430g2231.h"
#include "stdbool.h"
#include "main.h"
#include "init.h"
#include "io.h"

void main(void)
{
	*isReceiving = false; // Set initial values
	*hasReceived = false;

    InitSPI();

	 __bis_SR_register(GIE); // interrupts enabled

	P1OUT |= BIT6;				// Turn on LED while testing

	while(1)
	{
		Receive(isReceiving, hasReceived, RXByte, TXByte, BitCnt);
		/*if (*hasReceived)		// If the device has recieved a value
		{
			Receive(isReceiving, hasReceived, RXByte, TXByte, BitCnt);
		}
		/*if(ADCDone)				// If the ADC is done with a measurement
		{
			ADCDone = false;				// Clear flag
			TXByte = ADCValue & 0x00FF;		// Set TXByte
			Transmit();						// Send
			TXByte = (ADCValue >> 8);		// Set TXByte to the upper 8 bits
			TXByte = TXByte & 0x00FF;
			Transmit();
		}*/
		if (~(*hasReceived))			// Loop again if either flag is set
			 __bis_SR_register(CPUOFF + GIE);	// LPM0, the ADC interrupt will wake the processor up.
	}
}

/**
* Starts the receive timer, and disables any current transmission.
**/
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	*isReceiving = true;
	P1IE &= ~BIT2;			// Disable RXD interrupt
	P1IFG &= ~BIT2;			// Clear RXD IFG (interrupt flag)
	TACTL = TASSEL_2 + MC_2;	// SMCLK, continuous mode
	CCR0 = TAR;			// Initialize compare register
	CCR0 += Bit_time_5;		// Set time till first bit
	CCTL0 = OUTMOD1 + CCIE;		// Dissable TX and enable interrupts
	RXByte = 0;			// Initialize RXByte
	*BitCnt = 0x9;			// Load Bit counter, 8 bits + ST
}

/**
* Timer interrupt routine. This handles transmiting and receiving bytes.
**/
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	if(!*isReceiving)
	{
		CCR0 += Bit_time;			// Add Offset to CCR0
		if ( *BitCnt == 0)			// If all bits TXed
		{
			TACTL = TASSEL_2;		// SMCLK, timer off (for power consumption)
			CCTL0 &= ~ CCIE ;		// Disable interrupt
		}
		else
		{
			CCTL0 |=  OUTMOD2;		// Set TX bit to 0
			if (*TXByte & 0x01)
			CCTL0 &= ~ OUTMOD2;		// If it should be 1, set it to 1
			*TXByte = *TXByte >> 1;
			*BitCnt --;
		}
	}
	else
	{
		CCR0 += Bit_time;			// Add Offset to CCR0
		if ( *BitCnt == 0)
		{
			TACTL = TASSEL_2;		// SMCLK, timer off (for power consumption)
			CCTL0 &= ~ CCIE ;		// Disable interrupt
			*isReceiving = false;
			P1IFG &= ~BIT2;			// clear RXD IFG (interrupt flag)
			P1IE |= BIT2;			// enabled RXD interrupt
			if ( (*RXByte & 0x201) == 0x200) // Validate the start and stop bits are correct
			{
				*RXByte = *RXByte >> 1;	// Remove start bit
				*RXByte &= 0xFF;		// Remove stop bit
				*hasReceived = true;
			}
			__bic_SR_register_on_exit(CPUOFF);	// Enable CPU so the main while loop continues
		}
		else
		{
			if ( (P1IN & BIT2) == BIT2)	// If bit is set?
			*RXByte |= 0x400;		// Set the value in the RXByte
			*RXByte = *RXByte >> 1;		// Shift the bits down
			*BitCnt --;
		}
	}
}
