#ifndef EVENT_HANDLER_
#define EVENT_HANDLER_

#include <QObject>

/**
 * @interface EventHandler.
 *
 * @brief Defines a generical interface for handle the API events.
 */
class IEventHandler : public QObject {
  Q_OBJECT
public:
  /**
   * @brief Destructor.
   */
  virtual ~IEventHandler() = default;
};

#endif  // EVENT_HANDLER_
