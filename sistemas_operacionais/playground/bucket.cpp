#include "bucket.h"

Bucket::Bucket(const uint8_t bucket_capacity)
    : QGraphicsPixmapItem(QPixmap(":/images/images/empty_bucket.png")),
      available_positions_sem_(bucket_capacity),
      available_balls_sem_(0),
      stop_(false),
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
    setToolTip(QString::fromStdString("O cesto contém: " + std::to_string(available_balls_sem_.available()) + " bola(s)"));
}

void Bucket::Push()
{
    available_positions_sem_.acquire();

    if (!stop_) {
        setToolTip(QString::fromStdString("O cesto contém: " + std::to_string(available_balls_sem_.available() + 1) + " bola(s)"));
        emit Repaint(imgs_.at(available_balls_sem_.available() + 1));
    }

    available_balls_sem_.release();
}

void Bucket::Pull()
{
    available_balls_sem_.acquire();

    if (!stop_) {
        setToolTip(QString::fromStdString("O cesto contém: " + std::to_string(available_balls_sem_.available()) + " bola(s)"));
        emit Repaint(imgs_.at(available_balls_sem_.available()));
    }

    available_positions_sem_.release();
}

void Bucket::Destroy()
{
    stop_ = true;
    available_balls_sem_.release(5);
    available_positions_sem_.release(5);
}
