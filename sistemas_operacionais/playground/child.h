#ifndef CHILD_H_
#define CHILD_H_

#include <QObject>
#include <QPoint>

#include <cstdint>
#include <memory>
#include <string>

#include "bucket.h"
#include "logger.h"

class Child : public QObject
{
    Q_OBJECT
public:
    Child(const int id, const int play_time, const int quiet_time,
          const bool has_ball, const std::vector<QPoint> &path_to_bucket,
          std::shared_ptr<Bucket> b);

    void MainThread();

    const Logger *log_handler() const;

signals:
    void SetChildPosition(const int id, const QPoint &point);
    void RefreshChild(const int id);
    void DrawChild(const int id, const QPoint &point);

private:
    void Play();
    void StayQuiet();
    void PickBall();
    void ReturnBall();

    uint8_t play_time_;
    uint8_t quiet_time_;
    uint8_t id_;
    bool has_ball_;
    std::string status_;
    std::shared_ptr<Bucket> bucket_;
    std::vector<QPoint> path_to_bucket_;
    Logger log_handler_;
};

#endif // CHILD_H_
