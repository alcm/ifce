#include "playground.h"
#include "ui_playground.h"

#include <QGraphicsItem>

#include <functional>

Playground::Playground(const int bucket_capacity, QWidget *parent)
    : QMainWindow(parent),
      bucket_(std::make_shared<Bucket>(kPlaygroundCapacity_)),
      kPlaygroundCapacity_(bucket_capacity),
      pool_(kPlaygroundCapacity_),
      view_(&scene_),
      ui_(new Ui::Playground)
{
    if (!bucket_capacity)
        throw std::invalid_argument("Capacidade do cesto inválida.");

    ui_->setupUi(this);
    ui_->layout->addWidget(&view_);

    // Draw background
    auto bg_img = new QGraphicsPixmapItem(QPixmap(":/images/images/background.jpg"));

    scene_.addItem(bg_img);
    bg_img->setPos(0, 0);
    bg_img->setScale(1.4);
    bg_img->setZValue(-0.1);

    // Draw bucket
    auto bucket_img = new QGraphicsPixmapItem(QPixmap(":/images/images/ball_barrel.png"));

    scene_.addItem(bucket_img);
    bucket_img->setPos(500, 680);
    bucket_img->setScale(1.0);
    bucket_img->setZValue(-0.1);

    paths_to_bucket_.insert({ 0, std::vector<QPoint>({ QPoint(0,   450), QPoint(0,   480),
                                                       QPoint(0,   510), QPoint(0,   540),
                                                       QPoint(50,  540), QPoint(100, 540),
                                                       QPoint(150, 540), QPoint(200, 540),
                                                       QPoint(250, 540), QPoint(300, 540) }) });
    paths_to_bucket_.insert({ 1, std::vector<QPoint>({ QPoint(800,  450), QPoint(800, 480),
                                                       QPoint(800,   510), QPoint(800,   540),
                                                       QPoint(750,  540), QPoint(700, 540),
                                                       QPoint(650, 540), QPoint(600, 540),
                                                       QPoint(550, 540), QPoint(500, 540) }) });
    paths_to_bucket_.insert({ 2, std::vector<QPoint>({ QPoint(380,  350), QPoint(380, 380),
                                                       QPoint(380, 420) }) });
    paths_to_bucket_.insert({ 3, std::vector<QPoint>({ QPoint(150,  350), QPoint(175,  380),
                                                       QPoint(200,  410), QPoint(225,  440),
                                                       QPoint(250,  470), QPoint(275, 500),
                                                       QPoint(300, 530), QPoint(325, 560) }) });
    paths_to_bucket_.insert({ 4, std::vector<QPoint>({ QPoint(600,  350), QPoint(590, 380),
                                                       QPoint(580,  410), QPoint(570,  440),
                                                       QPoint(560,  470), QPoint(550, 500),
                                                       QPoint(540, 530), QPoint(530, 560) }) });

    QObject::connect(ui_->create_child_button, SIGNAL(clicked()), this,
                     SLOT(OnAddChildButtonClicked()));
}

Playground::~Playground()
{
    for (auto &entry : childs_) {
        auto ch = entry.second;

        UninstallSignals(ch);
        delete ch;
    }

    QObject::disconnect(ui_->create_child_button, SIGNAL(clicked()), this,
                        SLOT(OnAddChildButtonClicked()));

    delete ui_;
}

void Playground::InstallSignals(Child *child)
{
    QObject::connect(child, SIGNAL(SetPosition(const int, const QPoint &)), this,
                     SLOT(SetChildPosition(const int, const QPoint &)));
    QObject::connect(child, SIGNAL(Repaint(const int, const std::string &)), this,
                     SLOT(RepaintChild(const int, const std::string &)));
    QObject::connect(child->log_handler(), SIGNAL(SendMsg(const std::string &)), this,
                     SLOT(LogMessage(const std::string &)));
}

void Playground::UninstallSignals(Child *child)
{
    QObject::disconnect(child, SIGNAL(SetPosition(const int, const QPoint &)), this,
                        SLOT(SetChildPosition(const int, const QPoint &)));
    QObject::disconnect(child, SIGNAL(Repaint(const int, const std::string &)), this,
                        SLOT(RepaintChild(const int, const std::string &)));
    QObject::disconnect(child->log_handler(), SIGNAL(SendMsg(const std::string &)), this,
                        SLOT(LogMessage(const std::string &)));
}

void Playground::OnAddChildButtonClicked()
{
    int id = static_cast<int>(childs_.size());
    std::string name = ui_->id_line_edit->text().isEmpty() ? std::to_string(id)
                                                           : ui_->id_line_edit->text().toStdString();
    int play_time = ui_->play_interval_line_edit->text().toInt();
    int quiet_time = ui_->quiet_interval_line_edit->text().toInt();
    bool has_ball = ui_->has_ball_checkbox->isChecked();

    if (childs_.size() < kPlaygroundCapacity_)
        CreateChild(id, name, play_time, quiet_time, has_ball);
}

void Playground::DrawChild(Child *ch)
{
    std::lock_guard<std::mutex> lk(child_mutex_);

    auto start_pos = paths_to_bucket_.at(childs_.size()).front();

    scene_.addItem(ch);
    childs_.insert({ ch->id(), ch });
    ch->setPos(start_pos.x(), start_pos.y());
}

void Playground::SetChildPosition(const int id, const QPoint &point)
{
    std::lock_guard<std::mutex> lk(child_mutex_);

    auto child = childs_.at(id);
    if (child)
        child->setPos(point.x(), point.y());
}

void Playground::RepaintChild(const int id, const std::string &img_path)
{
    std::lock_guard<std::mutex> lk(child_mutex_);

    auto child = childs_.at(id);
    if (child)
        child->setPixmap(QPixmap(img_path.c_str()));
}

void Playground::LogMessage(const std::string &msg)
{
    std::lock_guard<std::mutex> lk(log_mutex_);

    ui_->log_text_edit->append(QString::fromStdString(msg));
}

void Playground::CreateChild(const int id, const std::string &name, const int play_time,
                             const int quiet_time, const bool has_ball)
{
    Child *c = new Child(id, name, play_time, quiet_time, has_ball, paths_to_bucket_[id], bucket_);

    DrawChild(c);
    InstallSignals(c);
    pool_.EnqueueTask(std::bind(&Child::MainThread, c));
}
