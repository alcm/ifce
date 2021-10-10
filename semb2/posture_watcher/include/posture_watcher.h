/**
 * @brief This file contains all implementations related to posture watcher.
 */
#ifndef POSTURE_WATCHER_H_
#define POSTURE_WATCHER_H_

#include <stdbool.h>

/**
 * @brief Checks if the given measures corresponds to a "correct posture", according
 * with a pre-defined range of posture values.
 *
 * @param  angles array containing x, y and z angles calculated.
 *
 * @return true if correct otherwise returns false.
 */
bool posture_is_correct(const float * angles);

/**
 * @brief run the application main loop.
 */
void run_application(void);

#endif // POSTURE_WATCHER_H_
