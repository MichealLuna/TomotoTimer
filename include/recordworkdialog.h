#ifndef RECORDWORKDIALOG_H
#define RECORDWORKDIALOG_H

#include <QDialog>

namespace Ui {
class RecordWorkDialog;
}

class RecordWorkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordWorkDialog(QWidget *parent = nullptr);
    ~RecordWorkDialog();
    void clearContext();
signals:
    void updateRecord(QString&);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::RecordWorkDialog *ui;
};

#endif // RECORDWORKDIALOG_H
