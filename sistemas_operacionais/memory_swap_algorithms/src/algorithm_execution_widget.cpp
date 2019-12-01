#include "include/algorithm_execution_widget.h"

#include "ui_algorithm_execution_widget.h"

AlgorithmExecutionWidget::AlgorithmExecutionWidget(const std::string &algorithm_name,
                                                   QWidget* parent)
    : QWidget{parent},
      ui_{new Ui::AlgorithmExecutionWidget},
      gif_movie_{new QMovie{KProgressGif}} {
    ui_->setupUi(this);

    ui_->algorithm_name_label->setText(QString::fromStdString(algorithm_name));
    ui_->test_progress_bar->setVisible(true);
    ui_->progress_label->setVisible(true);
    ui_->img_label->setMovie(gif_movie_.get());
    gif_movie_->start();
}

AlgorithmExecutionWidget::~AlgorithmExecutionWidget()
{
    delete ui_;
}

void AlgorithmExecutionWidget::SetProgress(const int progress)
{
    ui_->progress_label->setText(QString::number(progress) + " %");
    ui_->test_progress_bar->setValue(progress);
}

void AlgorithmExecutionWidget::SetFinish()
{
    QString img_path(kTestSuccessImg);

    gif_movie_->stop();
    ui_->img_label->setPixmap(QPixmap{img_path});
}
