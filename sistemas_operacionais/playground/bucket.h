#ifndef BUCKET_H_
#define BUCKET_H_

#include <QGraphicsPixmapItem>
#include <QObject>

#include <cstdint>
#include <map>
#include <mutex>

#include "semaphore.h"

class Bucket : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Bucket(const uint8_t bucket_capacity);

    void Push();
    void Pull();

signals:
    void Repaint(const std::string &img_path);

private:
   std::mutex mutex_;

   Semaphore available_positions_sem_;
   Semaphore available_balls_sem_;
   std::map<int, std::string> imgs_;
};

#endif // BUCKET_H_
