#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

class QFileDialog;

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void recordStateChanged(int);
    void saveStateChanged(int);
    //void on_pushButton_clicked();

signals:
    void updateTomato(double val);
    void updateHappy(double val);
    void updateRecordState(int);
    void updateSaveState(int);
    //void updateMuisc(QString&);
private:
    Ui::Setting *ui;
};

#endif // SETTING_H
