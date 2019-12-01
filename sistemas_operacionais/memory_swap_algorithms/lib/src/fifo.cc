#include "fifo.h"

#include <algorithm>

namespace swapping_algorithms {

Fifo::Fifo(int q, const std::vector<MemOperation> &data)
    : Algorithm(AlgorithmId::FIFO, q, "Fifo", data)
{
}

void Fifo::Run(ExecutionListener &listener)
{
    bool alloc = false;

    listener.OnAlgorithmStart(id_, q_);

    for (int i = 0; i < data_.size(); i++) {
        listener.OnProgress(id_, q_, ((100 * i) / data_.size()));

        auto it = std::find(memory_.begin(), memory_.end(), data_[i].page);

        // if the page was found in memory.
        if (it != memory_.end()) {
            hit_count_++;
            queue_.emplace_back(data_[i].page);
            continue;
        } else {
            for (int j = 0; j < memory_.capacity(); j++) {
                if (memory_[j] == -1) {
                    memory_[j] = data_[i].page;
                    queue_.emplace_back(data_[i].page);
                    alloc = true;
                    break;
                }
            }

            if (alloc) {
                alloc = false;
                continue;
            }

            // if this part was reached, the memory is full, so we must to perform the swap.
            int item_to_delete = queue_[0];
            auto pos_it = std::find(memory_.begin(), memory_.end(), item_to_delete);
            int idx = std::distance(memory_.begin(), pos_it);

            memory_[idx] = data_[i].page;
            queue_.erase(std::remove(queue_.begin(), queue_.end(), item_to_delete), queue_.end());
            queue_.emplace_back(data_[i].page);
        }
    }

    listener.OnProgress(id_, q_, 100);
    listener.OnAlgorithmFinish(id_, q_, hit_count_);
}

}
