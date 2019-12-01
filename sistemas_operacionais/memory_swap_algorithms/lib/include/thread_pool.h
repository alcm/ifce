/**
 * \file
 * \brief  Thread pool class implementation.
 */
#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <future>
#include <functional>
#include <vector>

namespace swapping_algorithms {

class ThreadPool {
public:
    /**
     * \brief  Constructor
     */
    ThreadPool() : pool_size_(std::thread::hardware_concurrency())
    {
    }

    /**
     * \brief  Destructor.
     */
    ~ThreadPool()
    {
        for (auto &entry : futures_)
            entry.get();
    }

    /**
     * \brief  Add a new task to pool.
     * \param  cb The task to be executed.
     */
    void EnqueueTask(const std::function<void()> &cb)
    {
        futures_.emplace_back(std::async(std::launch::async, cb));
    }

private:
    uint8_t pool_size_;
    std::vector<std::future<void>> futures_;  //!< Futures.
};

}

#endif // THREAD_POOL_H_
