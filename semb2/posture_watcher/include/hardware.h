/**
 * @brief This file contains all implementations related to hardware peripherals configuration.
 */
#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <avr/io.h>

#ifndef F_CPU
  #define F_CPU               16000000UL /* 16 MHz */
#endif

#include <util/delay.h>

#define VIBRACALL_PIN         PD7
#define VIBRACALL_OFF()       (PORTD &= ~(1 << VIBRACALL_PIN))
#define VIBRACALL_ON()        (PORTD |= (1 << VIBRACALL_PIN))

#define LED_PIN               PD5
#define LED_OFF()             (PORTD &= ~(1 << LED_PIN))
#define LED_ON()              (PORTD |= (1 << LED_PIN))

/**
 * @brief configures all hardware peripherals.
 */
void sys_config(void);

#endif // HARDWARE_H_
