//------------------------------------------------------------------------------
// init.c contains all functions call in the begin of the process.
//------------------------------------------------------------------------------
#include <msp430g2553.h>
#include "init.h"

//------------------------------------------------------------------------------
// InitUART : shall be call at the launch of the program. Initialize pin of the
//            microC.
// IN/OUT:	  none.
// return:    none.
//------------------------------------------------------------------------------
void InitUART(void)
{
	P1DIR |= BIT6;								// Led en sortie
	//P1OUT |= BIT6;
    P1SEL |= (BIT1 + BIT2);                 	// P1.1 = RXD, P1.2=TXD
    P1SEL2 |= (BIT1 + BIT2);                	// P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2;                   	// SMCLK
    UCA0BR0 = 104;                          	// 1MHz, 9600
    UCA0BR1 = 0;                            	// 1MHz, 9600
    UCA0CTL0 &= ~UCPEN & ~UCPAR & ~UCMSB;
    UCA0CTL0 &= ~UC7BIT & ~UCSPB & ~UCMODE1;
    UCA0CTL0 &= ~UCMODE0 & ~UCSYNC;
    UCA0CTL1 &= ~UCSWRST;                   	// **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                        	// Enable USCI_A0 RX interrupt
}

//------------------------------------------------------------------------------
// InitSPI :  shall be call at the launch of the program. Initialize parameters
//			  for SPI communication.
// IN/OUT:	  none.
// return:    none.
//------------------------------------------------------------------------------
void InitSPI(void)
{
	P1DIR |= BIT4;
	P1OUT |= BIT4;
	P1SEL |= (BIT5 + BIT6 + BIT7);                 // P1.1 = RXD, P1.2=TXD
	P1SEL2 |= (BIT5 + BIT6 + BIT7);                // P1.1 = RXD, P1.2=TXD

	UCB0CTL1 |= UCSSEL_2;
	UCB0BR0 = 104;                          // 1MHz, 9600
	UCB0BR1 = 0;                            // 1MHz, 9600

	UCB0CTL0 = 0 | (UCMSB | UCMST);
	UCB0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
}
