#include "include/results_screen.h"
#include "ui_results_screen.h"

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QBarCategoryAxis>

ResultsScreen::ResultsScreen(const std::map<int, std::vector<swapping_algorithms::AlgorithmResult> > &results,
                             QWidget *parent)
    : ScreenComponent{nullptr},
      ui(new Ui::ResultsScreen)
{
    ui->setupUi(this);

    QTableWidget *table = new QTableWidget(this);
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels(QStringList() << "QUANTIDADE DE FRAMES" << "FIFO" << "NUR" << "MRU" << "SEGUNDA CHANCE" << "OTIMO");
    table->setColumnWidth(0, 200);
    table->setColumnWidth(1, 196);
    table->setColumnWidth(2, 196);
    table->setColumnWidth(3, 196);
    table->setColumnWidth(4, 195);
    table->setColumnWidth(5, 155);

    auto chart = new QtCharts::QChart();

    auto series_fifo = new QtCharts::QLineSeries();
    auto series_mru = new QtCharts::QLineSeries();
    auto series_second_chance = new QtCharts::QLineSeries();

    series_fifo->setName("Fifo");
    series_mru->setName("Mru");
    series_second_chance->setName("Second chance");

    series_fifo->setPointsVisible(true);
    series_mru->setPointsVisible(true);
    series_second_chance->setPointsVisible(true);

    QStringList axis_x_list;
    QStringList axis_y_list;

    axis_x_list << "0";
    axis_y_list << "0";

    int counter = 0;
    for (auto &result : results) {
        int q = result.first;
        table->insertRow(counter);
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(QString::number(q));
        table->setItem(counter, 0, item);

        axis_x_list << QString::number(q);
        for (auto &entry : result.second) {
            int hit_count = entry.hit_count;

            axis_y_list << QString::number(hit_count);

            if (!entry.name.compare("Fifo")) {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setText(QString::number(hit_count));
                table->setItem(counter, 1, item);
                *series_fifo << QPoint(q, hit_count);
            } else if (!entry.name.compare("Mru")) {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setText(QString::number(hit_count));
                table->setItem(counter, 3, item);
                *series_mru << QPoint(q, hit_count);
            } else if (!entry.name.compare("Second chance")) {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setText(QString::number(hit_count));
                table->setItem(counter, 4, item);
                *series_second_chance << QPoint(q, hit_count);
            }
        }

        counter++;
    }

    chart->addSeries(series_fifo);
    chart->addSeries(series_mru);
    chart->addSeries(series_second_chance);

    QtCharts::QBarCategoryAxis *axis_x = new QtCharts::QBarCategoryAxis();
    QtCharts::QBarCategoryAxis *axis_y = new QtCharts::QBarCategoryAxis();

    axis_x->append(axis_x_list);
    axis_y->append(axis_y_list);

    chart->setTitle("Resultados");
    QFont font;

    font.setBold(true);
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->addAxis(axis_y, Qt::AlignmentFlag::AlignLeft);
    chart->addAxis(axis_x, Qt::AlignmentFlag::AlignBottom);
    chart->axisX()->setTitleText("Quantidade de Frames");
    chart->axisY()->setTitleText("Quantidade de Acertos");
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->verticalLayout->addWidget(chartView);
    ui->verticalLayout->addWidget(table);
}

ResultsScreen::~ResultsScreen()
{
    delete ui;
}
