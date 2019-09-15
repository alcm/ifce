#ifndef BUCKET_SIZE_DIALOG_H
#define BUCKET_SIZE_DIALOG_H

#include <QDialog>

namespace Ui {
class BucketSizeDialog;
}

class BucketSizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BucketSizeDialog(QWidget *parent = nullptr);
    ~BucketSizeDialog();

    int bucket_capacity() const;

private slots:
    void OnButtonClicked();

private:
    int bucket_capacity_;
    Ui::BucketSizeDialog *ui_;
};

#endif // BUCKET_SIZE_DIALOG_H
