#include "semaphore.h"

Semaphore::Semaphore(const int count)
    : count_(count)
{

}

void Semaphore::Up()
{
    std::unique_lock<std::mutex> lock(mutex_);

    count_.store(count_ + 1);
    cv_.notify_all();
}

void Semaphore::Down()
{
    std::unique_lock<std::mutex> lock(mutex_);

    while (!count_.load())
        cv_.wait(lock);

    count_.store(count_ - 1);
}

int Semaphore::count() const
{
    return count_.load();
}
