#include "semaphore.h"

Semaphore::Semaphore(const int count)
    : count_(count)
{

}

void Semaphore::Up()
{
    std::unique_lock<std::mutex> lock(mutex_);

    count_++;
    cv_.notify_one();
}

void Semaphore::Down()
{
    std::unique_lock<std::mutex> lock(mutex_);

    while (!count_)
        cv_.wait(lock);

    count_--;
}

int Semaphore::count() const
{
    return count_;
}
