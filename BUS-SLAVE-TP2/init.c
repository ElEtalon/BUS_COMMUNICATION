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
	P1OUT =  0x10;                        // P1.4 set, else reset
	P1REN |= 0x10;                        // P1.4 pullup
	P1DIR = 0x01;                         // P1.0 output, else input

	P1DIR |= 0x04;                        // Reset Slave
	P1DIR &= ~0x04;
}

void InitSPI(void){
    USICTL0 |= USIPE5 + USIPE6 + USIPE7 + USIMST + USIOE;  // 3-pin, 8-bit SPI master
    USICKCTL = USIDIV_2 + USISSEL_2;
    USICTL0 &= ~USISWRST;                 // USI released for operation
}
