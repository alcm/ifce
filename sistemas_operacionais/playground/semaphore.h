#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    explicit Semaphore(const int count = 0);

    void Up();
    void Down();

    int count() const;

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    int count_;
};

#endif // SEMAPHORE_H_
