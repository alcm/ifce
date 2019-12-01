#ifndef MEDIATOR_H_
#define MEDIATOR_H_

#include <QWidget>

#include <memory>

#include "include/command.h"
#include "include/event_handler.h"

class ScreenComponent;
class ICommand;

/**
 * @class Mediator.
 *
 * @brief Mediates the interaction between the screen components with the API
 * and the Window Manager.
 */
class Mediator {
public:
  /**
   * @brief Constructor
   */
  Mediator() = default;

  /**
   * @brief Destructor
   */
  virtual ~Mediator() = default;

  /**
   * @brief Initialize the mediator.
   */
  virtual bool Init(ScreenComponent *screen) = 0;

  /**
   * @brief Handle a received command.
   * @param sender Command sender component.
   * @param cmd Command received.
   */
  virtual void HandleCommand(const ScreenComponent *sender, ICommand *cmd) = 0;
};

/**
 * @class ScreenComponent.
 *
 * @brief Represents an object mediated by mediator.
 */
class ScreenComponent : public QWidget {
public:
  /**
   * @brief Constructor.
   * @param event_handler Screen component event handler.
   */
  explicit ScreenComponent(std::shared_ptr<IEventHandler> event_handler)
    : QWidget{}, event_handler_{event_handler} {
  }

  /**
   * @brief Destructor.
   */
  virtual ~ScreenComponent() = default;

  /**
   * @brief Sends a command to mediator.
   * @param cmd Command.
   */
  void SendCommand(ICommand& cmd) const {
    if (std::shared_ptr<Mediator> m = mediator_.lock()) {
      m->HandleCommand(this, &cmd);
    }
  }

  /**
   * @brief Sets the mediator.
   * @param mediator Mediator.
   */
  void set_mediator(std::shared_ptr<Mediator> mediator) {
    mediator_ = mediator;
  }

  /**
   * @brief Gets the screen component event handler.
   * @return The event handler.
   */
  std::shared_ptr<IEventHandler> event_handler() const {
    return event_handler_;
  }

private:
  std::weak_ptr<Mediator> mediator_; //!< Mediator.

protected:
  std::shared_ptr<IEventHandler> event_handler_; //!< Screen component event handler.
};

#endif  // MEDIATOR_H_
