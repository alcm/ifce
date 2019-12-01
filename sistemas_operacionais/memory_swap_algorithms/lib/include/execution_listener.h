#ifndef EXECUTION_LISTENER_H_
#define EXECUTION_LISTENER_H_

#include "types.h"

namespace swapping_algorithms {

class ExecutionListener {
   public:
    virtual void OnExecutionStart() = 0;
    virtual void OnExecutionFinish() = 0;
    virtual void OnAlgorithmStart(const AlgorithmId id, const uint32_t q) = 0;
    virtual void OnAlgorithmFinish(const AlgorithmId id, const uint32_t q,
                                   const uint32_t hit_count) = 0;
    virtual void OnProgress(const AlgorithmId id, const uint32_t q, const uint8_t progress) = 0;
};

}

#endif  // EXECUTION_LISTENER_H_
