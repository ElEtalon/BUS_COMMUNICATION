//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------
#include <msp430g2553.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "io.h"
#include "init.h"

void sendAlphabet(void){
	char l;

	// For each alphabet char
	for(l = 'a'; l<='z'; ++l) {

		// Envoi
		sendCharSPI(l);

		// RECEPTION
		listeningSPI();
	}
}

void sendCharSPI(char p_char){
	char str[30];

	// ENVOI
	sprintf(str, "** ENVOI : %c ** %s", p_char, EOL_WINDOWS);
	SendString( strlen(str), str);

	// EMISSION
	// transmit
	TXSPI((unsigned char)p_char);
}

void listeningSPI(){
	char str[30];
	unsigned char result;

	// get result
	result = RXSPI();

	// show result
	if(result != NULL){
		sprintf(str, "** RECU : %c ** %s", result, EOL_WINDOWS);
		SendString( strlen(str), str);
	}
}

void showHelp(void){
	char str[100];
	sprintf(str, "a%sEnvoyer l'aphabet en SPI%s", TAB_WINDOWS, EOL_WINDOWS);
	SendString( strlen(str), str);
	sprintf(str, "h%sAfficher la liste des commandes%sh", TAB_WINDOWS, EOL_WINDOWS);
	SendString( strlen(str), str);
	sprintf(str, "l%sListen SPI%s", TAB_WINDOWS, EOL_WINDOWS);
	SendString( strlen(str), str);
}

void main(void)
{
	char str[1];
	WDTCTL = WDTPW + WDTHOLD;   // Stop WDT
    BCSCTL1 = CALBC1_1MHZ;      // Set DCO to 1Mhz
    DCOCTL = CALDCO_1MHZ;       // Set DCO to 1Mhz
    P1DIR = BIT0;               //

    InitUART();
    InitSPI();

    //sprintf(str, "--- Bienvenue sur PMPB BUS DE COM --- %s", EOL_WINDOWS);
    //sprintf(str, "En attente d'une commande... %s", EOL_WINDOWS, EOL_WINDOWS);
    sprintf(str, ">");
    SendString( strlen(str), str);

    __bis_SR_register(GIE); // interrupts enabled

    while(1);
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	char str[200];
	unsigned char choice;

	choice = UCA0RXBUF;

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

