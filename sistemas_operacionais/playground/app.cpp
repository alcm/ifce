#include "playground.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Playground w;
    w.show();

    return a.exec();
}
