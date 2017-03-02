//------------------------------------------------------------------------------
// io.c contains functions managing Inputs and Outputs of the microC
//------------------------------------------------------------------------------

#include <msp430g2553.h>
#include "io.h"

//------------------------------------------------------------------------------
// TXdata: 	  [UART function] shall be call for puTTY use. TXdata is for send
//			  character in the buffer (which is send to the UART port).
// IN:	  	  - 'c': character to send in the buffer (receive by puTTY).
// OUT:		  none.
// return:    none.
//------------------------------------------------------------------------------
void TXdata(unsigned char c)
{
    while (!(IFG2 & UCA0TXIFG));  				// USCI_A0 TX buffer ready? --wait flag
    UCA0TXBUF = c;              				// TX -> RXed character
}

//------------------------------------------------------------------------------
// RXdata: 	  [UART function] shall be call for puTTY use. RXdata is for receive
//			  character from the buffer (which was received to the UART port).
// IN:	  	  none.
// OUT:		  none.
// return:    'UCA0RXBUF': buffer which contains the character to receive.
//------------------------------------------------------------------------------
unsigned char RXdata()
{
	while(!(IFG2 & UCA0RXIFG)); 				//receptionUSCI_A0 ? --wait flag
	return UCA0RXBUF;
}

//------------------------------------------------------------------------------
// TXSPI: 	  [SPI function] shall be call for send character from MASTER to SLAVE
// IN:	  	  - 'c': character to send in the buffer (receive by SLAVE).
// OUT:		  none.
// return:    none.
//------------------------------------------------------------------------------
void TXSPI(unsigned char c)
{
	while (!(IFG2 & UCB0TXIFG));  				// USCI_A0 TX buffer ready? --wait flag
	UCB0TXBUF = c;              				// TX -> RXed character
}

//------------------------------------------------------------------------------
// RXSPI: 	  [SPI function] shall be call for receive character from SLAVE
// IN:	  	  none.
// OUT:		  none.
// return:    'UCA0RXBUF': buffer which contains the character to receive.
//------------------------------------------------------------------------------
unsigned char RXSPI()
{
	while(!(IFG2 & UCB0RXIFG)); 				//receptionUSCI_A0 ? --wait flag
	return UCB0RXBUF;
}

//------------------------------------------------------------------------------
// SendString: 	shall be call for send array of character to puTTY (and puTTY only)
// IN:	  	  	- 'size': size of the string to send.
//				- 'pstr': pointer on the string to send.
// OUT:		  	none.
// return:    	none.
//------------------------------------------------------------------------------
void SendString(int size, char * pstr)
{
	int i;

	for(i=0; i<size; i++)              			//For each element of the string.
	{
		TXdata((unsigned char)pstr[i]);			//Send the current character.
	}
}
