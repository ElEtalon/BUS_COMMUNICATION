//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------
#ifndef IO_HEADER
#define IO_HEADER

#define		Bit_time	104
#define		Bit_time_5	0

void Receive(bool * isReceiving, bool * hasReceived, unsigned int * RXByte, unsigned int * TXByte, unsigned char * BitCnt);
void Transmit(bool * isReceiving, unsigned int * RXByte, unsigned int * TXByte, unsigned char * BitCnt);

#endif
