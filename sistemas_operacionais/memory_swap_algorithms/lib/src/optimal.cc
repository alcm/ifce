#include "optimal.h"

#include <iostream>

namespace swapping_algorithms {

Optimal::Optimal(int q, const std::vector<MemOperation> &data)
    : Algorithm(AlgorithmId::OPTIMAL, q, "Optimal", data)
{

}

void Optimal::Run(ExecutionListener &listener)
{
//    bool alloc = false;
//
//    listener.OnAlgorithmStart(id_, q_);
//
//    //std::cout << "SIZE: " << data_.size() << std::endl;
//    for (int i = 0; i < data_.size(); i++) {
//        listener.OnProgress(id_, q_, ((100 * i) / data_.size()));
//
//        auto it = std::find(memory_.begin(), memory_.end(), data_[i].page);
//
//        // if the page was found in memory.
//        if (it != memory_.end()) {
//            //std::cout << "ACERTO: " << data_[i].page << std::endl;
//            //std::cout << "HIT_COUNT: " << hit_count_ << std::endl;
//            hit_count_++;
//            queue_.emplace_back(data_[i].page);
//            continue;
//        } else {
//            for (int j = 0; j < memory_.capacity(); j++) {
//                if (memory_[j] == -1) {
//                    //std::cout << "PAGINA " << data_[i].page << " ALOCADA" << std::endl;
//                    memory_[j] = data_[i].page;
//                    queue_.emplace_back(data_[i].page);
//                    alloc = true;
//                    break;
//                }
//            }
//
//            if (alloc) {
//                alloc = false;
//                continue;
//            }
//
//            // if this part was reached, the memory is full, so we must to perform the swap.
//            int page_to_swap = GetPageToSwap(i);
//            //std::cout << "A PAGINA " << oldest_page << " VAI SAIR PRA ENTRAR " << data_[i].page << std::endl;
//            auto pos_it = std::find(memory_.begin(), memory_.end(), page_to_swap);
//            int idx = std::distance(memory_.begin(), pos_it);
//
//            memory_[idx] = data_[i].page;
//            queue_.erase(std::remove(queue_.begin(), queue_.end(), page_to_swap), queue_.end());
//            queue_.emplace_back(data_[i].page);
//        }
//    }
//
//    listener.OnProgress(id_, q_, 100);
//    listener.OnAlgorithmFinish(id_, q_, hit_count_);
}

int Optimal::GetPageToSwap(int curr_index) const
{
//    std::map<int, int> distances;
//    for (auto &entry : memory_) {
//        bool found = false;
//
//        for (int i = curr_index + 1; i < data_.size(); i++) {
//            auto cb = [entry] (const swapping_algorithms::MemOperation &op)
//                      {
//                          return entry == op.page;
//                      };
//
//            auto it = std::find_if(data_.begin(), data_.end(), cb);
//            if (it != data_.end()) {
//                found = true;
//                distances[entry] = std::distance(it, data_.end()) - 1;
//                break;
//            }
//        }
//
//        if (!found) {
//            std::cout << "NAO VAI MAIS USAR" << std::endl;
//            return entry;
//        }
//    }
//
//    int max_distance = 0;
//    int oldest_page = 0;
//    for (auto &entry : distances) {
//        if (entry.second > max_distance) {
//            max_distance = entry.second;
//            oldest_page = entry.first;
//        }
//    }
//
//    return oldest_page;
}

int Optimal::GetOldestPage() const
{
    std::map<int, int> distances;

    for (int i = 0; i < memory_.size(); i++) {
        int page = memory_[i];
        auto it = std::find_if(data_.begin() + i, data_.end(),
                [page] (const swapping_algorithms::MemOperation &data) { return page == data.page; });

        distances[page] = std::distance(it, data_.end()) - 1;
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
