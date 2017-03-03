#include "msp430g2231.h"
#include "main.h"
#include "init.h"

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  unsigned char receive;

  InitPort();
  InitSPI();

  __bis_SR_register(GIE);   // Enter LPM0 w/ interrupt

  while(1){
	  while((USICTL1 & USIIFG) != BIT0); // Scrutation
	  receive = USISRL;
	  switch(receive){
	  case 'z':
		  P1OUT |= BIT1;
		  break;
	  case 'a':
		  P1OUT &= ~BIT1;
		  break;
	  default:break;
	  }
  }
}


#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)
{

}
