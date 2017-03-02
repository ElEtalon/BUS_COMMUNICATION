//------------------------------------------------------------------------------
// io.h contains prototype of all managing functions for Inputs and Outputs
//------------------------------------------------------------------------------
#ifndef IO_HEADER
#define IO_HEADER

//------------------------------------------------------------------------------
// TXdata: 	  [UART function] shall be call for puTTY use. TXdata is for send
//			  character in the buffer (which is send to the UART port).
// IN:	  	  - 'c': character to send in the buffer (receive by puTTY).
// OUT:		  none.
// return:    none.
//------------------------------------------------------------------------------
void TXdata(unsigned char c);

//------------------------------------------------------------------------------
// RXdata: 	  [UART function] shall be call for puTTY use. RXdata is for receive
//			  character from the buffer (which was received to the UART port).
// IN:	  	  none.
// OUT:		  none.
// return:    'UCA0RXBUF': buffer which contains the character to receive.
//------------------------------------------------------------------------------
unsigned char RXdata();

//------------------------------------------------------------------------------
// TXSPI: 	  [SPI function] shall be call for send character from MASTER to SLAVE
// IN:	  	  - 'c': character to send in the buffer (receive by SLAVE).
// OUT:		  none.
// return:    none.
//------------------------------------------------------------------------------
void TXSPI(unsigned char c);

//------------------------------------------------------------------------------
// RXSPI: 	  [SPI function] shall be call for receive character from SLAVE
// IN:	  	  none.
// OUT:		  none.
// return:    'UCA0RXBUF': buffer which contains the character to receive.
//------------------------------------------------------------------------------
unsigned char RXSPI();

//------------------------------------------------------------------------------
// SendString: 	shall be call for send array of character to puTTY (and puTTY only)
// IN:	  	  	- 'size': size of the string to send.
//				- 'pstr': pointer on the string to send.
// OUT:		  	none.
// return:    	none.
//------------------------------------------------------------------------------
void SendString(int size, char * pstr);

#endif
