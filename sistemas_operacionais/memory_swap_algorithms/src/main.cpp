#include "include/app.h"
#include "include/data_input_dialog.h"

#include <QMessageBox>

int main(int argc, char **argv)
{
    App app{argc, argv};
    DataInputDialog dialog;

    dialog.exec();

    int ret = 1;
    try {
        ret = app.Run(dialog.q1(), dialog.q2(), dialog.bit_r(), dialog.file_path().toStdString());
    } catch (const std::exception &e) {
        QMessageBox::warning(&dialog, "Erro", QString::fromStdString(e.what()));
    }

    return ret;
}
