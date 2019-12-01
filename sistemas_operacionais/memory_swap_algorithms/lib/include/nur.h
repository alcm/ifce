#ifndef NUR_H_
#define NUR_H_

#include "algorithm.h"

namespace swapping_algorithms {

class Nur : public Algorithm {
public:
    Nur(int bit_r, int q, const std::vector<MemOperation> &data);

    void Run(ExecutionListener &listener) override;

private:
    int bit_r_;
};

}

#endif  // NUR_H_
