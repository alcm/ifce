#ifndef MRU_H_
#define MRU_H_

#include "algorithm.h"

namespace swapping_algorithms {

class Mru : public Algorithm {
public:
    Mru(int q, const std::vector<MemOperation> &data);

    void Run(ExecutionListener &listener) override;

private:
    int GetOldestPage() const;
};

}

#endif  // MRU_H_
