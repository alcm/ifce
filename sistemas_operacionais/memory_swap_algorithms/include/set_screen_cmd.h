#ifndef SET_SCREEN_CMD_H_
#define SET_SCREEN_CMD_H_

#include "include/command.h"
#include "include/mediator.h"

/**
 * @class SetScreenCmd.
 *
 * @brief Represents a Set screen command.
 */
class SetScreenCmd : public ICommand {
public:
  /**
   * @brief Constructor.
   * @param screen
   */
  explicit SetScreenCmd(ScreenComponent *screen)
    : ICommand{}, screen_{screen} {
  }

  /**
   * @brief screen
   * @return
   */
  ScreenComponent *screen() const {
    return screen_;
  }

private:
  ScreenComponent *screen_;
};

#endif  // SET_SCREEN_CMD_H_
