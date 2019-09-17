#include "bucket.h"

Bucket::Bucket(const uint8_t bucket_capacity)
    : n_balls_(0), capacity_(bucket_capacity),
      imgs_({ {0, ":/images/images/empty_bucket.png" },
              {1, ":/images/images/bucket_one_ball.png" },
              {2, ":/images/images/bucket_two_ball.png" },
              {3, ":/images/images/bucket_three_ball.png" },
              {4, ":/images/images/bucket_four_ball.png" },
              {5, ":/images/images/bucket_five_ball.png" },
              {6, ":/images/images/bucket_six_ball.png" },
              {7, ":/images/images/bucket_seven_ball.png" }})
{
    qRegisterMetaType<std::string>("std::string");
}

void Bucket::Push()
{
    n_balls_++;
    // TODO: decrease full semaphore
    emit Repaint(imgs_.at(n_balls_));
}

void Bucket::Pull()
{
    n_balls_--;
    // TODO: decrease empty semaphore
    emit Repaint(imgs_.at(n_balls_));
}
