
#ifndef WIDGET_H
#define WIDGET_H

#include <QIcon>
#include <QWidget>
#include <QDateTime>
#include <QCloseEvent>
#include <QMediaPlayer>
#include <QSystemTrayIcon>

#include "setting.h"
#include "fileapender.h"
#include "musicform.h"
#include "recordworkdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    enum State{
        WorkTime,
        HappyTime
    };
private slots:
    void on_pushButton_clicked();
    //void updateMusicPath(QString&);
    void on_pushButton_2_clicked();
    //textBrowser
    void onCurrenLineLight();
    void onTimeOut();
    void on_trayIconActivated(QSystemTrayIcon::ActivationReason);
    void tomatoTimeOut();
    void updateTomato(double val);
    void updateHappy(double val);
    void updateWorkContext(QString&);
    void updateRecordState(int);
    void updateSaveState(int);
    void on_Widget_customContextMenuRequested(const QPoint& point);
    void setTrueClose();
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void onWorking();
    void onBreaking();
private:
    Ui::Widget *ui;
    Setting *setting;
    RecordWorkDialog *recordDialog;

    //enable work recording or not,and save it or not.
    bool EnableWork;
    bool isSave;

    QDateTime beginTime;
    int64_t tomatoTimes = 25 * 60 * 1000;
    int64_t happyTimes = 5 * 60 * 1000;
    State currState = WorkTime;
    QFont font;
    int count = 0; //当天计数

    //update work context
    QString workContext;

    //music config
    QString musicPath;
    MusicForm* musicFrom;

    //log
    Apender * apender;

    QSystemTrayIcon* m_trayIcon;
    bool trueClose = false;
};

#endif // WIDGET_H
