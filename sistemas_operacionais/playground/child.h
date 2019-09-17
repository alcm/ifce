#ifndef CHILD_H_
#define CHILD_H_

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPoint>

#include <cstdint>
#include <memory>
#include <string>

#include "bucket.h"
#include "logger.h"

class Child : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Child(const int id, const std::string &name, const int play_time, const int quiet_time,
          const bool has_ball, const std::vector<QPoint> &path_to_bucket,
          std::shared_ptr<Bucket> b);

    void MainThread();

    const Logger *log_handler() const;

    int id() const;

    void set_must_stop(bool must_stop);

signals:
    void SetPosition(const int id, const QPoint &point);
    void Repaint(const int id, const std::string &img_path);

private:
    void Play();
    void StayQuiet();
    void PickBall();
    void ReturnBall();

    bool must_stop_;
    uint8_t play_time_;
    uint8_t quiet_time_;
    int id_;
    std::string name_;
    bool has_ball_;
    std::shared_ptr<Bucket> bucket_;
    std::vector<QPoint> path_to_bucket_;
    const std::vector<std::string> images_;
    Logger log_handler_;
};

#endif // CHILD_H_
