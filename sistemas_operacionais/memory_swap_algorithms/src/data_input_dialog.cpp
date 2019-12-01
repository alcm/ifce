/**
 * \file
 * \brief  Bucket size dialog class implementation.
 */
#include "include/data_input_dialog.h"

#include <QFileDialog>
#include <iostream>

#include "ui_data_input_dialog.h"

DataInputDialog::DataInputDialog(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::DataInputDialog)
{
    ui_->setupUi(this);

    QObject::connect(ui_->ok_pb, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
    QObject::connect(ui_->file_browser_pb, SIGNAL(clicked()), this, SLOT(on_browse_file_button_clicked()));
}

DataInputDialog::~DataInputDialog()
{
    delete ui_;
}

void DataInputDialog::on_button_clicked()
{
    q1_ = ui_->q1_le->text().toInt();
    q2_ = ui_->q2_le->text().toInt();
    bit_r_ = ui_->bit_r_le->text().toInt();
    file_path_ = ui_->file_path_le->text();

    close();
}

void DataInputDialog::on_browse_file_button_clicked()
{
    ui_->file_path_le->setText(QFileDialog::getOpenFileName(this, tr("Selecione o arquivo"),
                                                            "/home/andre"));
}

QString DataInputDialog::file_path() const
{
    return file_path_;
}

int DataInputDialog::bit_r() const
{
    return bit_r_;
}

int DataInputDialog::q2() const
{
    return q2_;
}

int DataInputDialog::q1() const
{
    return q1_;
}
