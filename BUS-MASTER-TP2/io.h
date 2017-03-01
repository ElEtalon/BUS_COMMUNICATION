//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------
#ifndef IO_HEADER
#define IO_HEADER

void TXdata(unsigned char c);
void SendString(int size, char * str);
unsigned char RXdata();
unsigned char RXSPI();
void TXSPI(unsigned char c);

#endif
