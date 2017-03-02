//------------------------------------------------------------------------------
// init.h contains prototype of init functions.
//------------------------------------------------------------------------------
#ifndef INIT_HEADER
#define INIT_HEADER

//------------------------------------------------------------------------------
// InitUART : shall be call at the launch of the program. Initialize pin of the
//            microC.
// IN/OUT:	  none.
// return:    none.
//------------------------------------------------------------------------------
void InitUART(void);

//------------------------------------------------------------------------------
// InitSPI :  shall be call at the launch of the program. Initialize parameters
//			  for SPI communication.
// IN/OUT:	  none.
// return:    none.
//------------------------------------------------------------------------------
void InitSPI(void);

#endif

