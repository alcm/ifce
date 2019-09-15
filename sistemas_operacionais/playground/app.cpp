#include <QApplication>

#include <QDialog>
#include "bucket_size_dialog.h"
#include "playground.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BucketSizeDialog dialog;

    dialog.exec();

    Playground w(dialog.bucket_capacity());

    w.show();

    return a.exec();
}
