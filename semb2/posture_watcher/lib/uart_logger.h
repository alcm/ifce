#ifndef UART_LOGGER_H_
#define UART_LOGGER_H_

#define F_CPU           16000000UL

#include <stdint.h>

/**
 * \brief configures the uart communication.
 * \param baudrate - baudrate value.
 */
void setup_uart_logger(const uint16_t baudrate);

/**
 * \brief send a message to uart interface.
 * \param data - message
 */
void uart_logger(const char data[]);

#endif // UART_LOGGER_H_
