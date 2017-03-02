//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------

#include <msp430g2231.h>
#include "io.h"

void Send_char_SPI(unsigned char carac)
{
	P1OUT &= ~BIT4;
	USISRL = carac;
	USICNT = 8;
	while ((USICTL1 & USIIFG) == 0);
	P1OUT |= BIT4;
}
