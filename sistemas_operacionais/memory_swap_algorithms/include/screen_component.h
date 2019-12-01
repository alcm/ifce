//#ifndef LDIAG_VIEWS_SAMPLE_API_INCLUDE_MEDIATOR_H_
//#define LDIAG_VIEWS_SAMPLE_API_INCLUDE_MEDIATOR_H_

//#include <QWidget>

//#include <memory>

//#include "views/sample_api/include/command.h"
//#include "views/sample_api/include/event_handler.h"

//namespace sample_api {

//class Mediator;

///**
// * @brief Object to be mediated
// */
//class ScreenComponent : public QWidget {
//public:
//  /**
//   * \brief Constructor
//   */
//  explicit ScreenComponent(std::shared_ptr<IEventHandler> event_handler);

//  /**
//   * @brief Destructor
//   */
//  virtual ~ScreenComponent() = default;

//  /**
//   * @brief Send command to mediator
//   * @param cmd Command
//   */
//  void SendCommand(ICommand& cmd) const;

//  /**
//   * @brief Set mediator
//   * @param mediator Mediator
//   */
//  void set_mediator(std::shared_ptr<Mediator> mediator);

//  /**
//   * @brief event_handler
//   * @return
//   */
//  std::shared_ptr<IEventHandler> event_handler() const;

//protected:
//  std::shared_ptr<IEventHandler> event_handler_; //!<

//private:
//  std::weak_ptr<Mediator> mediator_;  //!< Mediator is responsible to manage commands from/to this component
//};

//}  // namespace sample_api

//#endif  // LDIAG_VIEWS_SAMPLE_API_INCLUDE_MEDIATOR_H_
