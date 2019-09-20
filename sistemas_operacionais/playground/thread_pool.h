#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <future>
#include <functional>
#include <vector>

class ThreadPool {
public:
    explicit ThreadPool(const uint8_t size)
    {
        futures_.reserve(size);
    }

    ~ThreadPool()
    {
        for (auto &entry : futures_)
            entry.get();
    }

    void EnqueueTask(const std::function<void()> &cb)
    {
        futures_.emplace_back(std::async(std::launch::async, cb));
    }

private:
    std::vector<std::future<void>> futures_;
};

#endif // THREAD_POOL_H_
