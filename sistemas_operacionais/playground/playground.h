#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QMainWindow>
#include <QObject>
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
    void DrawChild(const int id, const QPoint &point);
    void SetChildPosition(const int id, const QPoint &point);
    void LogMessage(const std::string &msg);

private slots:
    void OnAddChildButtonClicked();

private:
    void AddChild(const int id, const int play_time, const int quiet_time, const bool has_ball);

    std::shared_ptr<Bucket> bucket_;
    std::map<int, Child *> childs_;
    std::map<int, QImage *> child_images_;
    std::map<int, std::vector<QPoint>> paths_to_bucket_;

    uint8_t kPlaygroundCapacity_;
    std::mutex log_mutex_;
    std::mutex child_mutex_;
    ThreadPool pool_;

    Ui::Playground *ui_;
};

#endif // PLAYGROUND_H
