//------------------------------------------------------------------------------
// Name: 				Bus Master TP2
//
// Description: 		Shall allow SPI communication between MSP430G2553 (MASTER)
//						and MSP430G2231 (SLAVE).
//
// Authors:				Paul Bouquet / Paul Mocquillon
//
// Date of creation: 	02/03/2017
//
// Version: 			1.2
//------------------------------------------------------------------------------
#include <msp430g2553.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "io.h"
#include "init.h"

//------------------------------------------------------------------------------
// sendAlphabet: 	shall be call for send alphabet from MASTER to SLAVE.
//					After each send of character, wait for the response.
// IN:	  	  		none.
// OUT:		 		none.
// return:    		none.
//------------------------------------------------------------------------------
void sendAlphabet(void)
{
	char l;
	// For each alphabet char
	for(l = 'a'; l<='z'; ++l)
	{
		// Sending character
		sendCharSPI(l);
		//__delay_cycles(2000000);//tempwait 2sec
		// Receiving
		listeningSPI(); //todo: shall threat response. If not equivalent of sending character, shall failed.
	}
}

//------------------------------------------------------------------------------
// sendCharSPI: 	shall be call for send alphabet from MASTER to SLAVE.
//					After send character, wait for the response.
// IN:	  	  		- 'param_char': character to send.
// OUT:		 		none.
// return:    		none.
//------------------------------------------------------------------------------
void sendCharSPI(char param_char)
{
	char str[30];
	//Sending
	sprintf(str, "** SEND : %c ** %s", param_char, EOL_WINDOWS);
	SendString( strlen(str), str); 			//Send to puTTY the actual character.
	TXSPI((unsigned char)param_char);		//Send to SLAVE the actual character.
}

//------------------------------------------------------------------------------
// listeningSPI: 	shall be call when SLAVE is responding to MASTER
// IN:	  	  		none.
// OUT:		 		none.
// return:    		none.
//------------------------------------------------------------------------------
void listeningSPI()
{
	char str[30];
	unsigned char result;

	// get result
	result = RXSPI();									//receiving from SLAVE
	// show result
	if(result != NULL)
	{
		sprintf(str, "** RECEIVE : %c ** %s", result, EOL_WINDOWS);
		SendString(strlen(str), str);					//send to puTTY the received response
	}
	else
	{
		sprintf(str, "** RECEIVE : NULL ** %s", EOL_WINDOWS);
		SendString(strlen(str), str);
	}
}

//------------------------------------------------------------------------------
// showHelp: 	shall be call when user (puTTY) ask for help (h)
// IN:	  	  		none.
// OUT:		 		none.
// return:    		none.
//------------------------------------------------------------------------------
void showHelp(void)
{
	char str[100];
	sprintf(str, "a%sEnvoyer l'aphabet en SPI%s", TAB_WINDOWS, EOL_WINDOWS);
	SendString( strlen(str), str);
	sprintf(str, "h%sAfficher la liste des commandes%sh", TAB_WINDOWS, EOL_WINDOWS);
	SendString( strlen(str), str);
	sprintf(str, "l%sListen SPI%s", TAB_WINDOWS, EOL_WINDOWS);
	SendString( strlen(str), str);
}

//------------------------------------------------------------------------------
// main: 	call each init functions and wait for ever.
//------------------------------------------------------------------------------
void main(void)
{
	char str[1];
	WDTCTL = WDTPW + WDTHOLD;   			// Stop WDT
    BCSCTL1 = CALBC1_1MHZ;      			// Set DCO to 1Mhz
    DCOCTL = CALDCO_1MHZ;       			// Set DCO to 1Mhz
    P1DIR = BIT0;

    InitUART();
    InitSPI();

    sprintf(str, ">");
    SendString( strlen(str), str);

    __bis_SR_register(GIE); 				// interrupts enabled
    while(1);
}

//------------------------------------------------------------------------------
// USCI0RX_ISR: 	interruption when SPI buffer is updated
//------------------------------------------------------------------------------
// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	char str[200];
	unsigned char choice;

	choice = RXdata();

	switch((int)choice)
	{
		case (int)'a':
			// COMMAND
			sprintf(str, "SEND ALPHABET SPI%s", EOL_WINDOWS);
			SendString( strlen(str), str);
			P1OUT &= ~BIT6; //CS select
			sendAlphabet();
			P1OUT |= BIT6; //CS unselect
			break;
		case (int)'l':
				// COMMAND
				sprintf(str, "LISTENING%s", EOL_WINDOWS);
				SendString( strlen(str), str);
				P1OUT &= ~BIT6; //CS select
				listeningSPI();
				P1OUT |= BIT6; //CS unselect
				break;
		case (int)'h':
		default:
			// COMMAND
			sprintf(str, "HELP%s", EOL_WINDOWS);
			SendString( strlen(str), str);
			showHelp();
			break;
	}

	// current launchpad
	sprintf(str, "%s", LAUNCHPAD_ROLE);
	SendString( strlen(str), str);

	// Return pipe
    sprintf(str, ">");
    SendString( strlen(str), str);
}
