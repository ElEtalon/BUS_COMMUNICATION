//------------------------------------------------------------------------------
// main.h contains prototype of main functions.
//------------------------------------------------------------------------------
#ifndef MAIN_HEADER
#define MAIN_HEADER

//------------------------------------------------------------------------------
// list of indentation for puTTY
//------------------------------------------------------------------------------
const char * EOL_WINDOWS = "\r\n";
const char * TAB_WINDOWS = "\t";
const char * LAUNCHPAD_ROLE = "master";

//------------------------------------------------------------------------------
// sendAlphabet: 	shall be call for send alphabet from MASTER to SLAVE.
//					After each send of character, wait for the response.
// IN:	  	  		none.
// OUT:		 		none.
// return:    		none.
//------------------------------------------------------------------------------
void sendAlphabet(void);

//------------------------------------------------------------------------------
// showHelp: 	shall be call when user (puTTY) ask for help (h)
// IN:	  	  		none.
// OUT:		 		none.
// return:    		none.
//------------------------------------------------------------------------------
void showHelp(void);

//------------------------------------------------------------------------------
// listeningSPI: 	shall be call when SLAVE is responding to MASTER
// IN:	  	  		none.
// OUT:		 		none.
// return:    		none.
//------------------------------------------------------------------------------
void listeningSPI();

//------------------------------------------------------------------------------
// sendCharSPI: 	shall be call for send alphabet from MASTER to SLAVE.
//					After send character, wait for the response.
// IN:	  	  		- 'param_char': character to send.
// OUT:		 		none.
// return:    		none.
//------------------------------------------------------------------------------
void sendCharSPI(char param_char);

#endif
