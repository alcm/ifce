/**
 * \file
 * \brief  Bucket size dialog class definition.
 */
#ifndef BUCKET_SIZE_DIALOG_H
#define BUCKET_SIZE_DIALOG_H

#include <QDialog>

namespace Ui {
class BucketSizeDialog;
}

/**
 * \brief  The bucket size dialog class represents the dialog responsible for get the bucket
 * capacity from user.
 */
class BucketSizeDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * \brief  Constructor.
     * \param  parent Widget parent.
     */
    explicit BucketSizeDialog(QWidget *parent = nullptr);

    /**
     * \brief  Destructor.
     */
    ~BucketSizeDialog();

    /**
     * \brief  Get the bucket capacity.
     * \return The bucket capacity.
     */
    int bucket_capacity() const;

private slots:
    /**
     * \brief  Button clicked callback.
     */
    void on_button_clicked();

private:
    int bucket_capacity_;       //!< Capacity of bucket.
    Ui::BucketSizeDialog *ui_;  //!< Ui component.
};

#endif // BUCKET_SIZE_DIALOG_H
