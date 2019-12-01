#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <algorithm>
#include <vector>

#include "execution_listener.h"
#include "types.h"

namespace swapping_algorithms {

class Algorithm {
public:
    Algorithm(AlgorithmId id, int q, const std::string &name, const std::vector<MemOperation> &data)
        : id_(id), q_(q), name_(name), data_(data), hit_count_(0)
    {
        memory_.reserve(q);
        for (int i = 0; i < memory_.capacity(); i++)
            memory_.emplace_back(-1);
    }

    virtual void Run(ExecutionListener &listener) = 0;

    AlgorithmId id() const
    {
        return id_;
    }

    int q() const
    {
        return q_;
    }

    std::string name() const
    {
        return name_;
    }

protected:
    AlgorithmId id_;
    int hit_count_;
    int q_;
    std::string name_;
    std::vector<MemOperation> data_;
    std::vector<int> memory_;
    std::vector<int> queue_;
};

}

#endif // ALGORITHM_H_
