#ifndef SECOND_CHANCE_H_
#define SECOND_CHANCE_H_

#include "algorithm.h"

#include <unordered_map>

namespace swapping_algorithms {

class SecondChance : public Algorithm {
   public:
    SecondChance(int q, int bit_r, const std::vector<MemOperation> &data);

    void Run(ExecutionListener &listener) override;

   private:
    int GetOldestPageWithBitRZero();

    std::unordered_map<int, int> pages_bit_r_;
    int bit_r_;
};

}

#endif  // SECOND_CHANCE_H_
