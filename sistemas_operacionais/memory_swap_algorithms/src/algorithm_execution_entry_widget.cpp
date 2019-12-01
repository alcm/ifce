#include "views/sample_api/include/test_execution_entry_widget.h"

#include "ui_test_execution_entry_widget.h"

namespace sample_api {

TestExecutionEntryWidget::TestExecutionEntryWidget(const std::string &test_name,
                                                   QWidget* parent)
  : QWidget{parent},
    ui_{new Ui::TestExecutionEntryWidget},
    gif_movie_{new QMovie{KProgressGif}} {
  ui_->setupUi(this);

  ui_->test_name_label->setText(QString::fromStdString(test_name));
  ui_->test_progress_bar->setVisible(false);
  ui_->progress_label->setVisible(false);
  ui_->img_label->setText("Waiting...");
}

TestExecutionEntryWidget::~TestExecutionEntryWidget() {
  delete ui_;
}

void TestExecutionEntryWidget::SetTestProgress(const uint8_t progress) {
  ui_->progress_label->setText(QString::number(progress) + " %");
  ui_->test_progress_bar->setValue(progress);
}

void TestExecutionEntryWidget::TestFinish(const ldiag::core::TestResult result) {
  gif_movie_->stop();
  ui_->test_progress_bar->setVisible(false);
  ui_->progress_label->setVisible(false);

  QString img_path;
  QString test_status;

  if (result == ldiag::core::TestResult::kSuccess) {
    img_path = kTestSuccessImg;
    test_status = "Success";
  } else if (result == ldiag::core::TestResult::kFail) {
    img_path = kTestFailedImg;
    test_status = "Failed";
  } else {
    img_path = kTestNotSupportedImg;
    test_status = "Not supported";
  }

  // TODO(andre.carvalho) implement all test results.

  ui_->img_label->setPixmap(QPixmap{img_path});
  ui_->test_status->setText(test_status);
}

void TestExecutionEntryWidget::TestStart() {
  ui_->test_progress_bar->setVisible(true);
  ui_->progress_label->setVisible(true);

  ui_->img_label->setMovie(gif_movie_.get());
  gif_movie_->start();
}

}
