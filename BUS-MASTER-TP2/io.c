//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------

#include <msp430g2553.h>
#include "io.h"

void TXdata( unsigned char c )
{
    while (!(IFG2 & UCA0TXIFG));  // USCI_A0 TX buffer ready?

    UCA0TXBUF = c;              // TX -> RXed character
}

unsigned char RXdata()
{
	while(!(IFG2 & UCA0RXIFG)); //receptionUSCI_A0 ?

	return UCA0RXBUF;
}

unsigned char RXSPI(){
	while(!(IFG2 & UCB0RXIFG)); //receptionUSCI_A0 ?

	return UCB0RXBUF;
}

void TXSPI( unsigned char c ){
	while (!(IFG2 & UCB0TXIFG));  // USCI_A0 TX buffer ready?

	UCB0TXBUF = c;              // TX -> RXed character
}

void SendString(int size, char * str)
{
	int i;

	for(i=0; i<size; i++)              // TX -> RXed character
	{
		TXdata((unsigned char)str[i]);
	}
}
