#include <QApplication>

#include <QDialog>
#include <QMessageBox>
#include <QString>

#include "bucket_size_dialog.h"
#include "playground.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BucketSizeDialog dialog;

    dialog.exec();

    int ret;
    try {
        Playground w(dialog.bucket_capacity());

        w.show();
        ret = a.exec();
    } catch (const std::exception &e) {
        QMessageBox::warning(&dialog, "Erro", QString::fromStdString(e.what()));
    }

    return ret;
}
