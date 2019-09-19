#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QMainWindow>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPoint>

#include <map>

#include "bucket.h"
#include "child.h"
#include "thread_pool.h"

namespace Ui {
class Playground;
}

class Playground : public QMainWindow
{
    Q_OBJECT

public:
    Playground(const int bucket_capacity = 0, QWidget *parent = nullptr);
    ~Playground();

private slots:
    void OnAddChildButtonClicked();
    void SetChildPosition(const int id, const QPoint &point);
    void RepaintChild(const int id, const std::string &img_path);
    void RepaintBucket(const std::string &img_path);
    void LogMessage(const std::string &msg);

private:
    void InstallChildSignals(Child *child);
    void UninstallChildSignals(Child *child);
    void CreateChild(const int id, const std::string &name, const int play_time, const int quiet_time, const bool has_ball);
    void DrawChild(Child *ch);

    std::map<int, Child *> childs_;
    std::map<int, std::vector<QPoint>> paths_to_bucket_;

    uint8_t kPlaygroundCapacity_;
    std::mutex log_mutex_;
    std::mutex child_mutex_;
    std::mutex bucket_mutex_;
    Bucket *bucket_;

    QGraphicsScene scene_;
    QGraphicsView view_;
    ThreadPool pool_;
    Ui::Playground *ui_;
};

#endif // PLAYGROUND_H
