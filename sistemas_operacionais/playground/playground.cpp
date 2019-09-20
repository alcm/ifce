#include "playground.h"
#include "ui_playground.h"

#include <QGraphicsItem>
#include <QMessageBox>

#include <functional>

Playground::Playground(const int bucket_capacity, QWidget *parent)
    : QMainWindow(parent),
      bucket_(new Bucket(bucket_capacity)),
      kMaxPlayers_(5),
      view_(&scene_),
      pool_(kMaxPlayers_),
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

    scene_.addItem(bucket_);
    bucket_->setPos(440, 610);
    bucket_->setScale(1.0);
    bucket_->setZValue(-0.1);

    paths_to_bucket_.insert({ 0, std::vector<QPoint>({ QPoint(400, 340), QPoint(400, 380),
                                                       QPoint(400, 385) }) });
    paths_to_bucket_.insert({ 1, std::vector<QPoint>({ QPoint(140, 350), QPoint(175, 380),
                                                       QPoint(200, 410), QPoint(225, 440),
                                                       QPoint(270, 450) }) });
    paths_to_bucket_.insert({ 2, std::vector<QPoint>({ QPoint(600, 350), QPoint(590, 380),
                                                       QPoint(580, 410), QPoint(570, 440),
                                                       QPoint(570, 450) }) });
    paths_to_bucket_.insert({ 3, std::vector<QPoint>({ QPoint(0,   450), QPoint(0,   480),
                                                       QPoint(0,   510), QPoint(0,   540),
                                                       QPoint(50,  540), QPoint(100, 540),
                                                       QPoint(150, 540), QPoint(170, 540),
                                                       QPoint(250, 540), QPoint(280, 540) }) });
    paths_to_bucket_.insert({ 4, std::vector<QPoint>({ QPoint(800, 430), QPoint(800, 480),
                                                       QPoint(800, 510), QPoint(800, 540),
                                                       QPoint(750, 540), QPoint(700, 540),
                                                       QPoint(650, 540), QPoint(600, 540),
                                                       QPoint(550, 540), QPoint(545, 540) }) });

    QObject::connect(ui_->create_child_button, SIGNAL(clicked()), this,
                     SLOT(OnAddChildButtonClicked()));
    QObject::connect(bucket_, SIGNAL(Repaint(const std::string &)), this,
                     SLOT(RepaintBucket(const std::string &)));
    QObject::connect(ui_->actionSobre, SIGNAL(triggered()), this, SLOT(ShowAboutPopup()));
}

Playground::~Playground()
{
    for (auto &entry : childs_) {
        auto ch = entry.second;

        ch->set_must_stop(true);
        UninstallChildSignals(ch);
    }

    bucket_->Destroy();

    QObject::disconnect(ui_->create_child_button, SIGNAL(clicked()), this,
                        SLOT(OnAddChildButtonClicked()));
    QObject::disconnect(bucket_, SIGNAL(Repaint(const std::string &)), this,
                        SLOT(RepaintBucket(const std::string &)));

    delete ui_;
}

void Playground::InstallChildSignals(Child *child)
{
    QObject::connect(child, SIGNAL(SetPosition(const int, const QPoint &)), this,
                     SLOT(SetChildPosition(const int, const QPoint &)));
    QObject::connect(child, SIGNAL(Repaint(const int, const std::string &)), this,
                     SLOT(RepaintChild(const int, const std::string &)));
    QObject::connect(child->log_handler(), SIGNAL(SendMsg(const std::string &)), this,
                     SLOT(LogMessage(const std::string &)));
}

void Playground::UninstallChildSignals(Child *child)
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
    bool has_ball = ui_->has_ball_checkbox->isChecked();
    int play_time = ui_->play_interval_line_edit->text().toInt();
    int quiet_time = ui_->quiet_interval_line_edit->text().toInt();
    int id = static_cast<int>(childs_.size());
    std::string name = ui_->id_line_edit->text().isEmpty() ? std::to_string(id)
                                                           : ui_->id_line_edit->text().toStdString();

    if (!quiet_time || !play_time) {
        QMessageBox::warning(this, "Erro", "Preencha os campos corretamente!");
        return;
    }

    if (childs_.size() < kMaxPlayers_)
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

void Playground::RepaintBucket(const std::string &img_path)
{
    std::lock_guard<std::mutex> lk(bucket_mutex_);

    bucket_->setPixmap(QPixmap(QString::fromStdString(img_path)));
}

void Playground::LogMessage(const std::string &msg)
{
    std::lock_guard<std::mutex> lk(log_mutex_);

    ui_->log_text_edit->append(QString::fromStdString(msg));
}

void Playground::ShowAboutPopup()
{
    std::string text = "Trabalho de Sistemas operacionais\n\nImagine N crianças que estão, a princípio, quietas."
                       " M (M < N) crianças inicialmente possuem uma bola e as outras, não. De "
                       "repente, sentem vontade de brincar com uma bola. Com esse desejo "
                       "incontrolável, as que já estão com a bola simplesmente brincam. As que não "
                       " têm bola correm ao cesto de bolas, que está inicialmente vazio e que suporta"
                       " até K bolas. Se o cesto possuir bolas, uma criança pega a bola e vai brincar"
                       " feliz. Se o cesto estiver vazio, ela fica esperando até que outra criança "
                       " coloque uma bola no cesto. Quando uma criança termina de brincar, ela tem "
                       "que colocar a bola no cesto, mas se o cesto já estiver cheio, ela segura a "
                       "bola até que outra criança retire uma bola que já está no cesto, e então "
                       "solta sua bola no cesto e volta a ficar quieta. Admita que as crianças "
                       "continuem brincando e descansando (quieta) eternamente. Utilizando semáforos,"
                       " modele esse problema problema resolvendo os conflitos entre os N threads "
                       "\"criança\".\n\nAluno: André Luis Carvalho Moreira\nDisponível em: "
                       " github.com/carvalhudo/ifce/tree/sistemas_operacionais/sistemas_operacionais/playground";

    QMessageBox::information(this, "Sobre", QString::fromStdString(text));
}

void Playground::CreateChild(const int id, const std::string &name, const int play_time,
                             const int quiet_time, const bool has_ball)
{
    auto c = new Child(id, name, play_time, quiet_time, has_ball, paths_to_bucket_[id], bucket_);

    DrawChild(c);
    InstallChildSignals(c);
    pool_.EnqueueTask(std::bind(&Child::MainThread, c));
}
