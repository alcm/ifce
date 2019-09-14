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
    explicit Playground(QWidget *parent = nullptr);
    ~Playground();

public slots:
    void SetChildPosition(const int id, const QPoint &point);
    void RepaintChild(const int id, const std::string &img_path);
    void LogMessage(const std::string &msg);

private slots:
    void OnAddChildButtonClicked();

private:
    void InstallSignals(Child *child);
    void UninstallSignals(Child *child);
    void CreateChild(const int id, const int play_time, const int quiet_time, const bool has_ball);
    void DrawChild(Child *ch);

    std::shared_ptr<Bucket> bucket_;
    std::map<int, Child *> childs_;
    std::map<int, std::vector<QPoint>> paths_to_bucket_;

    uint8_t kPlaygroundCapacity_;
    std::mutex log_mutex_;
    std::mutex child_mutex_;
    ThreadPool pool_;

    QGraphicsScene scene_;
    QGraphicsView view_;
    Ui::Playground *ui_;
};

#endif // PLAYGROUND_H
