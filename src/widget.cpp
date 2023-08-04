#include<QTimer>
#include<QDateTime>
#include<QDebug>
#include<QMenu>
#include<QAction>
#include "../inc/widget.h"
#include "ui_widget.h"

#include<QtMultimedia/QMediaPlayer>


#define SECOND 1000
#define MUMITE 60

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , setting(new Setting)
    , recordDialog(new RecordWorkDialog(this))
    , EnableWork(false)
    , isSave(true)
    , musicFrom(new MusicForm)
    , m_trayIcon(new QSystemTrayIcon(this))
{
    ui->setupUi(this);
    setWindowTitle(tr("Tomato Timer"));
    //setAttribute(Qt::WA_DeleteOnClose,false);

    //init font
    font.setBold(true);
    font.setPointSize(12);

    musicFrom->hide();
    connect(this,SIGNAL(onWorking()),musicFrom,SLOT(pause()));
    connect(this,SIGNAL(onBreaking()),musicFrom,SLOT(play()));

    //init setting widget
    setting->hide();
    connect(setting,SIGNAL(updateHappy(double)),this,SLOT(updateHappy(double)));
    connect(setting,SIGNAL(updateTomato(double)),this,SLOT(updateTomato(double)));
    connect(setting,SIGNAL(updateRecordState(int)),this,SLOT(updateRecordState(int)));
    connect(setting,SIGNAL(updateSaveState(int)),this,SLOT(updateSaveState(int)));

    //init recordDialog
    recordDialog->hide();
    connect(recordDialog,SIGNAL(updateRecord(QString&)),this,SLOT(updateWorkContext(QString&)));

    //init work record
    workContext = tr("Do nothing");

    //init lcd timer
    ui->lcdNumber->setDigitCount(25);
    ui->lcdNumber->setMode(QLCDNumber::Dec);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setStyleSheet("border: 1px solid green; color: green; background:silver;");

    ui->lcdNumber_2->setDigitCount(13);
    ui->lcdNumber_2->setMode(QLCDNumber::Dec);
    ui->lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber_2->setStyleSheet("border: 1px solid green; color: green; background:silver;");

    //Set click timer 1000ms.
    QTimer *ptimer = new QTimer(this);
    ptimer->setInterval(1000);
    beginTime = QDateTime::currentDateTime();
    connect(ptimer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    connect(ptimer,SIGNAL(timeout()),this,SLOT(tomatoTimeOut()));
    ptimer->start();

    //init log path
    QString logFileName = "./";
    logFileName += beginTime.toString("yyyy_MM_dd");
    logFileName += "_log.txt";
    apender = new FileApender(logFileName);

    //select cursor
    connect(ui->textBrowser,SIGNAL(cursorPositionChanged()),this,SLOT(onCurrenLineLight()));

    //trayIcon
    QIcon icon = QIcon(":/icons/icon.png");
    setWindowIcon(icon);
    m_trayIcon->setIcon(icon);
    m_trayIcon->setToolTip(tr("这是一个任务记录"));
    QString titlec = tr("Timer");
    QString textc  = QString::fromLatin1("Tomato timer");
    m_trayIcon->show();
    m_trayIcon->showMessage(titlec,textc,QSystemTrayIcon::Information,5000);
    connect(m_trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason))
            ,this,SLOT(on_trayIconActivated(QSystemTrayIcon::ActivationReason)));

    //trayIcon message
    setContextMenuPolicy(Qt::CustomContextMenu);
}

Widget::~Widget()
{
    delete ui;
    delete setting;
    delete apender;
    delete musicFrom;
}

void Widget::closeEvent(QCloseEvent *event){
    if(!trueClose)
    {
        event->ignore();
        hide();
    }
}

void Widget::on_Widget_customContextMenuRequested(const QPoint &point){
    QMenu Menu =  QMenu(this);
    QAction open =  QAction(tr("显示主界面"),this);
    QAction close =  QAction(tr("退出"),this);

    Menu.addAction(&open);
    Menu.addAction(&close);

    connect(&open,SIGNAL(triggered()),this,SLOT(show()));
    connect(&close,SIGNAL(triggered()),this,SLOT(setTrueClose()));

    Menu.exec(point);
}

