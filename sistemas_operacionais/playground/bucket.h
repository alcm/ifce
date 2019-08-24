#ifndef BUCKET_H_
#define BUCKET_H_

#include <cstdint>
#include <mutex>

class Bucket
{
public:
    explicit Bucket(const uint8_t bucket_capacity);

    void Push();
    void Pull();

private:
   std::mutex mutex_;
   uint8_t n_balls_;
   uint8_t capacity_;
};

#endif // BUCKET_H_
