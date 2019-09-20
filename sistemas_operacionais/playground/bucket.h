#ifndef BUCKET_H_
#define BUCKET_H_

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QSemaphore>

#include <cstdint>
#include <map>
#include <mutex>

class Bucket : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Bucket(const uint8_t bucket_capacity);

    void Push();
    void Pull();
    void Destroy();

signals:
    void Repaint(const std::string &img_path);

private:
   QSemaphore available_positions_sem_;
   QSemaphore available_balls_sem_;

   std::mutex mutex_;

   std::map<int, std::string> imgs_;
};

#endif // BUCKET_H_
