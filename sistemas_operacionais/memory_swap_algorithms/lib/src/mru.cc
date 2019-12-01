#include "mru.h"

#include <map>

namespace swapping_algorithms {

Mru::Mru(int q, const std::vector<MemOperation> &data)
    : Algorithm(AlgorithmId::MRU, q, "Mru", data)
{

}

void Mru::Run(ExecutionListener &listener)
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
            int oldest_page = GetOldestPage();
            auto pos_it = std::find(memory_.begin(), memory_.end(), oldest_page);
            int idx = std::distance(memory_.begin(), pos_it);

            memory_[idx] = data_[i].page;
            queue_.erase(std::remove(queue_.begin(), queue_.end(), oldest_page), queue_.end());
            queue_.emplace_back(data_[i].page);
        }
    }

    listener.OnProgress(id_, q_, 100);
    listener.OnAlgorithmFinish(id_, q_, hit_count_);
}

int Mru::GetOldestPage() const
{
    std::map<int, int> distances;

    for (int i = 0; i < queue_.size(); i++) {
        int page = queue_[i];
        auto it = std::find(queue_.begin() + i, queue_.end(), page);

        distances[page] = std::distance(it, queue_.end()) - 1;
    }

    int max_distance = 0;
    int oldest_page = 0;
    for (auto &entry : distances) {
        if (entry.second > max_distance) {
            max_distance = entry.second;
            oldest_page = entry.first;
        }
    }

    return oldest_page;
}

}