void Widget::on_trayIconActivated(QSystemTrayIcon::ActivationReason reason){
    if(reason == QSystemTrayIcon::DoubleClick)
        show();
    else if(reason == QSystemTrayIcon::Trigger){
        on_Widget_customContextMenuRequested(cursor().pos());
    }
}

void Widget::onTimeOut()
{
    QDateTime datatime = QDateTime::currentDateTime();
    ui->lcdNumber->display(datatime.toString("yyyy-MM-dd HH:mm:ss.zzz"));
}

void Widget::tomatoTimeOut(){
    std::chrono::milliseconds delta = QDateTime::currentDateTime() - beginTime;

    if(currState == WorkTime && delta.count() >= tomatoTimes){
        currState = HappyTime;
        ui->label_2->setText(tr("EatTomato"));
        ui->label_2->setFont(font);
        ui->label_2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        //printf work time,what you do and what next to do
        QString currWork(tr("【%1】番茄工作时间: ").arg(++count) +
                         beginTime.toString("HH:mm") + " - "  +
                         QDateTime::currentDateTime().toString("HH:mm "));

        currWork += "\n【WorkFlied】: ";

        //get work filed and work context
        if(EnableWork){
            recordDialog->setModal(true);
            recordDialog->setWindowModality(Qt::ApplicationModal);
            recordDialog->exec();
        }

        currWork += workContext; //这里背后使用了信号槽，让recordDialog传送context
        workContext = tr("Do nothing");
        ui->textBrowser->append(currWork);

        apender->writeLog(currWork);

        beginTime = QDateTime::currentDateTime();

        emit onBreaking();  // notiy the audioPlayer to play music

        return ;
    }else if(currState == HappyTime && delta.count() >= happyTimes){
        currState = WorkTime;
        ui->label_2->setText(tr("Tomato"));
        ui->label_2->setFont(font);
        ui->label_2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        QString Break(tr("【Break】番茄休息时间: ")  +
                      beginTime.toString("HH:mm") + " - " +
                      QDateTime::currentDateTime().toString("HH:mm "));

        Break += "\n";      //应该把记录责任抽出来，交给专门记录的函数。

        ui->textBrowser->append(Break);
        apender->writeLog(Break);

        beginTime = QDateTime::currentDateTime();

        emit onWorking(); //notiy the dudioPlayer to stop playing music

        return ;
    }

    int64_t minutes = delta.count() / (1000 * 60);
    int64_t seconds = (delta.count()/1000) % (60);
    int64_t milliseconds = (delta.count()) % 1000;

    ui->lcdNumber_2->display(QString("%1:%2.%3").arg(minutes).arg(seconds).arg(milliseconds));
}

void Widget::updateTomato(double val){
    tomatoTimes = static_cast<int64_t>(val * MUMITE * SECOND);
}

void Widget::updateHappy(double val){
    happyTimes = static_cast<int64_t>(val * MUMITE * SECOND);
}

void Widget::updateWorkContext(QString& ctx){
    workContext = ctx;
}

void Widget::updateRecordState(int val){
    if(val == 0){
        EnableWork = false;
    }else if(val == 2){
        EnableWork = true;
    }else if(val == 1){
        EnableWork = false;
    }
}

void Widget::updateSaveState(int val){
    if(val == 0){
        isSave = false;
    }else if(val == 2){
        isSave = true;
    }else if(val == 1){
        isSave = false;
    }
}

//void Widget::updateMusicPath(QString &val){
//    musicPath = val;
//}

void Widget::on_pushButton_2_clicked()
{
    musicFrom->show();
}

void Widget::on_pushButton_clicked()
{
    setting->show();
}

void Widget::onCurrenLineLight(){
    QList<QTextBrowser::ExtraSelection> extraSelection;
    QTextBrowser::ExtraSelection selection;
    QColor color = QColor(Qt::gray).lighter(150);
    selection.format.setBackground(color);
    selection.format.setProperty(QTextFormat::FullWidthSelection,true);
    selection.cursor = ui->textBrowser->textCursor();
    selection.cursor.clearSelection();

    extraSelection.append(selection);
    ui->textBrowser->setExtraSelections(extraSelection);
}

void Widget::setTrueClose(){
    trueClose = true;
    close();
}
