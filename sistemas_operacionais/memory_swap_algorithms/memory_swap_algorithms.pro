#-------------------------------------------------
#
# Project created by QtCreator 2019-11-24T15:59:42
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = memory_swap_algorithms
TEMPLATE = app
LIBS += -L/home/andre/dev/ifce/sistemas_operacionais/memory_swap_algorithms/lib/build -lswapping_algorithms


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        src/algorithm_execution_screen.cpp \
        src/algorithm_execution_widget.cpp \
        src/app.cpp \
        src/controller.cpp \
        src/data_input_dialog.cpp \
        src/execution_event_handler.cpp \
        src/main.cpp \
        src/results_screen.cpp \
        src/window_manager.cpp

HEADERS += \
        include/algorithm_execution_screen.h \
        include/algorithm_execution_widget.h \
        include/app.h \
        include/command.h \
        include/data_input_dialog.h \
        include/execute_algorithms_cmd.h \
        include/execution_event_handler.h \
        include/event_handler.h \
        include/mediator.h \
        include/results_screen.h \
        include/set_screen_cmd.h \
        include/window_manager.h

FORMS += \
        view/algorithm_execution_screen.ui \
        view/algorithm_execution_widget.ui \
        view/data_input_dialog.ui \
        view/results_screen.ui \
        view/window_manager.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += images.qrc
