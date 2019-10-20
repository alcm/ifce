/**
 * \file
 * \brief  Child definition.
 */
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

/**
 * \brief  Child class definition. The Child class represents a graphical child.
 */
class Child : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * \brief  Constructor.
     * \param  id Child's ID.
     * \param  name Child's name.
     * \param  play_time Child's play time.
     * \param  quiet_time Child's quiet time.
     * \param  has_ball Flag who indicates if the child has a ball.
     * \param  path_to_bucket Path to the bucket.
     * \param  b Bucket.
     */
    Child(const int id, const std::string &name, const int play_time, const int quiet_time,
          const bool has_ball, const std::vector<QPoint> &path_to_bucket,
          Bucket *b);

    /**
     * \brief  Child main routine.
     */
    void MainThread();

    /**
     * \brief  Get the log handler.
     * \return Log handler.
     */
    const Logger *log_handler() const;

    /**
     * \brief  Get the child ID.
     * \return The child ID.
     */
    int id() const;

    /**
     * \brief  Set the 'must stop' flag.
     * \param  must_stop Flag value.
     */
    void set_must_stop(bool must_stop);

signals:
    /**
     * \brief  Signal for set the child position.
     * \param  id Child's ID.
     * \param  point New position.
     */
    void SetPosition(const int id, const QPoint &point);

    /**
     * \brief  Signal for repaint the child on playground.
     * \param  id Child's ID.
     * \param  img_path Path to the new image.
     */
    void Repaint(const int id, const std::string &img_path);

    /**
     * \brief  Signal indicating the child's main thread has finished.
     * \param  id Child's ID.
     */
    void Finished(const int id);

private:
    /**
     * \brief  Play routine of child.
     */
    void Play();

    /**
     * \brief  Stay quiet routine of child.
     */
    void StayQuiet();

    /**
     * \brief  Pick a ball from bucket.
     */
    void PickBall();

    /**
     * \brief  Return a ball to bucket.
     */
    void ReturnBall();

    bool must_stop_;                        //!< Flag indicating the child's main thread to stop.
    uint8_t play_time_;                     //!< Child's play time.
    uint8_t quiet_time_;                    //!< Child's quiet time.
    int id_;                                //!< Child's ID.
    std::string name_;                      //!< Child's name.
    bool has_ball_;                         //!< Child's 'has ball' flag.
    Bucket *bucket_;                        //!< Bucket.
    std::vector<QPoint> path_to_bucket_;    //!< Path to bucket.
    const std::vector<std::string> images_; //!< List of child images.
    Logger log_handler_;                    //!< Log handler.
};

#endif // CHILD_H_
