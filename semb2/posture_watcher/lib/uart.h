#ifndef UART_H_
#define UART_H_

#define F_CPU           16000000UL

#include <stdint.h>

/**
 * @brief configures the uart communication.
 *
 * @param baudrate baudrate value.
 */
void setup_uart(const uint16_t baudrate);

/**
 * @brief send a message to uart interface.
 *
 * @param data - message
 */
void send_uart(const char data[]);

#endif // UART_H_
