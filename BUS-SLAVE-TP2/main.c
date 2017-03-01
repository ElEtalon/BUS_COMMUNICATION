#include <msp430g2211.h>
#define CS BIT5         // Chip Select line
#define CD BIT7         // Command/Data mode line
#define MOSI BIT0       // Master-out Slave-in
#define SCK BIT6        // Serial clock

#if 20110706 > __MSPGCC__
/* A crude delay function. */
void __delay_cycles( unsigned long n ) {
    volatile unsigned int i = n/6;
    while( i-- ) ;
}
#endif

/* Write data to slave device.  Since the LCD panel is
 * write-only, we don't worry about reading any bits.
 * Destroys the data array (normally received data would
 * go in its place). */
void spi_IO( unsigned char data[], int bytes ) {
    int i, n;

    // Set Chip Select low, so LCD panel knows we are talking to it.
    P1OUT &= ~CS;
    __delay_cycles( 500 );

    for( n = 0; n < bytes; n++ ) {
        for( i = 0; i < 8; i++ ) {
            // Put bits on the line, most significant bit first.
            if( data[n] & 0x80 ) {
                P1OUT |= MOSI;
            } else {
                P1OUT &= ~MOSI;
            }
            data[n] <<= 1;

            // Pulse the clock low and wait to send the bit.  According to
            // the data sheet, data is transferred on the rising edge.
            P1OUT &= ~SCK;
            __delay_cycles( 500 );

            // Send the clock back high and wait to set the next bit.  Normally
            // we'd also read the data bits here, but the LCD is write-only.
            P1OUT |= SCK;
            __delay_cycles( 500 );
        }
    }

    // Set Chip Select back high to finish the communication.
    // For data, this also triggers the LCD to update/display.
    P1OUT |= CS;
}

/* Sets the LCD to command mode, and sends a 7-byte
 * sequence to initialize the panel. */
void init_lcd( void ) {
    unsigned char data[] = {
        0x40, // M=0(4-share-1/3 duty; FF=0)
        0x30, // Unsynchronized transfers
        0x18, // Blink off
        0x11, // Display on
        0x15, // Segment Decoder ON
        0x20, // Clear Data and pointer
        0x00  // Clear blink memory
    };

    P1OUT |= CD;        // set for commands

    spi_IO( data, sizeof(data));
}

/* Prints a string on the LCD panel using the 7 segment decoder.
 * Understood characters are 0x00 (zero) to 0x09 (nine) and
 * 0x0A to 0x0F (the symbols -, E, C, =, and space). */
void print_lcd( unsigned char data[], int n ) {
    unsigned char copy[12];
    unsigned char tmp;
    int i;

    if( n < 1 ) return;
    if( n > 12 ) n=12;

    // The panel expects data arranged right to left, so we'll
    // reverse the array of data passed before writing it out.
    for( i = n; i > 0; i-- ) {
        copy[n-i] = data[i-1];
    }

    P1OUT &= ~CD;       // set for data

    spi_IO( copy, n );
}

/* Draws a decimal point n places from the right, by turning on
 * the individual LCD segment (OR 0x8 mask with segment memory). */
void decimal_on( int n ) {
    unsigned char data[] = {
        0x14,           // Segment Decoder off
        0xE0+2*n,       // Set pointer 0 (plus 2 for each digit)
        0xB8,           // Decimal point on (OR 0x8 with memory contents)
        0x15            // Segment Decoder on
    };

    if( n < 0 || n > 11 ) return;

    P1OUT |= CD;        // set for commands

    spi_IO( data, sizeof(data));
}

void main( void ) {
    // Stop the watchdog timer so it doesn't reset our chip
    WDTCTL = WDTPW + WDTHOLD;

    // These are the pins we need to drive.
    P1DIR |= SCK + MOSI + CS + CD;

    // De-select the LCD panel and set the clock high
    P1OUT |= CS + SCK;

    // Pause so everything has time to start up properly.
    __delay_cycles( 15000 );

    // Initialize the LCD panel.
    init_lcd();

    // Print a message: 1234.5
    print_lcd("\1\2\3\4\5", 5 );
    decimal_on( 1 );

    for( ;; ) {
        __bis_SR_register( LPM3_bits + GIE );
    }
}
