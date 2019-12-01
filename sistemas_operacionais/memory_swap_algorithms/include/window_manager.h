#ifndef WINDOW_MANAGER_H_
#define WINDOW_MANAGER_H_

#include <QMainWindow>

namespace Ui {
class WindowManager;
}

/**
 * @class WindowManager.
 *
 * @brief Represents the main application screen and it's responsible for
 * manage the application screens.
 */
class WindowManager : public QMainWindow {
  Q_OBJECT
public:
  /**
   * @brief Constructor.
   * @param parent Parent window.
   */
  explicit WindowManager(QWidget *parent = 0);

  /**
   * @brief Destructor.
   */
  ~WindowManager();

  /**
   * @brief Set the current screen.
   * @param screen New screen.
   */
  void SetScreen(QWidget *screen);

private:
  Ui::WindowManager *ui_;
};

#endif  // WINDOW_MANAGER_H_
