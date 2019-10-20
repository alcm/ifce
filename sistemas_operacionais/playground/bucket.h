/**
 * \file
 * \brief  Bucket class.
 */
#ifndef BUCKET_H_
#define BUCKET_H_

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QSemaphore>

#include <cstdint>
#include <map>
#include <mutex>

/**
 * \brief  Bucket class definition. The Bucket class represents the graphical bucket ball.
 */
class Bucket : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * \brief  Constructor.
     * \param  bucket_capacity Capacity of bucket.
     */
    explicit Bucket(const uint8_t bucket_capacity);

    /**
     * \brief  Push a ball into the bucket.
     */
    void Push();

    /**
     * \brief  Pull a ball from the bucket.
     */
    void Pull();

    /**
     * \brief  Wake up all threads.
     */
    void Destroy();

signals:
    /**
     * \brief  Signalize to GUI thread for change bucket image.
     * \param  img_path Image path.
     */
    void Repaint(const std::string &img_path);

private:
   QSemaphore available_positions_sem_; //!< Available positions in the bucket semaphore.
   QSemaphore available_balls_sem_;     //!< Abailable balls in the bucket semaphore.
   bool stop_;                          //!< Flag who indicates that the application was signalized to finish.
   std::mutex mutex_;                   //!< Bucket semaphore.

   std::map<int, std::string> imgs_;    //!< Images map.
};

#endif // BUCKET_H_
