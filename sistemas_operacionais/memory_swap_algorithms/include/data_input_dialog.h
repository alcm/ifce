/**
 * \file
 * \brief  Bucket size dialog class definition.
 */
#ifndef DATA_INPUT_DIALOG_H_
#define DATA_INPUT_DIALOG_H_

#include <QDialog>

namespace Ui {
class DataInputDialog;
}

/**
 * \brief  The bucket size dialog class represents the dialog responsible for get the bucket
 * capacity from user.
 */
class DataInputDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * \brief  Constructor.
     * \param  parent Widget parent.
     */
    explicit DataInputDialog(QWidget *parent = nullptr);

    /**
     * \brief  Destructor.
     */
    ~DataInputDialog();

    int q1() const;

    int q2() const;

    int bit_r() const;

    QString file_path() const;

private slots:
    /**
     * \brief  Button clicked callback.
     */
    void on_button_clicked();

    void on_browse_file_button_clicked();

private:
    int q1_;       //!<
    int q2_;       //!<
    int bit_r_;       //!<
    QString file_path_;       //!<

    Ui::DataInputDialog *ui_;  //!< Ui component.
};

#endif // DATA_INPUT_DIALOG_H_
