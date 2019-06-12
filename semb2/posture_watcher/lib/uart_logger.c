#include <avr/io.h>
#include <string.h>
#include <stdarg.h>

#include "uart_logger.h"

void setup_uart_logger(const uint16_t baudrate)
{
  // set baud rate   
  unsigned int baud = (((F_CPU / (baudrate * 16UL))) - 1);
    
  UBRR1H = (unsigned char)(baud >> 8 );
  UBRR1L = (unsigned char)baud;
    
  // enable received and transmitter
  UCSR1B = (1 << RXEN1) | (1 << TXEN1);
    
  // set frame format ( 8data, 2stop )
  UCSR1C = (1 << USBS1 ) | (3 << UCSZ10);
}

// write a string to the uart
void uart_logger(const char data[])
{
  int i = 0;
 
  for (; i < strlen(data); i++) {
    // wait for empty transmit buffer
    while (!(UCSR1A & ( 1 << UDRE1)));
    
    // put data into buffer, sends data
    UDR1 = data[i];
  }
}
