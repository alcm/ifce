#include "include/window_manager.h"

#include "include/mediator.h"

#include "ui_window_manager.h"

#include <QCloseEvent>

WindowManager::WindowManager(QWidget *parent)
    : QMainWindow{parent},
      ui_{new Ui::WindowManager}
{
    ui_->setupUi(this);
}

WindowManager::~WindowManager()
{
    delete ui_;
}

void WindowManager::SetScreen(QWidget *screen)
{
    ui_->stacked_widget->addWidget(screen);
    ui_->stacked_widget->setCurrentWidget(screen);

    show();
}
