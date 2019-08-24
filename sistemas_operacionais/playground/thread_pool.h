/**
 * \file
 * \brief  Thread pool class implementation.
 */
#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <future>
#include <functional>
#include <vector>

class ThreadPool
{
public:
    /**
     * \brief  Constructor
     * \param  size Size of pool.
     */
    explicit ThreadPool(const uint8_t size)
    {
        futures_.reserve(size);
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
    std::vector<std::future<void>> futures_;  //!< Futures.
};

#endif // THREAD_POOL_H_
