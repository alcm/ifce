#include "include/algorithm_execution_screen.h"

#include "ui_algorithm_execution_screen.h"

#include <QTableWidget>
#include <QHeaderView>

#include "include/execute_algorithms_cmd.h"
#include "include/execution_event_handler.h"
#include "include/results_screen.h"
#include "include/set_screen_cmd.h"
#include "lib/include/fifo.h"
#include "lib/include/optimal.h"
#include "lib/include/nur.h"
#include "lib/include/mru.h"
#include "lib/include/second_chance.h"

AlgorithmExecutionScreen::AlgorithmExecutionScreen(int q1, int q2, int bit_r, const std::vector<swapping_algorithms::MemOperation> &data)
    : ScreenComponent{std::make_shared<ExecutionEventHandler>()},
      algo_names_({ { swapping_algorithms::AlgorithmId::MRU, "Mru" },
                    { swapping_algorithms::AlgorithmId::NUR, "Nur" },
                    { swapping_algorithms::AlgorithmId::FIFO, "Fifo" },
                    { swapping_algorithms::AlgorithmId::OPTIMAL, "Optimal" },
                    { swapping_algorithms::AlgorithmId::SECOND_CHANCE, "Second chance" } }),
      ui_{new Ui::AlgorithmExecutionScreen}
{
    ui_->setupUi(this);

    ui_->progress_bar->setValue(0);
    ui_->diag_status_label->setText("");

    if (!q1 || !q2 || !bit_r || data.empty())
        throw std::invalid_argument("Parâmetros inválidos");

    for (int i = q1; i <= q2; i++) {
        //algorithms_.emplace_back(std::make_shared<swapping_algorithms::Optimal>(i, data));
        algorithms_.emplace_back(std::make_shared<swapping_algorithms::Fifo>(i, data));
        //algorithms_.emplace_back(std::make_shared<swapping_algorithms::Nur>(bit_r, i, data));
        algorithms_.emplace_back(std::make_shared<swapping_algorithms::Mru>(i, data));
        algorithms_.emplace_back(std::make_shared<swapping_algorithms::SecondChance>(i, bit_r, data));
    }

    total_global_progress_ = 100 * (algorithms_.size() * 3);
    global_progress_ = 0;

    ConnectSignals();
}

AlgorithmExecutionScreen::~AlgorithmExecutionScreen()
{
    delete ui_;
}

void AlgorithmExecutionScreen::OnExecutionStart()
{
    ui_->diag_status_label->setText("Running");
}

void AlgorithmExecutionScreen::OnExecutionFinish()
{
    ui_->diag_status_label->setText("Finished");

    SetScreenCmd cmd(new ResultsScreen(results_));
    SendCommand(cmd);
}

void AlgorithmExecutionScreen::OnAlgorithmStart(const swapping_algorithms::AlgorithmId id, const uint32_t q)
{
    DrawExecutionEntry(id, q);
}

void AlgorithmExecutionScreen::OnAlgorithmFinish(const swapping_algorithms::AlgorithmId id, const uint32_t q, const uint32_t hit_count)
{
    auto wdg = GetAlgorithmWidget(id, q);

    if (wdg)
        wdg->SetFinish();

    ui_->progress_bar->setValue(100 * ((float)(++global_progress_) / algorithms_.size()));
    results_[q].emplace_back(swapping_algorithms::AlgorithmResult { algo_names_.at(id), (int)hit_count });
}

void AlgorithmExecutionScreen::OnProgress(const swapping_algorithms::AlgorithmId id, const uint32_t q, const uint8_t progress)
{
    auto wdg = GetAlgorithmWidget(id, q);

    if (wdg)
        wdg->SetProgress(progress);

}

void AlgorithmExecutionScreen::showEvent(QShowEvent *e)
{
    ExecuteAlgorithmsCmd cmd{algorithms_};

    SendCommand(cmd);
}

void AlgorithmExecutionScreen::DrawExecutionEntry(const swapping_algorithms::AlgorithmId &id, const uint32_t q)
{
    QTableWidget *table_widget{new QTableWidget};

    table_widget->setColumnCount(1);
    table_widget->horizontalHeader()->setVisible(false);
    table_widget->verticalHeader()->setVisible(false);
    table_widget->horizontalHeader()->setStretchLastSection(true);
    table_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table_widget->setStyleSheet("QTableWidget { border: 0px;  "
                                "border-bottom: 1px solid #BDBDBD; } "
                                "QTableWidget::item {  border-top: 1px #BDBDBD; "
                                "border-bottom: 1px solid #BDBDBD; "
                                "border-left: 1px solid #BDBDBD; "
                                "border-right: 1px solid #BDBDBD;} ");

    table_widget->setRowCount(table_widget->rowCount() + 1);
    auto algo_entry = new AlgorithmExecutionWidget{algo_names_.at(id) + " (Q = " + std::to_string(q) + ")", this};

    algo_entry->setStyleSheet("background-color: white;");
    widgets_.insert({ { id, q }, algo_entry });

    table_widget->setCellWidget(table_widget->rowCount() - 1, 0, algo_entry);
    ui_->vertical_layout_5->addWidget(table_widget);

    table_widget->setMinimumHeight(table_widget->rowCount()*
                                   table_widget->rowHeight(0));
    table_widget->setMaximumHeight(table_widget->rowCount()*
                                   table_widget->rowHeight(0));

}

AlgorithmExecutionWidget *AlgorithmExecutionScreen::GetAlgorithmWidget(const swapping_algorithms::AlgorithmId id, int q)
{
    for (auto &entry : widgets_) {
        if (entry.first.first == id && entry.first.second == q)
            return entry.second;
    }

    return nullptr;
}

void AlgorithmExecutionScreen::ConnectSignals()
{
    QObject::connect(event_handler_.get(), SIGNAL(ExecutionStart()), this,
                     SLOT(OnExecutionStart()), Qt::QueuedConnection);
    QObject::connect(event_handler_.get(), SIGNAL(ExecutionFinish()), this,
                     SLOT(OnExecutionFinish()), Qt::QueuedConnection);
    QObject::connect(event_handler_.get(),
                     SIGNAL(AlgorithmStart(const swapping_algorithms::AlgorithmId, const uint32_t)),
                     this,
                     SLOT(OnAlgorithmStart(const swapping_algorithms::AlgorithmId, const uint32_t)), Qt::QueuedConnection);
    QObject::connect(event_handler_.get(),
                     SIGNAL(AlgorithmFinish(const swapping_algorithms::AlgorithmId, const uint32_t, const uint32_t)),
                     this,
                     SLOT(OnAlgorithmFinish(const swapping_algorithms::AlgorithmId, const uint32_t, const uint32_t)), Qt::QueuedConnection);
    QObject::connect(event_handler_.get(),
                     SIGNAL(Progress(const swapping_algorithms::AlgorithmId, const uint32_t, const uint8_t)),
                     this,
                     SLOT(OnProgress(const swapping_algorithms::AlgorithmId, const uint32_t, const uint8_t)), Qt::QueuedConnection);
}
