/**
 * \file
 * \brief  Playground definition.
 */
#ifndef PLAYGROUND_H_
#define PLAYGROUND_H_

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QPoint>

#include <map>

#include "bucket.h"
#include "child.h"
#include "thread_pool.h"

namespace Ui {
class Playground;
}

/**
 * \brief  Playground class definition. This class is the graphical representation of playground
 * component.
 */
class Playground : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * \brief  Constructor.
     * \param  bucket_capacity Capacity of bucket.
     * \param  parent Parent widget.
     */
    Playground(const int bucket_capacity = 0, QWidget *parent = nullptr);

    /**
     * \brief  Destructor.
     */
    ~Playground();

private slots:
    /**
     * \brief  'Add child' button callback.
     */
    void OnAddChildButtonClicked();

    /**
     * \brief  Set the child position on playground.
     * \param  id Child's ID.
     * \param  point New child cordinate.
     */
    void SetChildPosition(const int id, const QPoint &point);

    /**
     * \brief  Repaint the child on playground (used to refresh the child image).
     * \param  id Child's ID.
     * \param  img_path Path to the new child image.
     */
    void RepaintChild(const int id, const std::string &img_path);

    /**
     * \brief  Repaint the bucket on playground (used to refresh the bucket image when a ball is
     * pulled/pushed from bucket).
     * \param  img_path Path to new bucket image.
     */
    void RepaintBucket(const std::string &img_path);

    /**
     * \brief  Log a message on log visual component.
     * \param  msg Message to be logged.
     */
    void LogMessage(const std::string &msg);

    /**
     * \brief  Show the 'about' popup.
     */
    void ShowAboutPopup();

    /**
     * \brief  Exit the application gracefully.
     */
    void Exit();

    /**
     * \brief  Perform the cleanup for the child instance.
     * \param  id Child's ID.
     */
    void HandleChildThreadFinished(const int id);

private:
    /**
     * \brief  Install the child signals.
     * \param  child Child instance.
     */
    void InstallChildSignals(Child *child);

    /**
     * \brief  Create a new child.
     * \param  id Child's ID.
     * \param  name Child's name.
     * \param  play_time Child's play time.
     * \param  quiet_time Child's quiet time.
     * \param  has_ball Flag who indicates if the child has a ball.
     */
    void CreateChild(const int id, const std::string &name, const int play_time,
                     const int quiet_time, const bool has_ball);

    /**
     * \brief  Draw a new child on playground.
     * \param  ch Child.
     */
    void DrawChild(Child *ch);

    std::map<int, Child *> childs_;                      //!< Child map.
    std::map<int, std::vector<QPoint>> paths_to_bucket_; //!< Predefined paths to bucket.

    uint8_t kMaxPlayers_;     //!< Maximum number of child on playground.
    std::mutex log_mutex_;    //!< Semaphore for log.

    QGraphicsScene *scene_; //!< Playground scene.
    QGraphicsView view_;    //!< Playground view.
    Bucket *bucket_;        //!< Bucket of balls.
    ThreadPool *pool_;      //!< Thread pool.
    Ui::Playground *ui_;    //!< UI.
};

#endif // PLAYGROUND_H_
