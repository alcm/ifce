#include "child.h"

#include <chrono>
#include <thread>

Child::Child(const int id, const std::string &name, const int play_time, const int quiet_time,
             const bool has_ball, const std::vector<QPoint> &path_to_bucket,
             Bucket *b)
    : must_stop_(false), id_(id), name_(name), play_time_(play_time), quiet_time_(quiet_time),
      has_ball_(has_ball), path_to_bucket_(path_to_bucket), bucket_(b),
      images_({":/images/images/kid_0.png", ":/images/images/kid_1.png",
               ":/images/images/kid_2.png", ":/images/images/kid_3.png",
               ":/images/images/kid_4.png", ":/images/images/kid_4.png",
               ":/images/images/kid_5.png", ":/images/images/kid_6.png",
               ":/images/images/kid_7.png"})
{
    setToolTip(QString::fromStdString("name: " + name + ", Tq: " + std::to_string(quiet_time_)
                                      + ", Tb: " + std::to_string(play_time_)));
}

void Child::MainThread()
{
    emit Repaint(id_, has_ball_ ? images_.at(2) : images_.at(0));

    while (!must_stop_) {
        StayQuiet();

        if (!has_ball_)
            PickBall();

        Play();
        ReturnBall();
    }
}

const Logger *Child::log_handler() const
{
    return &log_handler_;
}

int Child::id() const
{
   return id_;
}

void Child::Play()
{
    std::chrono::time_point<std::chrono::steady_clock> start, now;

    log_handler_.Log("A criança " + name_ + " está brincando.");

    start = std::chrono::steady_clock::now();
    // 'play_time_ - 1' due the sleeps inside loop.
    while (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() <= (play_time_ - 1)
           && !must_stop_) {
        for (int i = 1; i < images_.size(); i++) {
            emit Repaint(id_, images_.at(i));
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        now = std::chrono::steady_clock::now();
    }

    log_handler_.Log("A criança " + name_ + " parou de brincar.");
}

void Child::StayQuiet()
{
    std::chrono::time_point<std::chrono::steady_clock> start, now;

    log_handler_.Log("A criança " + name_ + " está quieta.");

    start = std::chrono::steady_clock::now();
    while ((std::chrono::duration_cast<std::chrono::seconds>(now - start).count() < quiet_time_)
           && !must_stop_)
        now = std::chrono::steady_clock::now();
}

void Child::PickBall()
{
    log_handler_.Log("A criança " + name_ + " foi pegar a bola.");

    emit Repaint(id_, images_.front());
    for (int i = 1 ; i < path_to_bucket_.size(); i++) {
        emit SetPosition(id_, path_to_bucket_.at(i));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    bucket_->Pull();
    has_ball_ = true;

    log_handler_.Log("A criança " + name_ + " pegou a bola.");

    emit Repaint(id_, images_.at(2));
    for (int i = path_to_bucket_.size() - 1; i >= 0; i--) {
        emit SetPosition(id_, path_to_bucket_.at(i));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Child::ReturnBall()
{
    log_handler_.Log("A criança " + name_ + " está indo devolver a bola.");

    emit Repaint(id_, images_.at(2));
    for (int i = 1 ; i < path_to_bucket_.size(); i++) {
        emit SetPosition(id_, path_to_bucket_.at(i));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    bucket_->Push();
    has_ball_ = false;

    log_handler_.Log("A criança " + name_ + " devolveu a bola.");

    emit Repaint(id_, images_.front());
    for (int i = path_to_bucket_.size() - 1; i >= 0; i--) {
        emit SetPosition(id_, path_to_bucket_.at(i));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Child::set_must_stop(bool must_stop)
{
    must_stop_ = must_stop;
}
