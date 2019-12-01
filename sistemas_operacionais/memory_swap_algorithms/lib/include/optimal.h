#ifndef OPTIMAL_H_
#define OPTIMAL_H_

#include "algorithm.h"

namespace swapping_algorithms {

class Optimal : public Algorithm {
public:
    Optimal(int q, const std::vector<MemOperation> &data);

    void Run(ExecutionListener &listener) override;

private:
    int GetPageToSwap(int curr_index) const;
    int GetOldestPage() const;
};

};

#endif  // OPTIMAL_H_
