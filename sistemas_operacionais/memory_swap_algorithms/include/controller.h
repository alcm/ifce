#ifndef LDIAG_VIEWS_SAMPLE_API_INCLUDE_CONTROLLER_H_
#define LDIAG_VIEWS_SAMPLE_API_INCLUDE_CONTROLLER_H_

#include <memory>

#include "include/mediator.h"
#include "include/window_manager.h"
#include "lib/include/runner.h"

/**
 * @class Controller.
 *
 * @brief Implements the mediator insterface.
 */
class Controller : public Mediator, public std::enable_shared_from_this<Mediator> {
public:
  /**
   * @brief Constructor.
   */
  Controller() = default;

  /**
   * @brief Destructor.
   */
  ~Controller() = default;

  /**
   * @brief @see Mediator::Init().
   */
  bool Init(ScreenComponent *screen) override;

  /**
   * @brief @see Mediator::HandleCommand(const ScreenComponent *, ICommand *).
   */
  void HandleCommand(const ScreenComponent *sender, ICommand *cmd) override;

private:  
    swapping_algorithms::Runner runner_; //!< API instance.
    WindowManager window_mgr_; //!< Window manager.
};

#endif  // LDIAG_VIEWS_SAMPLE_API_INCLUDE_CONTROLLER_H_
