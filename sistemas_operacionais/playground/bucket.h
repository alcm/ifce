#ifndef BUCKET_H_
#define BUCKET_H_

#include <QObject>

#include <cstdint>
#include <map>
#include <mutex>

class Bucket : public QObject
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
   uint8_t n_balls_;
   uint8_t capacity_;

   std::map<int, std::string> imgs_;
};

#endif // BUCKET_H_
