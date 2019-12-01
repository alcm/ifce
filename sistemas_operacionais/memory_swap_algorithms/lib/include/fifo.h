#ifndef FIFO_H_
#define FIFO_H_

#include "algorithm.h"

namespace swapping_algorithms {

class Fifo : public Algorithm {
   public:
    Fifo(int q, const std::vector<MemOperation> &data);

    void Run(ExecutionListener &listener) override;
};

}

#endif  // FIFO_H_
