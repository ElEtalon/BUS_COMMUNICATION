//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------
#ifndef MAIN_HEADER
#define MAIN_HEADER

const char * EOL_WINDOWS = "\r\n";
const char * TAB_WINDOWS = "\t";
const char * LAUNCHPAD_ROLE = "slave";

bool * isReceiving;		// Status for when the device is receiving
bool * hasReceived;		// Lets the program know when a byte is received

unsigned char * BitCnt;	// Bit count, used when transmitting byte
unsigned int * TXByte;	// Value sent over UART when Transmit() is called
unsigned int * RXByte;	// Value recieved once hasRecieved is set

void sendAlphabet(void);
void showHelp(void);
void listeningSPI();
void sendCharSPI(char p_char);

#endif
