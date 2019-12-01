#ifndef ALGORITHM_EXECUTION_SCREEN_H_
#define ALGORITHM_EXECUTION_SCREEN_H_

#include <condition_variable>
#include <memory>
#include <map>

#include "include/mediator.h"  // TODO(andre.carvalho) screen_component.h
#include "include/algorithm_execution_widget.h"
#include "lib/include/algorithm.h"
#include "lib/include/types.h"

namespace Ui {
class AlgorithmExecutionScreen;
}

/**
 * @class AlgorithmExecutionScreen.
 *
 * @brief Represents the Test screen. It's responsible for send the diagnostics
 * execution request to API.
 */
class AlgorithmExecutionScreen : public ScreenComponent {
  Q_OBJECT
public:
  /**
   * @brief Constructor.
   * @param iteration_counter Number of diagnostic iterations.
   * @param selected_tests Tests selected from user.
   * @param module Module associated.
   */
  AlgorithmExecutionScreen(int q1, int q2, int bit_r, const std::vector<swapping_algorithms::MemOperation> &data);

  /**
   * @brief Destructor.
   */
  ~AlgorithmExecutionScreen();

private slots:
    void OnExecutionStart();
    void OnExecutionFinish();
    void OnAlgorithmStart(const swapping_algorithms::AlgorithmId id, const uint32_t q);
    void OnAlgorithmFinish(const swapping_algorithms::AlgorithmId id, const uint32_t q, const uint32_t hit_count);
    void OnProgress(const swapping_algorithms::AlgorithmId id, const uint32_t q, const uint8_t progress);

protected:
  void showEvent(QShowEvent *e);

private:
  /**
   * @brief Draw on the main screen the Tests in execution for a given Device.
   */
  void DrawExecutionEntry(const swapping_algorithms::AlgorithmId &id,
                          const uint32_t q);

  AlgorithmExecutionWidget *GetAlgorithmWidget(const swapping_algorithms::AlgorithmId id, int q);

  /**
   * @brief Setup the screen signals/slots.
   */
  void ConnectSignals();

  std::vector<std::shared_ptr<swapping_algorithms::Algorithm>> algorithms_;
  std::map<std::pair<swapping_algorithms::AlgorithmId, int>, AlgorithmExecutionWidget *> widgets_;

  std::map<swapping_algorithms::AlgorithmId, std::string> algo_names_;
  std::map<int, std::vector<swapping_algorithms::AlgorithmResult>> results_;

  Ui::AlgorithmExecutionScreen *ui_;

  int global_progress_;
  int total_global_progress_;
};

#endif  // ALGORITHM_EXECUTION_SCREEN_H_
