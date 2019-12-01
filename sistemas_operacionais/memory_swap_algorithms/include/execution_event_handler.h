#ifndef EXECUTION_EVENT_HANDLER_H_
#define EXECUTION_EVENT_HANDLER_H_

#include <memory>

#include "lib/include/execution_listener.h"
#include "include/event_handler.h"

class ExecutionEventHandler : public IEventHandler,
                              public swapping_algorithms::ExecutionListener {
    Q_OBJECT
public:
    /**
     * @brief Constructor.
     */
    ExecutionEventHandler();

    /**
     * @brief Destructor.
     */
    ~ExecutionEventHandler() = default;

    void OnExecutionStart() override;
    void OnExecutionFinish() override;
    void OnAlgorithmStart(const swapping_algorithms::AlgorithmId id, const uint32_t q) override;
    void OnAlgorithmFinish(const swapping_algorithms::AlgorithmId id, const uint32_t q, const uint32_t hit_count) override;
    void OnProgress(const swapping_algorithms::AlgorithmId id, const uint32_t q, const uint8_t progress) override;

signals:
    void ExecutionStart();
    void ExecutionFinish();
    void AlgorithmStart(const swapping_algorithms::AlgorithmId id, const uint32_t q);
    void AlgorithmFinish(const swapping_algorithms::AlgorithmId id, const uint32_t q, const uint32_t hit_count);
    void Progress(const swapping_algorithms::AlgorithmId id, const uint32_t q, const uint8_t progress);
};

#endif  // EXECUTION_EVENT_HANDLER_H_
