#include <stdio.h>
#include <string.h>

#include "adxl345.h"
#include "hardware.h"
#include "posture_watcher.h"
#include "uart_logger.h"

bool posture_is_correct(const float *angles)
{
    const float ideal_xyz[3] = {175.0, 88.0, 88.0}; // TODO: check these values...

    return !((fabsf(angles[0] - ideal_xyz[0]) >= 15.0) ||
             (fabsf(angles[1] - ideal_xyz[1]) >= 15.0) ||
             (fabsf(angles[2] - ideal_xyz[2]) >= 10.0));
}

void run_application(void)
{
    int16_t raw_data[3];
    float xyz_angles[3];

    while (1) {
        LED_OFF();
        _delay_ms(1000);
        LED_ON();

        memset(raw_data, 0, sizeof(raw_data));
        memset(xyz_angles, 0, sizeof(xyz_angles));

        read_from_adxl345(raw_data);
        get_xyz_angles(raw_data, xyz_angles);

#if (DEBUG == 1)
        char logger_msg[255];

        sprintf(logger_msg, "[LOG] (x/y/z): (%f/%f/%f) deg\n", xyz_angles[0], xyz_angles[1], xyz_angles[2]);
        uart_logger(logger_msg);
#endif

    if (!posture_is_correct(xyz_angles)) {
        uart_logger("[LOG] Incorrect posture detected...\n");
        VIBRACALL_ON();
    } else {
        VIBRACALL_OFF();
    }
  }
}

int main(void)
{
    sys_config();
    uart_logger("[LOG] Starting the application...\n");
    run_application();

    return 1; // normally never reached...
}
