#ifndef RESULTS_SCREEN_H
#define RESULTS_SCREEN_H

#include <QTableWidget>

#include "include/mediator.h"
#include "lib/include/types.h"

namespace Ui {
class ResultsScreen;
}

class ResultsScreen : public ScreenComponent
{
    Q_OBJECT

public:
    ResultsScreen(const std::map<int, std::vector<swapping_algorithms::AlgorithmResult>> &results,
                  QWidget *parent = nullptr);
    ~ResultsScreen();

private:
    QTableWidget table_;
    Ui::ResultsScreen *ui;
};

#endif // RESULTS_SCREEN_H
