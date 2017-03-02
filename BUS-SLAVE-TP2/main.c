/******************************************************************************

 ******************************************************************************/

#include "msp430g2231.h"
#include "stdbool.h"
#include "main.h"
#include "init.h"
#include "io.h"

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;            // Stop watchdog

	InitPort();
	InitSPI();

	USICNT = 8;                           // init-load counter
	//_BIS_SR(LPM0_bits + GIE);             // Enter LPM0 w/ interrupt

	while(1){
		Send_char_SPI('Q');
	}
}

// USI interrupt service routine
#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)
{
  Send_char_SPI('a');
  /*USISRL = 0xAA;          //write data to send
  USICNT = 0x08;              //init the counter to shift data
  while(!(USICTL1&USIIFG));*/
}
