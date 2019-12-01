#ifndef ALGORITHM_EXECUTION_WIDGET_H_
#define ALGORITHM_EXECUTION_WIDGET_H_

#include <QMovie>
#include <QWidget>

#include <memory>

namespace Ui {
    class AlgorithmExecutionWidget;
}

class AlgorithmExecutionWidget : public QWidget {
    Q_OBJECT
public:
    AlgorithmExecutionWidget(const std::string &algorithm_name,
                             QWidget* parent = nullptr);

    ~AlgorithmExecutionWidget();


public slots:
    void SetProgress(const int progress);

    void SetFinish();

private:
    const QString kTestSuccessImg{":/new/prefix1/images/icn_OK16x16.png"}; //!< Test success icon.
    const QString KProgressGif{":/new/prefix1/images/smallLoading.gif"}; //!< Progress gif icon.

    std::unique_ptr<QMovie> gif_movie_; //!< Progress gif.

    Ui::AlgorithmExecutionWidget *ui_;
};

#endif  // ALGORITHM_EXECUTION_WIDGET_H_
