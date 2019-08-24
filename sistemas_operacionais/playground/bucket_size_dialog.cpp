/**
 * \file
 * \brief  Bucket size dialog class implementation.
 */
#include "bucket_size_dialog.h"
#include "ui_bucket_size_dialog.h"

BucketSizeDialog::BucketSizeDialog(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::BucketSizeDialog)
{
    ui_->setupUi(this);

    QObject::connect(ui_->ok_button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
}

BucketSizeDialog::~BucketSizeDialog()
{
    delete ui_;
}

void BucketSizeDialog::on_button_clicked()
{
    bucket_capacity_ = ui_->capacity_line_edit->text().toInt();
    close();
}

int BucketSizeDialog::bucket_capacity() const
{
    return bucket_capacity_;
}
