#include "playground.h"
#include "ui_playground.h"

#include <functional>

Playground::Playground(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::Playground),
    kPlaygroundCapacity_(10),
    pool_(kPlaygroundCapacity_),
    bucket_(std::make_shared<Bucket>(kPlaygroundCapacity_))
{
    ui_->setupUi(this);

    QObject::connect(ui_->create_child_button_, SIGNAL(clicked()), this,
                     SLOT(OnAddChildButtonClicked()));

//    paths_to_bucket_.insert({ 0, std::vector<QPoint>() });
//    paths_to_bucket_.insert({ 1, std::vector<QPoint>() });
//    paths_to_bucket_.insert({ 2, std::vector<QPoint>() });
//    paths_to_bucket_.insert({ 3, std::vector<QPoint>() });
//    paths_to_bucket_.insert({ 4, std::vector<QPoint>() });
//    paths_to_bucket_.insert({ 5, std::vector<QPoint>() });
//    paths_to_bucket_.insert({ 6, std::vector<QPoint>() });
//    paths_to_bucket_.insert({ 7, std::vector<QPoint>() });
//    paths_to_bucket_.insert({ 8, std::vector<QPoint>() });
//    paths_to_bucket_.insert({ 9, std::vector<QPoint>() });
}

Playground::~Playground()
{
    for (auto &entry : childs_) {
        auto ch = entry.second;

        QObject::disconnect(ch, SIGNAL(DrawChild(const int, const QPoint &)), this,
                            SLOT(DrawChild(const int, const QPoint &)));
        QObject::disconnect(ch, SIGNAL(SetChildPosition(const int, const QPoint &)), this,
                            SLOT(SetChildPosition(const int, const QPoint &)));
        QObject::disconnect(ch->log_handler(), SIGNAL(SendMsg(const std::string &)), this,
                            SLOT(LogMessage(const std::string &)));

        delete ch;
    }

    QObject::disconnect(ui_->create_child_button_, SIGNAL(clicked()), this,
                        SLOT(OnAddChildButtonClicked()));

    delete ui_;
}

void Playground::OnAddChildButtonClicked()
{
    int id = childs_.size();
    int play_time = ui_->play_interval_line_edit_->text().toInt();
    int quiet_time = ui_->quiet_interval_line_edit_->text().toInt();
    bool has_ball = ui_->has_ball_checkbox_->isChecked();

    AddChild(id, play_time, quiet_time, has_ball);
}

void Playground::DrawChild(const int id, const QPoint &point)
{
    std::lock_guard<std::mutex> lk(child_mutex_);

    // auto child = childs_.at(id);
    // TODO: add child to screen
}

void Playground::SetChildPosition(const int id, const QPoint &point)
{

}

void Playground::LogMessage(const std::string &msg)
{
    std::lock_guard<std::mutex> lk(log_mutex_);

    ui_->log_text_edit_->append(QString::fromStdString(msg));
}

void Playground::AddChild(const int id, const int play_time, const int quiet_time,
                          const bool has_ball)
{
    if (childs_.size() < kPlaygroundCapacity_) {
        Child *c = new Child(id, play_time, quiet_time, has_ball, paths_to_bucket_[id], bucket_);

        QObject::connect(c, SIGNAL(DrawChild(const int, const QPoint &)), this,
                         SLOT(DrawChild(const int, const QPoint &)));
        QObject::connect(c, SIGNAL(SetChildPosition(const int, const QPoint &)), this,
                         SLOT(SetChildPosition(const int, const QPoint &)));
        QObject::connect(c->log_handler(), SIGNAL(SendMsg(const std::string &)), this,
                         SLOT(LogMessage(const std::string &)));

        childs_.insert({ id, c });
        pool_.EnqueueTask(std::bind(&Child::MainThread, c));
    }
}
