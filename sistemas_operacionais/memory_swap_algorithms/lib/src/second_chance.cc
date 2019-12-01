#include "second_chance.h"

namespace swapping_algorithms {

SecondChance::SecondChance(int q, int bit_r, const std::vector<MemOperation> &data)
    : Algorithm(AlgorithmId::SECOND_CHANCE, q, "Second chance", data), bit_r_(bit_r)
{
    for (int i = 0; i < q; i++)
        pages_bit_r_[i] = 0;
}

void SecondChance::Run(ExecutionListener &listener)
{
    bool alloc = false;
    int zero_counter = 1;

    listener.OnAlgorithmStart(id_, q_);

    for (int i = 0; i < data_.size(); i++) {
        listener.OnProgress(id_, q_, ((100 * i) / data_.size()));

        if (i == (zero_counter * bit_r_)) {
            zero_counter++;
            for (int k = 0; k < pages_bit_r_.size(); k++)
                pages_bit_r_[k] = 0;
        }

        auto it = std::find(memory_.begin(), memory_.end(), data_[i].page);

        // if the page was found in memory.
        if (it != memory_.end()) {
            hit_count_++;
            queue_.emplace_back(data_[i].page);
            pages_bit_r_[data_[i].page] = 1;
            continue;
        } else {
            for (int j = 0; j < memory_.capacity(); j++) {
                if (memory_[j] == -1) {
                    memory_[j] = data_[i].page;
                    queue_.emplace_back(data_[i].page);
                    pages_bit_r_[data_[i].page] = 1;
                    alloc = true;
                    break;
                }
            }

            if (alloc) {
                alloc = false;
                continue;
            }

            // if this part was reached, the memory is full, so we must to perform the swap.
            int item_to_delete = GetOldestPageWithBitRZero();
            auto pos_it = std::find(memory_.begin(), memory_.end(), item_to_delete);
            int idx = std::distance(memory_.begin(), pos_it);

            memory_[idx] = data_[i].page;
        }
    }

    listener.OnProgress(id_, q_, 100);
    listener.OnAlgorithmFinish(id_, q_, hit_count_);
}

int SecondChance::GetOldestPageWithBitRZero()
{
    auto queue = queue_;
    int found = 0;

    for (int i = 0; i < queue_.size(); i++) {
        int page = queue_[i];

        if (pages_bit_r_.at(page)) {
            queue.erase(std::remove(queue.begin(), queue.end(), page), queue.end());
            pages_bit_r_.at(page) = 0;
            queue.emplace_back(page);
            continue;
        } else {
            queue.erase(std::remove(queue.begin(), queue.end(), page), queue.end());
            pages_bit_r_.at(page) = 0;
            found = page;
            break;
        }
    }

    queue_ = queue;

    return found;
}

}
