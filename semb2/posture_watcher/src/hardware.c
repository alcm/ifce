#include "adxl345.h"
#include "hardware.h"
#include "i2c.h"
#include "uart_logger.h"
  
void sys_config(void)
{
  DDRD = (1 << VIBRACALL_PIN); /* VIBRACALL_PIN as output */
  DDRD = (1 << LED_PIN);
  PORTD = 0x00;

  setup_uart_logger(9600);
  setup_adxl345();
}
