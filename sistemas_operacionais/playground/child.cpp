#include "child.h"

#include <chrono>
#include <thread>

Child::Child(const int id, const int play_time, const int quiet_time,
             const bool has_ball, const std::vector<QPoint> &path_to_bucket,
             std::shared_ptr<Bucket> b)
    : id_(id), play_time_(play_time), quiet_time_(quiet_time), has_ball_(has_ball),
      status_(has_ball ? "playing" : "quiet"), path_to_bucket_(path_to_bucket), bucket_(b)
{

}

void Child::MainThread()
{
    emit DrawChild(id_, path_to_bucket_.front());

    while (1) {
        if (!has_ball_)
            PickBall();

        Play();
        ReturnBall();
        StayQuiet();
    }
}

const Logger *Child::log_handler() const
{
    return &log_handler_;
}

void Child::Play()
{
    std::chrono::time_point<std::chrono::steady_clock> start, now;

    log_handler_.Log("A criança " + std::to_string(id_) + " está brincando.");

    start = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() <= play_time_) {
        // TODO: refresh the GUI with the child playing with the ball.
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // TODO: refresh the GUI with the child playing with the ball.

        now = std::chrono::steady_clock::now();
    }

    log_handler_.Log("A criança " + std::to_string(id_) + " parou de brincar.");
}

void Child::StayQuiet()
{
    std::chrono::time_point<std::chrono::steady_clock> start, now;

    log_handler_.Log("A criança " + std::to_string(id_) + " está quieta.");

    start = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() < quiet_time_)
        now = std::chrono::steady_clock::now();
}

void Child::PickBall()
{
    log_handler_.Log("A criança " + std::to_string(id_) + " foi pegar a bola.");

    for (int i = 1 ; i < path_to_bucket_.size(); i++)
        emit SetChildPosition(id_, path_to_bucket_[i]);

    bucket_->Pull();
    has_ball_ = true;

    for (int i = path_to_bucket_.size() - 1; i >= 0; i--)
        emit SetChildPosition(id_, path_to_bucket_[i]);

    log_handler_.Log("A criança " + std::to_string(id_) + " pegou a bola.");
}

void Child::ReturnBall()
{
    log_handler_.Log("A criança " + std::to_string(id_) + " está indo devolver a bola.");

    for (int i = 1 ; i < path_to_bucket_.size(); i++)
        emit SetChildPosition(id_, path_to_bucket_[i]);

    bucket_->Push();
    has_ball_ = false;

    for (int i = path_to_bucket_.size() - 1; i >= 0; i--)
        emit SetChildPosition(id_, path_to_bucket_[i]);

    log_handler_.Log("A criança " + std::to_string(id_) + " devolveu a bola.");
}
