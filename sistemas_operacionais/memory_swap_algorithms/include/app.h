#ifndef APP_H_
#define APP_H_

#include <QApplication>

#include <memory>

#include "include/mediator.h"
#include "lib/include/types.h"

class App : public QApplication {
public:
  /**
   * @brief Contructor.
   * @param argc Arguments counter.
   * @param argv Arguments value.
   */
  App(int &argc, char **argv);

  /**
   * @brief Destructor.
   */
  ~App() = default;

  /**
   * @brief Run the application main loop.
   * @return 0 on success, otherwise a non-zero value must be returned.
   */
  int Run(int q1, int q2, int bit_r, const std::string &file_path);

private:
    std::vector<swapping_algorithms::MemOperation> ParseFile(const std::string &filepath);

    std::shared_ptr<Mediator> controller_; //!< Mediator instance.
};

#endif  // APP_H_
